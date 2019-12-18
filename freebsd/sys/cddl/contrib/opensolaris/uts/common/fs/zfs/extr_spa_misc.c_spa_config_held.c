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
struct TYPE_5__ {scalar_t__ scl_writer; int /*<<< orphan*/  scl_count; } ;
typedef  TYPE_2__ spa_config_lock_t ;
typedef  scalar_t__ krw_t ;

/* Variables and functions */
 scalar_t__ RW_READER ; 
 scalar_t__ RW_WRITER ; 
 int SCL_LOCKS ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 

int
spa_config_held(spa_t *spa, int locks, krw_t rw)
{
	int locks_held = 0;

	for (int i = 0; i < SCL_LOCKS; i++) {
		spa_config_lock_t *scl = &spa->spa_config_lock[i];
		if (!(locks & (1 << i)))
			continue;
		if ((rw == RW_READER &&
		    !zfs_refcount_is_zero(&scl->scl_count)) ||
		    (rw == RW_WRITER && scl->scl_writer == curthread))
			locks_held |= 1 << i;
	}

	return (locks_held);
}