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
struct TYPE_2__ {scalar_t__ max_freq; } ;
struct cpufreq_policy {TYPE_1__ cpuinfo; } ;
typedef  int /*<<< orphan*/  policy ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  CPUHP_AP_X86_KVM_CLK_ONLINE ; 
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_get_policy (struct cpufreq_policy*,int) ; 
 int /*<<< orphan*/  cpufreq_register_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  kvmclock_cpu_down_prep ; 
 int /*<<< orphan*/  kvmclock_cpu_online ; 
 int /*<<< orphan*/  kvmclock_cpufreq_notifier_block ; 
 scalar_t__ max_tsc_khz ; 
 int /*<<< orphan*/  memset (struct cpufreq_policy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 scalar_t__ tsc_khz ; 

__attribute__((used)) static void kvm_timer_init(void)
{
	max_tsc_khz = tsc_khz;

	if (!boot_cpu_has(X86_FEATURE_CONSTANT_TSC)) {
#ifdef CONFIG_CPU_FREQ
		struct cpufreq_policy policy;
		int cpu;

		memset(&policy, 0, sizeof(policy));
		cpu = get_cpu();
		cpufreq_get_policy(&policy, cpu);
		if (policy.cpuinfo.max_freq)
			max_tsc_khz = policy.cpuinfo.max_freq;
		put_cpu();
#endif
		cpufreq_register_notifier(&kvmclock_cpufreq_notifier_block,
					  CPUFREQ_TRANSITION_NOTIFIER);
	}

	cpuhp_setup_state(CPUHP_AP_X86_KVM_CLK_ONLINE, "x86/kvm/clk:online",
			  kvmclock_cpu_online, kvmclock_cpu_down_prep);
}