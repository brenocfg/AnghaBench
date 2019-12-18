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
struct proc {int dummy; } ;
struct itimer {scalar_t__ it_overrun; scalar_t__ it_overrun_last; } ;
struct TYPE_3__ {scalar_t__ ksi_overrun; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ITIMER_UNLOCK (struct itimer*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 struct itimer* itimer_find (struct proc*,int) ; 

int
itimer_accept(struct proc *p, int timerid, ksiginfo_t *ksi)
{
	struct itimer *it;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	it = itimer_find(p, timerid);
	if (it != NULL) {
		ksi->ksi_overrun = it->it_overrun;
		it->it_overrun_last = it->it_overrun;
		it->it_overrun = 0;
		ITIMER_UNLOCK(it);
		return (0);
	}
	return (EINVAL);
}