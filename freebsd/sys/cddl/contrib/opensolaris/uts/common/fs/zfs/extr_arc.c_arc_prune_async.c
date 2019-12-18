#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_pfunc; int /*<<< orphan*/  p_refcnt; int /*<<< orphan*/  p_adjust; } ;
typedef  TYPE_1__ arc_prune_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCSTAT_BUMP (int /*<<< orphan*/ ) ; 
 scalar_t__ TASKQID_INVALID ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  arc_prune_list ; 
 int /*<<< orphan*/  arc_prune_mtx ; 
 int /*<<< orphan*/  arc_prune_task ; 
 int /*<<< orphan*/  arc_prune_taskq ; 
 int /*<<< orphan*/  arcstat_prune ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_refcount_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arc_prune_async(int64_t adjust)
{
	arc_prune_t *ap;

	mutex_enter(&arc_prune_mtx);
	for (ap = list_head(&arc_prune_list); ap != NULL;
	    ap = list_next(&arc_prune_list, ap)) {

		if (zfs_refcount_count(&ap->p_refcnt) >= 2)
			continue;

		zfs_refcount_add(&ap->p_refcnt, ap->p_pfunc);
		ap->p_adjust = adjust;
		if (taskq_dispatch(arc_prune_taskq, arc_prune_task,
		    ap, TQ_SLEEP) == TASKQID_INVALID) {
			zfs_refcount_remove(&ap->p_refcnt, ap->p_pfunc);
			continue;
		}
		ARCSTAT_BUMP(arcstat_prune);
	}
	mutex_exit(&arc_prune_mtx);
}