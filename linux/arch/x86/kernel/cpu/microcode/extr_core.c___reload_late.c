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
typedef  enum ucode_state { ____Placeholder_ucode_state } ucode_state ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int UCODE_NFOUND ; 
 int UCODE_OK ; 
 int UCODE_UPDATED ; 
 scalar_t__ __wait_for_cpus (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apply_microcode_local (int*) ; 
 int /*<<< orphan*/  late_cpus_in ; 
 int /*<<< orphan*/  late_cpus_out ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  update_lock ; 

__attribute__((used)) static int __reload_late(void *info)
{
	int cpu = smp_processor_id();
	enum ucode_state err;
	int ret = 0;

	/*
	 * Wait for all CPUs to arrive. A load will not be attempted unless all
	 * CPUs show up.
	 * */
	if (__wait_for_cpus(&late_cpus_in, NSEC_PER_SEC))
		return -1;

	raw_spin_lock(&update_lock);
	apply_microcode_local(&err);
	raw_spin_unlock(&update_lock);

	/* siblings return UCODE_OK because their engine got updated already */
	if (err > UCODE_NFOUND) {
		pr_warn("Error reloading microcode on CPU %d\n", cpu);
		ret = -1;
	} else if (err == UCODE_UPDATED || err == UCODE_OK) {
		ret = 1;
	}

	/*
	 * Increase the wait timeout to a safe value here since we're
	 * serializing the microcode update and that could take a while on a
	 * large number of CPUs. And that is fine as the *actual* timeout will
	 * be determined by the last CPU finished updating and thus cut short.
	 */
	if (__wait_for_cpus(&late_cpus_out, NSEC_PER_SEC * num_online_cpus()))
		panic("Timeout during microcode update!\n");

	return ret;
}