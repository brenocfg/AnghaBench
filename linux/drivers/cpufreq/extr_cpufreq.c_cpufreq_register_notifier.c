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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CPUFREQ_POLICY_NOTIFIER 129 
#define  CPUFREQ_TRANSITION_NOTIFIER 128 
 int EBUSY ; 
 int EINVAL ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 scalar_t__ cpufreq_disabled () ; 
 int /*<<< orphan*/  cpufreq_fast_switch_count ; 
 int /*<<< orphan*/  cpufreq_fast_switch_lock ; 
 int /*<<< orphan*/  cpufreq_policy_notifier_list ; 
 int /*<<< orphan*/  cpufreq_transition_notifier_list ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int srcu_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

int cpufreq_register_notifier(struct notifier_block *nb, unsigned int list)
{
	int ret;

	if (cpufreq_disabled())
		return -EINVAL;

	switch (list) {
	case CPUFREQ_TRANSITION_NOTIFIER:
		mutex_lock(&cpufreq_fast_switch_lock);

		if (cpufreq_fast_switch_count > 0) {
			mutex_unlock(&cpufreq_fast_switch_lock);
			return -EBUSY;
		}
		ret = srcu_notifier_chain_register(
				&cpufreq_transition_notifier_list, nb);
		if (!ret)
			cpufreq_fast_switch_count--;

		mutex_unlock(&cpufreq_fast_switch_lock);
		break;
	case CPUFREQ_POLICY_NOTIFIER:
		ret = blocking_notifier_chain_register(
				&cpufreq_policy_notifier_list, nb);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}