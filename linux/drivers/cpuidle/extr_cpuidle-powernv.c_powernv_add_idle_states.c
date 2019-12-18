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
typedef  int u32 ;
struct pnv_idle_states_t {int flags; scalar_t__ latency_ns; scalar_t__ residency_ns; char* name; int /*<<< orphan*/  psscr_mask; int /*<<< orphan*/  psscr_val; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUIDLE_FLAG_NONE ; 
 int /*<<< orphan*/  CPUIDLE_FLAG_TIMER_STOP ; 
 int CPUIDLE_STATE_MAX ; 
 unsigned int DIV_ROUND_UP (scalar_t__,int) ; 
 int OPAL_PM_NAP_ENABLED ; 
 int OPAL_PM_SLEEP_ENABLED ; 
 int OPAL_PM_SLEEP_ENABLED_ER1 ; 
 int OPAL_PM_STOP_INST_DEEP ; 
 int OPAL_PM_STOP_INST_FAST ; 
 int OPAL_PM_TIMEBASE_STOP ; 
 scalar_t__ POWERNV_THRESHOLD_LATENCY_NS ; 
 int /*<<< orphan*/  add_powernv_state (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fastsleep_loop ; 
 int /*<<< orphan*/  nap_loop ; 
 int nr_pnv_idle_states ; 
 int pnv_get_supported_cpuidle_states () ; 
 struct pnv_idle_states_t* pnv_idle_states ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  stop_loop ; 

__attribute__((used)) static int powernv_add_idle_states(void)
{
	int nr_idle_states = 1; /* Snooze */
	int dt_idle_states;
	u32 has_stop_states = 0;
	int i;
	u32 supported_flags = pnv_get_supported_cpuidle_states();


	/* Currently we have snooze statically defined */
	if (nr_pnv_idle_states <= 0) {
		pr_warn("cpuidle-powernv : Only Snooze is available\n");
		goto out;
	}

	/* TODO: Count only states which are eligible for cpuidle */
	dt_idle_states = nr_pnv_idle_states;

	/*
	 * Since snooze is used as first idle state, max idle states allowed is
	 * CPUIDLE_STATE_MAX -1
	 */
	if (nr_pnv_idle_states > CPUIDLE_STATE_MAX - 1) {
		pr_warn("cpuidle-powernv: discovered idle states more than allowed");
		dt_idle_states = CPUIDLE_STATE_MAX - 1;
	}

	/*
	 * If the idle states use stop instruction, probe for psscr values
	 * and psscr mask which are necessary to specify required stop level.
	 */
	has_stop_states = (pnv_idle_states[0].flags &
			   (OPAL_PM_STOP_INST_FAST | OPAL_PM_STOP_INST_DEEP));

	for (i = 0; i < dt_idle_states; i++) {
		unsigned int exit_latency, target_residency;
		bool stops_timebase = false;
		struct pnv_idle_states_t *state = &pnv_idle_states[i];

		/*
		 * Skip the platform idle state whose flag isn't in
		 * the supported_cpuidle_states flag mask.
		 */
		if ((state->flags & supported_flags) != state->flags)
			continue;
		/*
		 * If an idle state has exit latency beyond
		 * POWERNV_THRESHOLD_LATENCY_NS then don't use it
		 * in cpu-idle.
		 */
		if (state->latency_ns > POWERNV_THRESHOLD_LATENCY_NS)
			continue;
		/*
		 * Firmware passes residency and latency values in ns.
		 * cpuidle expects it in us.
		 */
		exit_latency = DIV_ROUND_UP(state->latency_ns, 1000);
		target_residency = DIV_ROUND_UP(state->residency_ns, 1000);

		if (has_stop_states && !(state->valid))
				continue;

		if (state->flags & OPAL_PM_TIMEBASE_STOP)
			stops_timebase = true;

		if (state->flags & OPAL_PM_NAP_ENABLED) {
			/* Add NAP state */
			add_powernv_state(nr_idle_states, "Nap",
					  CPUIDLE_FLAG_NONE, nap_loop,
					  target_residency, exit_latency, 0, 0);
		} else if (has_stop_states && !stops_timebase) {
			add_powernv_state(nr_idle_states, state->name,
					  CPUIDLE_FLAG_NONE, stop_loop,
					  target_residency, exit_latency,
					  state->psscr_val,
					  state->psscr_mask);
		}

		/*
		 * All cpuidle states with CPUIDLE_FLAG_TIMER_STOP set must come
		 * within this config dependency check.
		 */
#ifdef CONFIG_TICK_ONESHOT
		else if (state->flags & OPAL_PM_SLEEP_ENABLED ||
			 state->flags & OPAL_PM_SLEEP_ENABLED_ER1) {
			/* Add FASTSLEEP state */
			add_powernv_state(nr_idle_states, "FastSleep",
					  CPUIDLE_FLAG_TIMER_STOP,
					  fastsleep_loop,
					  target_residency, exit_latency, 0, 0);
		} else if (has_stop_states && stops_timebase) {
			add_powernv_state(nr_idle_states, state->name,
					  CPUIDLE_FLAG_TIMER_STOP, stop_loop,
					  target_residency, exit_latency,
					  state->psscr_val,
					  state->psscr_mask);
		}
#endif
		else
			continue;
		nr_idle_states++;
	}
out:
	return nr_idle_states;
}