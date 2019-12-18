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
struct freq_qos_request {int dummy; } ;
struct cpufreq_policy {struct freq_qos_request* driver_data; TYPE_1__* freq_table; int /*<<< orphan*/  constraints; } ;
struct TYPE_2__ {int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ_QOS_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cbe_cpufreq_has_pmi ; 
 int freq_qos_add_request (int /*<<< orphan*/ *,struct freq_qos_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct freq_qos_request*) ; 
 struct freq_qos_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

void cbe_cpufreq_pmi_policy_init(struct cpufreq_policy *policy)
{
	struct freq_qos_request *req;
	int ret;

	if (!cbe_cpufreq_has_pmi)
		return;

	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return;

	ret = freq_qos_add_request(&policy->constraints, req, FREQ_QOS_MAX,
				   policy->freq_table[0].frequency);
	if (ret < 0) {
		pr_err("Failed to add freq constraint (%d)\n", ret);
		kfree(req);
		return;
	}

	policy->driver_data = req;
}