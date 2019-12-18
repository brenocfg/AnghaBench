#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct pcpu_state {int nextcallopt; int nextcall; int nextevent; int handle; } ;
typedef  int sbintime_t ;
struct TYPE_2__ {int et_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ABSENT (int) ; 
 int /*<<< orphan*/  CTR6 (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct pcpu_state* DPCPU_ID_PTR (int,int /*<<< orphan*/ ) ; 
 int ET_FLAGS_PERCPU ; 
 int /*<<< orphan*/  ET_HW_LOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  ET_HW_UNLOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  IPI_HARDCLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 scalar_t__ busy ; 
 int curcpu ; 
 int /*<<< orphan*/  ipi_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loadtimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ periodic ; 
 int /*<<< orphan*/  sbinuptime () ; 
 TYPE_1__* timer ; 
 int /*<<< orphan*/  timerstate ; 

void
cpu_new_callout(int cpu, sbintime_t bt, sbintime_t bt_opt)
{
	struct pcpu_state *state;

	/* Do not touch anything if somebody reconfiguring timers. */
	if (busy)
		return;
	CTR6(KTR_SPARE2, "new co at %d:    on %d at %d.%08x - %d.%08x",
	    curcpu, cpu, (int)(bt_opt >> 32), (u_int)(bt_opt & 0xffffffff),
	    (int)(bt >> 32), (u_int)(bt & 0xffffffff));

	KASSERT(!CPU_ABSENT(cpu), ("Absent CPU %d", cpu));
	state = DPCPU_ID_PTR(cpu, timerstate);
	ET_HW_LOCK(state);

	/*
	 * If there is callout time already set earlier -- do nothing.
	 * This check may appear redundant because we check already in
	 * callout_process() but this double check guarantees we're safe
	 * with respect to race conditions between interrupts execution
	 * and scheduling.
	 */
	state->nextcallopt = bt_opt;
	if (bt >= state->nextcall)
		goto done;
	state->nextcall = bt;
	/* If there is some other event set earlier -- do nothing. */
	if (bt >= state->nextevent)
		goto done;
	state->nextevent = bt;
	/* If timer is periodic -- there is nothing to reprogram. */
	if (periodic)
		goto done;
	/* If timer is global or of the current CPU -- reprogram it. */
	if ((timer->et_flags & ET_FLAGS_PERCPU) == 0 || cpu == curcpu) {
		loadtimer(sbinuptime(), 0);
done:
		ET_HW_UNLOCK(state);
		return;
	}
	/* Otherwise make other CPU to reprogram it. */
	state->handle = 1;
	ET_HW_UNLOCK(state);
#ifdef SMP
	ipi_cpu(cpu, IPI_HARDCLOCK);
#endif
}