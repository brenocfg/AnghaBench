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
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int dummy; } ;
struct pcpu_state {int nexthard; int nextstat; int nextprof; int nextcallopt; int nextcall; int nextevent; scalar_t__ idle; } ;
typedef  int sbintime_t ;
struct TYPE_4__ {struct trapframe* td_intr_frame; } ;
struct TYPE_3__ {int et_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int ET_FLAGS_PERCPU ; 
 int /*<<< orphan*/  ET_HW_LOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  ET_HW_UNLOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  KTR_SPARE2 ; 
 int SBT_MAX ; 
 int /*<<< orphan*/  TRAPF_PC (struct trapframe*) ; 
 int TRAPF_USERMODE (struct trapframe*) ; 
 int /*<<< orphan*/  busy ; 
 int /*<<< orphan*/  callout_process (int) ; 
 int /*<<< orphan*/  curcpu ; 
 TYPE_2__* curthread ; 
 int getnextcpuevent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardclock (int,int) ; 
 int /*<<< orphan*/  hardclocktime ; 
 int /*<<< orphan*/  loadtimer (int,int) ; 
 int /*<<< orphan*/  profclock (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ profiling ; 
 int profperiod ; 
 int /*<<< orphan*/  statclock (int,int) ; 
 int statperiod ; 
 int tick_sbt ; 
 TYPE_1__* timer ; 
 int /*<<< orphan*/  timerstate ; 

__attribute__((used)) static int
handleevents(sbintime_t now, int fake)
{
	sbintime_t t, *hct;
	struct trapframe *frame;
	struct pcpu_state *state;
	int usermode;
	int done, runs;

	CTR3(KTR_SPARE2, "handle at %d:  now  %d.%08x",
	    curcpu, (int)(now >> 32), (u_int)(now & 0xffffffff));
	done = 0;
	if (fake) {
		frame = NULL;
		usermode = 0;
	} else {
		frame = curthread->td_intr_frame;
		usermode = TRAPF_USERMODE(frame);
	}

	state = DPCPU_PTR(timerstate);

	runs = 0;
	while (now >= state->nexthard) {
		state->nexthard += tick_sbt;
		runs++;
	}
	if (runs) {
		hct = DPCPU_PTR(hardclocktime);
		*hct = state->nexthard - tick_sbt;
		if (fake < 2) {
			hardclock(runs, usermode);
			done = 1;
		}
	}
	runs = 0;
	while (now >= state->nextstat) {
		state->nextstat += statperiod;
		runs++;
	}
	if (runs && fake < 2) {
		statclock(runs, usermode);
		done = 1;
	}
	if (profiling) {
		runs = 0;
		while (now >= state->nextprof) {
			state->nextprof += profperiod;
			runs++;
		}
		if (runs && !fake) {
			profclock(runs, usermode, TRAPF_PC(frame));
			done = 1;
		}
	} else
		state->nextprof = state->nextstat;
	if (now >= state->nextcallopt || now >= state->nextcall) {
		state->nextcall = state->nextcallopt = SBT_MAX;
		callout_process(now);
	}

	t = getnextcpuevent(0);
	ET_HW_LOCK(state);
	if (!busy) {
		state->idle = 0;
		state->nextevent = t;
		loadtimer(now, (fake == 2) &&
		    (timer->et_flags & ET_FLAGS_PERCPU));
	}
	ET_HW_UNLOCK(state);
	return (done);
}