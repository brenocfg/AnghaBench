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
struct kobject {int dummy; } ;
struct cpufreq_policy {int /*<<< orphan*/  kobj_unregister; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct cpufreq_policy* to_policy (struct kobject*) ; 

__attribute__((used)) static void cpufreq_sysfs_release(struct kobject *kobj)
{
	struct cpufreq_policy *policy = to_policy(kobj);
	pr_debug("last reference is dropped\n");
	complete(&policy->kobj_unregister);
}