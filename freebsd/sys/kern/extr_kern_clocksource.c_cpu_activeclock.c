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
typedef  int /*<<< orphan*/  u_int ;
struct thread {int /*<<< orphan*/  td_intr_nesting_level; } ;
struct pcpu_state {scalar_t__ idle; int now; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct pcpu_state* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 scalar_t__ busy ; 
 int /*<<< orphan*/  curcpu ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  handleevents (int,int) ; 
 scalar_t__ periodic ; 
 int sbinuptime () ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 
 int /*<<< orphan*/  timerstate ; 

void
cpu_activeclock(void)
{
	sbintime_t now;
	struct pcpu_state *state;
	struct thread *td;

	state = DPCPU_PTR(timerstate);
	if (state->idle == 0 || busy)
		return;
	if (periodic)
		now = state->now;
	else
		now = sbinuptime();
	CTR3(KTR_SPARE2, "active at %d:  now  %d.%08x",
	    curcpu, (int)(now >> 32), (u_int)(now & 0xffffffff));
	spinlock_enter();
	td = curthread;
	td->td_intr_nesting_level++;
	handleevents(now, 1);
	td->td_intr_nesting_level--;
	spinlock_exit();
}