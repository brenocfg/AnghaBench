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
struct ttm_object_device {int /*<<< orphan*/  object_lock; int /*<<< orphan*/  object_hash; } ;
struct ttm_base_object {int /*<<< orphan*/  (* refcount_release ) (struct ttm_base_object**) ;TYPE_1__* tfile; int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {struct ttm_object_device* tdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_ht_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ttm_base_object**) ; 
 int /*<<< orphan*/  ttm_object_file_unref (TYPE_1__**) ; 

__attribute__((used)) static void ttm_release_base(struct ttm_base_object *base)
{
	struct ttm_object_device *tdev = base->tfile->tdev;

	(void)drm_ht_remove_item(&tdev->object_hash, &base->hash);
	rw_wunlock(&tdev->object_lock);
	/*
	 * Note: We don't use synchronize_rcu() here because it's far
	 * too slow. It's up to the user to free the object using
	 * call_rcu() or ttm_base_object_kfree().
	 */

	if (base->refcount_release) {
		ttm_object_file_unref(&base->tfile);
		base->refcount_release(&base);
	}
	rw_wlock(&tdev->object_lock);
}