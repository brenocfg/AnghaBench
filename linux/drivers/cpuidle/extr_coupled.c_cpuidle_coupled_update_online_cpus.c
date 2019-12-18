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
struct cpuidle_coupled {int /*<<< orphan*/  online_count; int /*<<< orphan*/  coupled_cpus; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_weight (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuidle_coupled_update_online_cpus(struct cpuidle_coupled *coupled)
{
	cpumask_t cpus;
	cpumask_and(&cpus, cpu_online_mask, &coupled->coupled_cpus);
	coupled->online_count = cpumask_weight(&cpus);
}