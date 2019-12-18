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
struct drm_lock_data {int idle_has_lock; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  kernel_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_KERNEL_CONTEXT ; 
 int drm_lock_take (struct drm_lock_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void drm_idlelock_take(struct drm_lock_data *lock_data)
{
	int ret;

	mtx_lock(&lock_data->spinlock);
	lock_data->kernel_waiters++;
	if (!lock_data->idle_has_lock) {

		mtx_unlock(&lock_data->spinlock);
		ret = drm_lock_take(lock_data, DRM_KERNEL_CONTEXT);
		mtx_lock(&lock_data->spinlock);

		if (ret == 1)
			lock_data->idle_has_lock = 1;
	}
	mtx_unlock(&lock_data->spinlock);
}