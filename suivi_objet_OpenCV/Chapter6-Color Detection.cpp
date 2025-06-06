#include<opencv2/opencv.hpp>
//此文件下包含了几乎所有需要用到的opencv源文件，无需再调用
#include<iostream>

//使用命名空间后不需要在API前声明std::或cv2::
//命名空间其实就是给API前加个前缀，这样引用的时候std::string可以防止重名，因为可能很多文件中都定义了string
using namespace cv;  //声明使用API的名字是cv的
using namespace std; 

int hmin = 10, smin = 0, vmin = 186;
int hmax = 179, smax = 61, vmax = 255;

//0,0,0
//179,255,188   //白光处全黑，反片后可清晰提取

//10,0,186;
//179,61,255;    //白光处全白，先erode x2,dilate x2 后无噪声。
int main() 
{
	///////////////////////////////////////图片中利用color detection对物体进行提取////////////////////////////////////
	//选中文本，ctrl+K→ctrl+C实现多行同时注释(comment)
	//选中文本，ctrl+K→ctrl+U实现取消多行注释(uncomment)
	
	// string path = "D:/OpenCV/Images/test.jpg";
	// Mat img, imgHSV, mask;
	// img = imread(path);
	// ////此部分为测试另一灰度图转化为RGB再转化为HSV的代码
	// //string path = "C:/Users/T480s/Desktop/image1.jpg";
	// //Mat img, imgHSV, mask,imgRGB;
	// //img = imread(path, 0);
	// //cvtColor(img, imgRGB, COLOR_GRAY2RGB);
	// //imshow("imgRGB", imgRGB);

	// Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //设定形状,卷积核越大则影响的区域越大，越小影响越细
	// erode(img, img, kernel); erode(img, img, kernel); dilate(img, img, kernel); dilate(img, img, kernel);

	// namedWindow("Trackbars", (640, 240));
	// createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	// createTrackbar("Hue Max", "Trackbars", &hmax, 179);  //HSV色彩空间中h最大值为179
	// createTrackbar("Sat Min", "Trackbars", &smin, 255);
	// createTrackbar("Sat Max", "Trackbars", &smax, 255);
	// createTrackbar("Val Min", "Trackbars", &vmin, 255);
	// createTrackbar("Val Max", "Trackbars", &vmax, 255); //改变滑动条后要按回车
	// //cvtColor(imgRGB, imgHSV, COLOR_RGB2HSV); 
	// cvtColor(img, imgHSV, COLOR_RGB2HSV);
	// while (true)
	// {
	// 	Scalar lower(hmin, smin, vmin);
	// 	Scalar upper(hmax, smax, vmax);
	// 	inRange(imgHSV, lower, upper, mask);
	// 	imshow("Original", img);
	// 	imshow("imgHSV", imgHSV);
	// 	imshow("mask", mask);
	// 	waitKey(0);
	// }
		
	 
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	///////////////////////////////视频中利用color detection/////////////////////////////////////////////
	Mat img, imgHSV, mask;
	Mat final_image;
	VideoCapture video("D:/OpenCV/Images/video_test.mp4");
	if (!video.isOpened())  //对video进行异常检测  
	{
		cout << endl; cout << endl;
		cout << "video opens with error!" << endl;
		cout << endl; cout << endl;
		return 0;
	}
	else
	{
		cout << endl; cout << endl;
		cout << "video opens successfully!" << endl;
		cout << endl; cout << endl;
	}
	int frameCount = video.get(CAP_PROP_FRAME_COUNT);
	int i = frameCount;
	//int framePosition = video.get(CAP_PROP_POS_FRAMES);

	while (i)
	{
		i--;
		video >> img;
		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		//没开GPU速度太慢
		//Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //设定形状,卷积核越大则影响的区域越大，越小影响越细
		//erode(img, img, kernel); erode(img, img, kernel); dilate(img, img, kernel); dilate(img, img, kernel);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		namedWindow("Original", 0);
		namedWindow("mask", 0);
		imshow("Original", img);
		//imshow("imgHSV", imgHSV);
		imshow("mask", mask);

		//vector<vector<Point>> contours;
		//findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		//// 在mask上绘制轮廓
		//drawContours(final_image, contours, -1, Scalar(0, 0, 255), 2);
		//imshow("Final", final_image);

		waitKey(1);
	}
	return 0;
}
