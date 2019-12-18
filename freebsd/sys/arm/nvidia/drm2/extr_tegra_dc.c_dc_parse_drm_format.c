#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_2__ {int pixel_format; int /*<<< orphan*/ * pitches; scalar_t__* offsets; int /*<<< orphan*/  bits_per_pixel; } ;
struct tegra_fb {int rotation; int flip_x; int flip_y; TYPE_1__ drm_fb; struct tegra_bo** planes; int /*<<< orphan*/  block_height; scalar_t__ block_linear; } ;
struct tegra_bo {scalar_t__ pbase; } ;
struct dc_window {int transpose_xy; int flip_x; int flip_y; int is_yuv; int is_yuv_planar; int /*<<< orphan*/ * stride; scalar_t__* base; int /*<<< orphan*/  bits_per_pixel; void* swap; void* color_mode; int /*<<< orphan*/  block_height; int /*<<< orphan*/  surface_kind; } ;

/* Variables and functions */
 void* BYTE_SWAP (int /*<<< orphan*/ ) ; 
#define  DRM_FORMAT_RGB565 134 
#define  DRM_FORMAT_UYVY 133 
#define  DRM_FORMAT_XBGR8888 132 
#define  DRM_FORMAT_XRGB8888 131 
#define  DRM_FORMAT_YUV420 130 
#define  DRM_FORMAT_YUV422 129 
#define  DRM_FORMAT_YUYV 128 
 int EINVAL ; 
 int /*<<< orphan*/  NOSWAP ; 
 int /*<<< orphan*/  SURFACE_KIND_BL_16B2 ; 
 int /*<<< orphan*/  SURFACE_KIND_PITCH ; 
 int /*<<< orphan*/  SWAP2 ; 
 void* WIN_COLOR_DEPTH_B5G6R5 ; 
 void* WIN_COLOR_DEPTH_B8G8R8A8 ; 
 void* WIN_COLOR_DEPTH_R8G8B8A8 ; 
 void* WIN_COLOR_DEPTH_YCbCr420P ; 
 void* WIN_COLOR_DEPTH_YCbCr422 ; 
 void* WIN_COLOR_DEPTH_YCbCr422P ; 
 int drm_format_num_planes (int) ; 

__attribute__((used)) static int
dc_parse_drm_format(struct tegra_fb *fb, struct dc_window *win)
{
	struct tegra_bo *bo;
	uint32_t cm;
	uint32_t sw;
	bool is_yuv, is_yuv_planar;
	int nplanes, i;

	switch (fb->drm_fb.pixel_format) {
	case DRM_FORMAT_XBGR8888:
		sw = BYTE_SWAP(NOSWAP);
		cm = WIN_COLOR_DEPTH_R8G8B8A8;
		is_yuv = false;
		is_yuv_planar = false;
		break;

	case DRM_FORMAT_XRGB8888:
		sw = BYTE_SWAP(NOSWAP);
		cm = WIN_COLOR_DEPTH_B8G8R8A8;
		is_yuv = false;
		is_yuv_planar = false;
		break;

	case DRM_FORMAT_RGB565:
		sw = BYTE_SWAP(NOSWAP);
		cm = WIN_COLOR_DEPTH_B5G6R5;
		is_yuv = false;
		is_yuv_planar = false;
		break;

	case DRM_FORMAT_UYVY:
		sw = BYTE_SWAP(NOSWAP);
		cm = WIN_COLOR_DEPTH_YCbCr422;
		is_yuv = true;
		is_yuv_planar = false;
		break;

	case DRM_FORMAT_YUYV:
		sw = BYTE_SWAP(SWAP2);
		cm = WIN_COLOR_DEPTH_YCbCr422;
		is_yuv = true;
		is_yuv_planar = false;
		break;

	case DRM_FORMAT_YUV420:
		sw = BYTE_SWAP(NOSWAP);
		cm = WIN_COLOR_DEPTH_YCbCr420P;
		is_yuv = true;
		is_yuv_planar = true;
		break;

	case DRM_FORMAT_YUV422:
		sw = BYTE_SWAP(NOSWAP);
		cm = WIN_COLOR_DEPTH_YCbCr422P;
		is_yuv = true;
		is_yuv_planar = true;
		break;

	default:
		/* Unsupported format */
		return (-EINVAL);
	}

	/* Basic check of arguments. */
	switch (fb->rotation) {
	case 0:
	case 180:
		break;

	case 90: 		/* Rotation is supported only */
	case 270:		/*  for block linear surfaces */
		if (!fb->block_linear)
			return (-EINVAL);
		break;

	default:
		return (-EINVAL);
	}
	/* XXX Add more checks (sizes, scaling...) */

	if (win == NULL)
		return (0);

	win->surface_kind =
	    fb->block_linear ? SURFACE_KIND_BL_16B2: SURFACE_KIND_PITCH;
	win->block_height = fb->block_height;
	switch (fb->rotation) {
	case 0:					/* (0,0,0) */
		win->transpose_xy = false;
		win->flip_x = false;
		win->flip_y = false;
		break;

	case 90:				/* (1,0,1) */
		win->transpose_xy = true;
		win->flip_x = false;
		win->flip_y = true;
		break;

	case 180:				/* (0,1,1) */
		win->transpose_xy = false;
		win->flip_x = true;
		win->flip_y = true;
		break;

	case 270:				/* (1,1,0) */
		win->transpose_xy = true;
		win->flip_x = true;
		win->flip_y = false;
		break;
	}
	win->flip_x ^= fb->flip_x;
	win->flip_y ^= fb->flip_y;

	win->color_mode = cm;
	win->swap = sw;
	win->bits_per_pixel = fb->drm_fb.bits_per_pixel;
	win->is_yuv = is_yuv;
	win->is_yuv_planar = is_yuv_planar;

	nplanes = drm_format_num_planes(fb->drm_fb.pixel_format);
	for (i = 0; i < nplanes; i++) {
		bo = fb->planes[i];
		win->base[i] = bo->pbase + fb->drm_fb.offsets[i];
		win->stride[i] = fb->drm_fb.pitches[i];
	}
	return (0);
}