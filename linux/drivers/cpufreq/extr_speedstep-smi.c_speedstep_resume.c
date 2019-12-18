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
struct cpufreq_policy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 
 int speedstep_smi_ownership () ; 

__attribute__((used)) static int speedstep_resume(struct cpufreq_policy *policy)
{
	int result = speedstep_smi_ownership();

	if (result)
		pr_debug("fails in re-acquiring ownership of a SMI interface.\n");

	return result;
}