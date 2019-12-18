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
struct freq_qos_request {int dummy; } ;
struct cpufreq_policy {struct freq_qos_request* driver_data; } ;

/* Variables and functions */
 scalar_t__ cbe_cpufreq_has_pmi ; 
 int /*<<< orphan*/  freq_qos_remove_request (struct freq_qos_request*) ; 
 int /*<<< orphan*/  kfree (struct freq_qos_request*) ; 

void cbe_cpufreq_pmi_policy_exit(struct cpufreq_policy *policy)
{
	struct freq_qos_request *req = policy->driver_data;

	if (cbe_cpufreq_has_pmi) {
		freq_qos_remove_request(req);
		kfree(req);
	}
}