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
typedef  int u_int ;
struct pcpu_state {scalar_t__ nexthard; scalar_t__ nextcall; scalar_t__ nextstat; scalar_t__ nextprof; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 scalar_t__ CPU_FIRST () ; 
 struct pcpu_state* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ curcpu ; 
 int hz ; 
 scalar_t__ profiling ; 
 int tc_min_ticktock_freq ; 
 int tick_sbt ; 
 int /*<<< orphan*/  timerstate ; 

__attribute__((used)) static sbintime_t
getnextcpuevent(int idle)
{
	sbintime_t event;
	struct pcpu_state *state;
	u_int hardfreq;

	state = DPCPU_PTR(timerstate);
	/* Handle hardclock() events, skipping some if CPU is idle. */
	event = state->nexthard;
	if (idle) {
		hardfreq = (u_int)hz / 2;
		if (tc_min_ticktock_freq > 2
#ifdef SMP
		    && curcpu == CPU_FIRST()
#endif
		    )
			hardfreq = hz / tc_min_ticktock_freq;
		if (hardfreq > 1)
			event += tick_sbt * (hardfreq - 1);
	}
	/* Handle callout events. */
	if (event > state->nextcall)
		event = state->nextcall;
	if (!idle) { /* If CPU is active - handle other types of events. */
		if (event > state->nextstat)
			event = state->nextstat;
		if (profiling && event > state->nextprof)
			event = state->nextprof;
	}
	return (event);
}