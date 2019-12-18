#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* output_poll_changed ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sysfs_hotplug_event (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 

void drm_kms_helper_hotplug_event(struct drm_device *dev)
{
	/* send a uevent + call fbdev */
#ifdef FREEBSD_NOTYET
	drm_sysfs_hotplug_event(dev);
#endif /* FREEBSD_NOTYET */
	if (dev->mode_config.funcs->output_poll_changed)
		dev->mode_config.funcs->output_poll_changed(dev);
}