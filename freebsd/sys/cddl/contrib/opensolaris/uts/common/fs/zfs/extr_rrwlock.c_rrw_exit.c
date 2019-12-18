#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ rc_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  rr_lock; int /*<<< orphan*/  rr_cv; int /*<<< orphan*/ * rr_writer; TYPE_2__ rr_linked_rcount; TYPE_2__ rr_anon_rcount; int /*<<< orphan*/  rr_track_all; } ;
typedef  TYPE_1__ rrwlock_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_PROBE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ rrn_find_and_remove (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  zfs__rrwfastpath__exitmiss ; 
 scalar_t__ zfs_refcount_is_zero (TYPE_2__*) ; 
 scalar_t__ zfs_refcount_remove (TYPE_2__*,void*) ; 

void
rrw_exit(rrwlock_t *rrl, void *tag)
{
	mutex_enter(&rrl->rr_lock);
#if !defined(DEBUG) && defined(_KERNEL)
	if (!rrl->rr_writer && rrl->rr_linked_rcount.rc_count == 0) {
		rrl->rr_anon_rcount.rc_count--;
		if (rrl->rr_anon_rcount.rc_count == 0)
			cv_broadcast(&rrl->rr_cv);
		mutex_exit(&rrl->rr_lock);
		return;
	}
	DTRACE_PROBE(zfs__rrwfastpath__exitmiss);
#endif
	ASSERT(!zfs_refcount_is_zero(&rrl->rr_anon_rcount) ||
	    !zfs_refcount_is_zero(&rrl->rr_linked_rcount) ||
	    rrl->rr_writer != NULL);

	if (rrl->rr_writer == NULL) {
		int64_t count;
		if (rrn_find_and_remove(rrl, tag)) {
			count = zfs_refcount_remove(
			    &rrl->rr_linked_rcount, tag);
		} else {
			ASSERT(!rrl->rr_track_all);
			count = zfs_refcount_remove(&rrl->rr_anon_rcount, tag);
		}
		if (count == 0)
			cv_broadcast(&rrl->rr_cv);
	} else {
		ASSERT(rrl->rr_writer == curthread);
		ASSERT(zfs_refcount_is_zero(&rrl->rr_anon_rcount) &&
		    zfs_refcount_is_zero(&rrl->rr_linked_rcount));
		rrl->rr_writer = NULL;
		cv_broadcast(&rrl->rr_cv);
	}
	mutex_exit(&rrl->rr_lock);
}