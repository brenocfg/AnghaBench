#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;

/* Variables and functions */
#define  DRM_FORMAT_NV12 147 
#define  DRM_FORMAT_NV16 146 
#define  DRM_FORMAT_NV21 145 
#define  DRM_FORMAT_NV24 144 
#define  DRM_FORMAT_NV42 143 
#define  DRM_FORMAT_NV61 142 
#define  DRM_FORMAT_UYVY 141 
#define  DRM_FORMAT_VYUY 140 
#define  DRM_FORMAT_YUV410 139 
#define  DRM_FORMAT_YUV411 138 
#define  DRM_FORMAT_YUV420 137 
#define  DRM_FORMAT_YUV422 136 
#define  DRM_FORMAT_YUV444 135 
#define  DRM_FORMAT_YUYV 134 
#define  DRM_FORMAT_YVU410 133 
#define  DRM_FORMAT_YVU411 132 
#define  DRM_FORMAT_YVU420 131 
#define  DRM_FORMAT_YVU422 130 
#define  DRM_FORMAT_YVU444 129 
#define  DRM_FORMAT_YVYU 128 
 int /*<<< orphan*/  drm_fb_get_bpp_depth (int,unsigned int*,int*) ; 
 int drm_format_num_planes (int) ; 

int drm_format_plane_cpp(uint32_t format, int plane)
{
	unsigned int depth;
	int bpp;

	if (plane >= drm_format_num_planes(format))
		return 0;

	switch (format) {
	case DRM_FORMAT_YUYV:
	case DRM_FORMAT_YVYU:
	case DRM_FORMAT_UYVY:
	case DRM_FORMAT_VYUY:
		return 2;
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV21:
	case DRM_FORMAT_NV16:
	case DRM_FORMAT_NV61:
	case DRM_FORMAT_NV24:
	case DRM_FORMAT_NV42:
		return plane ? 2 : 1;
	case DRM_FORMAT_YUV410:
	case DRM_FORMAT_YVU410:
	case DRM_FORMAT_YUV411:
	case DRM_FORMAT_YVU411:
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_YUV422:
	case DRM_FORMAT_YVU422:
	case DRM_FORMAT_YUV444:
	case DRM_FORMAT_YVU444:
		return 1;
	default:
		drm_fb_get_bpp_depth(format, &depth, &bpp);
		return bpp >> 3;
	}
}