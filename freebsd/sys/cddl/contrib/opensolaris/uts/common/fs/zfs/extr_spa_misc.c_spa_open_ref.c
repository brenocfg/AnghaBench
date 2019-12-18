#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ spa_minref; int /*<<< orphan*/  spa_refcount; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ zfs_refcount_count (int /*<<< orphan*/ *) ; 

void
spa_open_ref(spa_t *spa, void *tag)
{
	ASSERT(zfs_refcount_count(&spa->spa_refcount) >= spa->spa_minref ||
	    MUTEX_HELD(&spa_namespace_lock));
	(void) zfs_refcount_add(&spa->spa_refcount, tag);
}