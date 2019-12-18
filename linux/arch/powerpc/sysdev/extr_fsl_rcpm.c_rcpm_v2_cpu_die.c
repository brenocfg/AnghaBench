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

/* Variables and functions */
 int /*<<< orphan*/  E500_PM_PH20 ; 
 int cpu_first_thread_sibling (int) ; 
 scalar_t__ cpu_is_offline (int) ; 
 int /*<<< orphan*/  qoriq_disable_thread (int) ; 
 int /*<<< orphan*/  rcpm_v2_cpu_enter_state (int,int /*<<< orphan*/ ) ; 
 int threads_per_core ; 

__attribute__((used)) static void rcpm_v2_cpu_die(int cpu)
{
#ifdef CONFIG_PPC64
	int primary;

	if (threads_per_core == 2) {
		primary = cpu_first_thread_sibling(cpu);
		if (cpu_is_offline(primary) && cpu_is_offline(primary + 1)) {
			/* if both threads are offline, put the cpu in PH20 */
			rcpm_v2_cpu_enter_state(cpu, E500_PM_PH20);
		} else {
			/* if only one thread is offline, disable the thread */
			qoriq_disable_thread(cpu);
		}
	}
#endif

	if (threads_per_core == 1)
		rcpm_v2_cpu_enter_state(cpu, E500_PM_PH20);
}