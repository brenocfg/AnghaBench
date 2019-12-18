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
struct sysinfo_15_1_x {int dummy; } ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_TOPOLOGY ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpus_with_topology ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_cpu_state_mutex ; 
 int /*<<< orphan*/  store_topology (struct sysinfo_15_1_x*) ; 
 struct sysinfo_15_1_x* tl_info ; 
 int /*<<< orphan*/  tl_to_masks (struct sysinfo_15_1_x*) ; 
 int /*<<< orphan*/  topology_update_polarization_simple () ; 
 int /*<<< orphan*/  update_cpu_masks () ; 

__attribute__((used)) static int __arch_update_cpu_topology(void)
{
	struct sysinfo_15_1_x *info = tl_info;
	int rc = 0;

	mutex_lock(&smp_cpu_state_mutex);
	cpumask_clear(&cpus_with_topology);
	if (MACHINE_HAS_TOPOLOGY) {
		rc = 1;
		store_topology(info);
		tl_to_masks(info);
	}
	update_cpu_masks();
	if (!MACHINE_HAS_TOPOLOGY)
		topology_update_polarization_simple();
	mutex_unlock(&smp_cpu_state_mutex);
	return rc;
}