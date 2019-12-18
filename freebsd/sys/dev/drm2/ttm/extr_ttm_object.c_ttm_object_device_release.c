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
struct ttm_object_device {int /*<<< orphan*/  object_lock; int /*<<< orphan*/  object_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_OBJ_DEV ; 
 int /*<<< orphan*/  drm_ht_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ttm_object_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

void ttm_object_device_release(struct ttm_object_device **p_tdev)
{
	struct ttm_object_device *tdev = *p_tdev;

	*p_tdev = NULL;

	rw_wlock(&tdev->object_lock);
	drm_ht_remove(&tdev->object_hash);
	rw_wunlock(&tdev->object_lock);

	free(tdev, M_TTM_OBJ_DEV);
}