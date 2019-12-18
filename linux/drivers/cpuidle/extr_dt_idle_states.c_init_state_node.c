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
typedef  scalar_t__ u32 ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct device_node {char* name; } ;
struct cpuidle_state {int /*<<< orphan*/  desc; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; scalar_t__ target_residency; scalar_t__ exit_latency; int /*<<< orphan*/  enter_s2idle; int /*<<< orphan*/  enter; } ;

/* Variables and functions */
 scalar_t__ CPUIDLE_DESC_LEN ; 
 int /*<<< orphan*/  CPUIDLE_FLAG_TIMER_STOP ; 
 scalar_t__ CPUIDLE_NAME_LEN ; 
 int EINVAL ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct device_node*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static int init_state_node(struct cpuidle_state *idle_state,
			   const struct of_device_id *match_id,
			   struct device_node *state_node)
{
	int err;
	const char *desc;

	/*
	 * CPUidle drivers are expected to initialize the const void *data
	 * pointer of the passed in struct of_device_id array to the idle
	 * state enter function.
	 */
	idle_state->enter = match_id->data;
	/*
	 * Since this is not a "coupled" state, it's safe to assume interrupts
	 * won't be enabled when it exits allowing the tick to be frozen
	 * safely. So enter() can be also enter_s2idle() callback.
	 */
	idle_state->enter_s2idle = match_id->data;

	err = of_property_read_u32(state_node, "wakeup-latency-us",
				   &idle_state->exit_latency);
	if (err) {
		u32 entry_latency, exit_latency;

		err = of_property_read_u32(state_node, "entry-latency-us",
					   &entry_latency);
		if (err) {
			pr_debug(" * %pOF missing entry-latency-us property\n",
				 state_node);
			return -EINVAL;
		}

		err = of_property_read_u32(state_node, "exit-latency-us",
					   &exit_latency);
		if (err) {
			pr_debug(" * %pOF missing exit-latency-us property\n",
				 state_node);
			return -EINVAL;
		}
		/*
		 * If wakeup-latency-us is missing, default to entry+exit
		 * latencies as defined in idle states bindings
		 */
		idle_state->exit_latency = entry_latency + exit_latency;
	}

	err = of_property_read_u32(state_node, "min-residency-us",
				   &idle_state->target_residency);
	if (err) {
		pr_debug(" * %pOF missing min-residency-us property\n",
			     state_node);
		return -EINVAL;
	}

	err = of_property_read_string(state_node, "idle-state-name", &desc);
	if (err)
		desc = state_node->name;

	idle_state->flags = 0;
	if (of_property_read_bool(state_node, "local-timer-stop"))
		idle_state->flags |= CPUIDLE_FLAG_TIMER_STOP;
	/*
	 * TODO:
	 *	replace with kstrdup and pointer assignment when name
	 *	and desc become string pointers
	 */
	strncpy(idle_state->name, state_node->name, CPUIDLE_NAME_LEN - 1);
	strncpy(idle_state->desc, desc, CPUIDLE_DESC_LEN - 1);
	return 0;
}