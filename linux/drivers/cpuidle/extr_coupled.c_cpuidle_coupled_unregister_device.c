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
struct cpuidle_device {struct cpuidle_coupled* coupled; int /*<<< orphan*/  coupled_cpus; } ;
struct cpuidle_coupled {scalar_t__ refcnt; } ;

/* Variables and functions */
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cpuidle_coupled*) ; 

void cpuidle_coupled_unregister_device(struct cpuidle_device *dev)
{
	struct cpuidle_coupled *coupled = dev->coupled;

	if (cpumask_empty(&dev->coupled_cpus))
		return;

	if (--coupled->refcnt)
		kfree(coupled);
	dev->coupled = NULL;
}