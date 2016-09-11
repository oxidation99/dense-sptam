#include "dense.hpp"

Dense::Dense(const sensor_msgs::CameraInfoConstPtr& left_info, const sensor_msgs::CameraInfoConstPtr& right_info,
             double frustumNearPlaneDist, double frustumFarPlaneDist, double voxelLeafSize,
             double filter_meanK, double filter_stddev, std::string disp_calc_method)
  : left_info_(left_info)
  , right_info_(right_info)
  , frustumNearPlaneDist_(frustumNearPlaneDist)
  , frustumFarPlaneDist_(frustumFarPlaneDist)
  , voxelLeafSize_(voxelLeafSize)
  , filter_meanK_(filter_meanK)
  , filter_stddev_(filter_stddev)
  , disp_calc_method_(disp_calc_method)
{
    camera_ = new Camera(left_info_, right_info_, frustumNearPlaneDist_, frustumFarPlaneDist_);
    raw_image_pairs_ = new ImageQueue();
    disp_images_ = new DispImageQueue();
    point_clouds_ = new PointCloudQueue();

    disparityCalcThread = new DisparityCalcThread(this);
    projectionThread_ = new ProjectionThread(this);
    refinementThread_ = new RefinementThread(this);
}

Dense::~Dense()
{}
