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
struct drm_file {scalar_t__ is_master; TYPE_2__* minor; } ;
struct drm_device {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  master; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* master_drop ) (struct drm_device*,struct drm_file*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_master_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,struct drm_file*,int) ; 

int drm_dropmaster_ioctl(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	if (!file_priv->is_master)
		return -EINVAL;

	if (!file_priv->minor->master)
		return -EINVAL;

	DRM_LOCK(dev);
	if (dev->driver->master_drop)
		dev->driver->master_drop(dev, file_priv, false);
	drm_master_put(&file_priv->minor->master);
	file_priv->is_master = 0;
	DRM_UNLOCK(dev);
	return 0;
}