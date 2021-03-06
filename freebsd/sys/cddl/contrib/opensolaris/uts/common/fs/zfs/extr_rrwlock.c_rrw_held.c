#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rr_writer; int /*<<< orphan*/  rr_lock; int /*<<< orphan*/  rr_anon_rcount; } ;
typedef  TYPE_1__ rrwlock_t ;
typedef  scalar_t__ krw_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ RW_WRITER ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrn_find (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_refcount_is_zero (int /*<<< orphan*/ *) ; 

boolean_t
rrw_held(rrwlock_t *rrl, krw_t rw)
{
	boolean_t held;

	mutex_enter(&rrl->rr_lock);
	if (rw == RW_WRITER) {
		held = (rrl->rr_writer == curthread);
	} else {
		held = (!zfs_refcount_is_zero(&rrl->rr_anon_rcount) ||
		    rrn_find(rrl) != NULL);
	}
	mutex_exit(&rrl->rr_lock);

	return (held);
}