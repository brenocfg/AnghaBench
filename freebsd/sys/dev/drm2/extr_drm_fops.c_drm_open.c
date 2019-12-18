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
struct drm_minor {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  open_count; int /*<<< orphan*/  dev; int /*<<< orphan*/ * counts; } ;
struct cdev {struct drm_minor* si_drv1; } ;
typedef  int /*<<< orphan*/  DRM_STRUCTPROC ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  Giant ; 
 size_t _DRM_STAT_OPENS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_global_mutex ; 
 int drm_open_helper (struct cdev*,int,int,int /*<<< orphan*/ *,struct drm_device*) ; 
 int drm_setup (struct drm_device*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int drm_open(struct cdev *kdev, int flags, int fmt, DRM_STRUCTPROC *p)
{
	struct drm_device *dev = NULL;
	struct drm_minor *minor;
	int retcode = 0;
	int need_setup = 0;

	minor = kdev->si_drv1;
	if (!minor)
		return ENODEV;

	if (!(dev = minor->dev))
		return ENODEV;

	sx_xlock(&drm_global_mutex);

	/*
	 * FIXME Linux<->FreeBSD: On Linux, counter updated outside
	 * global mutex.
	 */
	if (!dev->open_count++)
		need_setup = 1;

	retcode = drm_open_helper(kdev, flags, fmt, p, dev);
	if (retcode) {
		sx_xunlock(&drm_global_mutex);
		return (-retcode);
	}
	atomic_inc(&dev->counts[_DRM_STAT_OPENS]);
	if (need_setup) {
		retcode = drm_setup(dev);
		if (retcode)
			goto err_undo;
	}
	sx_xunlock(&drm_global_mutex);
	return 0;

err_undo:
	mtx_lock(&Giant); /* FIXME: Giant required? */
	device_unbusy(dev->dev);
	mtx_unlock(&Giant);
	dev->open_count--;
	sx_xunlock(&drm_global_mutex);
	return -retcode;
}