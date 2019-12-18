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
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  CPUHP_AP_X86_KVM_CLK_ONLINE ; 
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  X86_HYPER_MS_HYPERV ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_hv_tscchange_cb () ; 
 int /*<<< orphan*/  cpufreq_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuhp_remove_state_nocalls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 scalar_t__ hypervisor_is_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_guest_cbs ; 
 int /*<<< orphan*/  kvm_lapic_exit () ; 
 int /*<<< orphan*/  kvm_mmu_module_exit () ; 
 int /*<<< orphan*/ * kvm_x86_ops ; 
 int /*<<< orphan*/  kvmclock_cpufreq_notifier_block ; 
 int /*<<< orphan*/  perf_unregister_guest_info_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvclock_gtod_notifier ; 
 int /*<<< orphan*/  pvclock_gtod_unregister_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shared_msrs ; 
 int /*<<< orphan*/  x86_fpu_cache ; 

void kvm_arch_exit(void)
{
#ifdef CONFIG_X86_64
	if (hypervisor_is_type(X86_HYPER_MS_HYPERV))
		clear_hv_tscchange_cb();
#endif
	kvm_lapic_exit();
	perf_unregister_guest_info_callbacks(&kvm_guest_cbs);

	if (!boot_cpu_has(X86_FEATURE_CONSTANT_TSC))
		cpufreq_unregister_notifier(&kvmclock_cpufreq_notifier_block,
					    CPUFREQ_TRANSITION_NOTIFIER);
	cpuhp_remove_state_nocalls(CPUHP_AP_X86_KVM_CLK_ONLINE);
#ifdef CONFIG_X86_64
	pvclock_gtod_unregister_notifier(&pvclock_gtod_notifier);
#endif
	kvm_x86_ops = NULL;
	kvm_mmu_module_exit();
	free_percpu(shared_msrs);
	kmem_cache_destroy(x86_fpu_cache);
}