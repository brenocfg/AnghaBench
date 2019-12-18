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
typedef  int /*<<< orphan*/  uint32_t ;
struct fb_info {int /*<<< orphan*/  fb_stride; } ;

/* Variables and functions */

void drm_fb_helper_fill_fix(struct fb_info *info, uint32_t pitch,
			    uint32_t depth)
{
	info->fb_stride = pitch;

	return;
}