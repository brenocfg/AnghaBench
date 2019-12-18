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
struct TYPE_2__ {int vi_flags; int vi_mem_model; int vi_planes; int vi_width; int vi_height; int vi_window_size; int vi_depth; } ;
typedef  TYPE_1__ video_info_t ;

/* Variables and functions */
 int V_INFO_GRAPHICS ; 
 int V_INFO_LINEAR ; 
#define  V_INFO_MM_DIRECT 130 
#define  V_INFO_MM_PACKED 129 
#define  V_INFO_MM_PLANAR 128 

int
sc_support_pixel_mode(void *arg)
{
#ifdef SC_PIXEL_MODE
	video_info_t *info = arg;

	if ((info->vi_flags & V_INFO_GRAPHICS) == 0)
		return (0);

	/*
	 * We currently support the following graphic modes:
	 *
	 * - 4 bpp planar modes whose memory size does not exceed 64K
	 * - 15, 16, 24 and 32 bpp linear modes
	 */
	switch (info->vi_mem_model) {
	case V_INFO_MM_PLANAR:
		if (info->vi_planes != 4)
			break;
		/*
		 * A memory size >64K requires bank switching to access
		 * the entire screen. XXX
		 */
		if (info->vi_width * info->vi_height / 8 > info->vi_window_size)
			break;
		return (1);
	case V_INFO_MM_DIRECT:
		if ((info->vi_flags & V_INFO_LINEAR) == 0 &&
		    info->vi_depth != 15 && info->vi_depth != 16 &&
		    info->vi_depth != 24 && info->vi_depth != 32)
			break;
		return (1);
	case V_INFO_MM_PACKED:
		if ((info->vi_flags & V_INFO_LINEAR) == 0 &&
		    info->vi_depth != 8)
			break;
		return (1);
	}
#endif
	return (0);
}