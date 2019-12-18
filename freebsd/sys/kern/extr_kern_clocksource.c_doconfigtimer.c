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
struct pcpu_state {int /*<<< orphan*/  handle; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 struct pcpu_state* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_HW_LOCK (struct pcpu_state*) ; 
 int /*<<< orphan*/  ET_HW_UNLOCK (struct pcpu_state*) ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_readandclear_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busy ; 
 int /*<<< orphan*/  et_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handleevents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loadtimer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbinuptime () ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  timerstate ; 

__attribute__((used)) static int
doconfigtimer(void)
{
	sbintime_t now;
	struct pcpu_state *state;

	state = DPCPU_PTR(timerstate);
	switch (atomic_load_acq_int(&state->action)) {
	case 1:
		now = sbinuptime();
		ET_HW_LOCK(state);
		loadtimer(now, 1);
		ET_HW_UNLOCK(state);
		state->handle = 0;
		atomic_store_rel_int(&state->action, 0);
		return (1);
	case 2:
		ET_HW_LOCK(state);
		et_stop(timer);
		ET_HW_UNLOCK(state);
		state->handle = 0;
		atomic_store_rel_int(&state->action, 0);
		return (1);
	}
	if (atomic_readandclear_int(&state->handle) && !busy) {
		now = sbinuptime();
		handleevents(now, 0);
		return (1);
	}
	return (0);
}