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
struct thread {int /*<<< orphan*/  td_intr_nesting_level; } ;
struct pcpu_state {int /*<<< orphan*/  now; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 struct pcpu_state* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_HW_LOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  ET_HW_UNLOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  curcpu ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  handleevents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hardclock_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbinuptime () ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 
 int /*<<< orphan*/  timerstate ; 

void
cpu_initclocks_ap(void)
{
	sbintime_t now;
	struct pcpu_state *state;
	struct thread *td;

	state = DPCPU_PTR(timerstate);
	now = sbinuptime();
	ET_HW_LOCK(state);
	state->now = now;
	hardclock_sync(curcpu);
	spinlock_enter();
	ET_HW_UNLOCK(state);
	td = curthread;
	td->td_intr_nesting_level++;
	handleevents(state->now, 2);
	td->td_intr_nesting_level--;
	spinlock_exit();
}