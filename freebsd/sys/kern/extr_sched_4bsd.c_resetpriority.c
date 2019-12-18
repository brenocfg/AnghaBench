#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct thread {scalar_t__ td_pri_class; TYPE_1__* td_proc; } ;
struct TYPE_4__ {int ts_estcpu; } ;
struct TYPE_3__ {int p_nice; } ;

/* Variables and functions */
 int INVERSE_ESTCPU_WEIGHT ; 
 int NICE_WEIGHT ; 
 int PRIO_MIN ; 
 int /*<<< orphan*/  PRI_MAX_TIMESHARE ; 
 int /*<<< orphan*/  PRI_MIN_TIMESHARE ; 
 scalar_t__ PRI_TIMESHARE ; 
 scalar_t__ PUSER ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_user_prio (struct thread*,scalar_t__) ; 
 TYPE_2__* td_get_sched (struct thread*) ; 

__attribute__((used)) static void
resetpriority(struct thread *td)
{
	u_int newpriority;

	if (td->td_pri_class != PRI_TIMESHARE)
		return;
	newpriority = PUSER +
	    td_get_sched(td)->ts_estcpu / INVERSE_ESTCPU_WEIGHT +
	    NICE_WEIGHT * (td->td_proc->p_nice - PRIO_MIN);
	newpriority = min(max(newpriority, PRI_MIN_TIMESHARE),
	    PRI_MAX_TIMESHARE);
	sched_user_prio(td, newpriority);
}