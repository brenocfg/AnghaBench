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
struct drm_master {int /*<<< orphan*/  lock; } ;
struct drm_lock {scalar_t__ context; } ;
struct drm_file {struct drm_master* master; } ;
struct drm_device {int /*<<< orphan*/ * counts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CURRENTPID ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DRM_KERNEL_CONTEXT ; 
 int EINVAL ; 
 size_t _DRM_STAT_UNLOCKS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_lock_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  unblock_all_signals () ; 

int drm_unlock(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	struct drm_lock *lock = data;
	struct drm_master *master = file_priv->master;

	if (lock->context == DRM_KERNEL_CONTEXT) {
		DRM_ERROR("Process %d using kernel context %d\n",
			  DRM_CURRENTPID, lock->context);
		return -EINVAL;
	}

	atomic_inc(&dev->counts[_DRM_STAT_UNLOCKS]);

	if (drm_lock_free(&master->lock, lock->context)) {
		/* FIXME: Should really bail out here. */
	}

#if defined(__linux__)
	unblock_all_signals();
#endif
	return 0;
}