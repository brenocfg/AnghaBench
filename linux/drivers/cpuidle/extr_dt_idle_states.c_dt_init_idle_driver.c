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
struct of_device_id {int dummy; } ;
struct device_node {int dummy; } ;
struct cpuidle_state {int dummy; } ;
struct cpuidle_driver {unsigned int state_count; struct cpuidle_state* states; int /*<<< orphan*/  cpumask; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 unsigned int CPUIDLE_STATE_MAX ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/ * cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  idle_state_valid (struct device_node*,int,int /*<<< orphan*/  const*) ; 
 int init_state_node (struct cpuidle_state*,struct of_device_id const*,struct device_node*) ; 
 struct device_node* of_cpu_device_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct of_device_id* of_match_node (struct of_device_id const*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

int dt_init_idle_driver(struct cpuidle_driver *drv,
			const struct of_device_id *matches,
			unsigned int start_idx)
{
	struct cpuidle_state *idle_state;
	struct device_node *state_node, *cpu_node;
	const struct of_device_id *match_id;
	int i, err = 0;
	const cpumask_t *cpumask;
	unsigned int state_idx = start_idx;

	if (state_idx >= CPUIDLE_STATE_MAX)
		return -EINVAL;
	/*
	 * We get the idle states for the first logical cpu in the
	 * driver mask (or cpu_possible_mask if the driver cpumask is not set)
	 * and we check through idle_state_valid() if they are uniform
	 * across CPUs, otherwise we hit a firmware misconfiguration.
	 */
	cpumask = drv->cpumask ? : cpu_possible_mask;
	cpu_node = of_cpu_device_node_get(cpumask_first(cpumask));

	for (i = 0; ; i++) {
		state_node = of_parse_phandle(cpu_node, "cpu-idle-states", i);
		if (!state_node)
			break;

		match_id = of_match_node(matches, state_node);
		if (!match_id) {
			err = -ENODEV;
			break;
		}

		if (!of_device_is_available(state_node)) {
			of_node_put(state_node);
			continue;
		}

		if (!idle_state_valid(state_node, i, cpumask)) {
			pr_warn("%pOF idle state not valid, bailing out\n",
				state_node);
			err = -EINVAL;
			break;
		}

		if (state_idx == CPUIDLE_STATE_MAX) {
			pr_warn("State index reached static CPU idle driver states array size\n");
			break;
		}

		idle_state = &drv->states[state_idx++];
		err = init_state_node(idle_state, match_id, state_node);
		if (err) {
			pr_err("Parsing idle state node %pOF failed with err %d\n",
			       state_node, err);
			err = -EINVAL;
			break;
		}
		of_node_put(state_node);
	}

	of_node_put(state_node);
	of_node_put(cpu_node);
	if (err)
		return err;
	/*
	 * Update the driver state count only if some valid DT idle states
	 * were detected
	 */
	if (i)
		drv->state_count = state_idx;

	/*
	 * Return the number of present and valid DT idle states, which can
	 * also be 0 on platforms with missing DT idle states or legacy DT
	 * configuration predating the DT idle states bindings.
	 */
	return i;
}