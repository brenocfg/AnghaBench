#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* spa_config_lock; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_5__ {scalar_t__ scl_write_wanted; int /*<<< orphan*/ * scl_writer; int /*<<< orphan*/  scl_count; int /*<<< orphan*/  scl_cv; int /*<<< orphan*/  scl_lock; } ;
typedef  TYPE_2__ spa_config_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SCL_LOCKS ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_config_lock_destroy(spa_t *spa)
{
	for (int i = 0; i < SCL_LOCKS; i++) {
		spa_config_lock_t *scl = &spa->spa_config_lock[i];
		mutex_destroy(&scl->scl_lock);
		cv_destroy(&scl->scl_cv);
		zfs_refcount_destroy(&scl->scl_count);
		ASSERT(scl->scl_writer == NULL);
		ASSERT(scl->scl_write_wanted == 0);
	}
}