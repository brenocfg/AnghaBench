#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct freq_qos_request {int dummy; } ;
struct cpufreq_policy {TYPE_1__* freq_table; struct freq_qos_request* driver_data; } ;
struct TYPE_5__ {scalar_t__ type; size_t data1; size_t data2; } ;
typedef  TYPE_2__ pmi_message_t ;
struct TYPE_4__ {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PMI_TYPE_FREQ_CHANGE ; 
 int cbe_node_to_cpu (size_t) ; 
 struct cpufreq_policy* cpufreq_cpu_get (int) ; 
 int /*<<< orphan*/  cpufreq_cpu_put (struct cpufreq_policy*) ; 
 int freq_qos_update_request (struct freq_qos_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,size_t) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void cbe_cpufreq_handle_pmi(pmi_message_t pmi_msg)
{
	struct cpufreq_policy *policy;
	struct freq_qos_request *req;
	u8 node, slow_mode;
	int cpu, ret;

	BUG_ON(pmi_msg.type != PMI_TYPE_FREQ_CHANGE);

	node = pmi_msg.data1;
	slow_mode = pmi_msg.data2;

	cpu = cbe_node_to_cpu(node);

	pr_debug("cbe_handle_pmi: node: %d max_freq: %d\n", node, slow_mode);

	policy = cpufreq_cpu_get(cpu);
	if (!policy) {
		pr_warn("cpufreq policy not found cpu%d\n", cpu);
		return;
	}

	req = policy->driver_data;

	ret = freq_qos_update_request(req,
			policy->freq_table[slow_mode].frequency);
	if (ret < 0)
		pr_warn("Failed to update freq constraint: %d\n", ret);
	else
		pr_debug("limiting node %d to slow mode %d\n", node, slow_mode);

	cpufreq_cpu_put(policy);
}