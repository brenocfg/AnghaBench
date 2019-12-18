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
struct pcpu_state {int now; int idle; int nextevent; } ;
typedef  int sbintime_t ;
struct TYPE_2__ {int et_flags; } ;

/* Variables and functions */
 scalar_t__ CPU_FIRST () ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct pcpu_state* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int ET_FLAGS_PERCPU ; 
 int /*<<< orphan*/  ET_HW_LOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  ET_HW_UNLOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ busy ; 
 scalar_t__ curcpu ; 
 int getnextcpuevent (int) ; 
 scalar_t__ idletick ; 
 int /*<<< orphan*/  loadtimer (int,int /*<<< orphan*/ ) ; 
 scalar_t__ periodic ; 
 int sbinuptime () ; 
 TYPE_1__* timer ; 
 int /*<<< orphan*/  timerstate ; 

sbintime_t
cpu_idleclock(void)
{
	sbintime_t now, t;
	struct pcpu_state *state;

	if (idletick || busy ||
	    (periodic && (timer->et_flags & ET_FLAGS_PERCPU))
#ifdef DEVICE_POLLING
	    || curcpu == CPU_FIRST()
#endif
	    )
		return (-1);
	state = DPCPU_PTR(timerstate);
	if (periodic)
		now = state->now;
	else
		now = sbinuptime();
	CTR3(KTR_SPARE2, "idle at %d:    now  %d.%08x",
	    curcpu, (int)(now >> 32), (u_int)(now & 0xffffffff));
	t = getnextcpuevent(1);
	ET_HW_LOCK(state);
	state->idle = 1;
	state->nextevent = t;
	if (!periodic)
		loadtimer(now, 0);
	ET_HW_UNLOCK(state);
	return (MAX(t - now, 0));
}