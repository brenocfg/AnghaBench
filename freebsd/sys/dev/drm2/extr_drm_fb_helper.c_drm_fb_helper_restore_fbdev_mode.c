#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_set {TYPE_3__* crtc; } ;
struct drm_fb_helper {int crtc_count; TYPE_1__* crtc_info; } ;
struct TYPE_6__ {TYPE_2__* funcs; } ;
struct TYPE_5__ {int (* set_config ) (struct drm_mode_set*) ;} ;
struct TYPE_4__ {struct drm_mode_set mode_set; } ;

/* Variables and functions */
 int stub1 (struct drm_mode_set*) ; 

bool drm_fb_helper_restore_fbdev_mode(struct drm_fb_helper *fb_helper)
{
	bool error = false;
	int i, ret;

	for (i = 0; i < fb_helper->crtc_count; i++) {
		struct drm_mode_set *mode_set = &fb_helper->crtc_info[i].mode_set;
		ret = mode_set->crtc->funcs->set_config(mode_set);
		if (ret)
			error = true;
	}
	return error;
}