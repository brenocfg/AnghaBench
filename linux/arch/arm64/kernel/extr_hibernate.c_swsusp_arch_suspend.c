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
struct sleep_stack_data {int dummy; } ;

/* Variables and functions */
#define  ARM64_SSBD_FORCE_ENABLE 129 
#define  ARM64_SSBD_KERNEL 128 
 int EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ __cpu_suspend_enter (struct sleep_stack_data*) ; 
 int /*<<< orphan*/  __cpu_suspend_exit () ; 
 int /*<<< orphan*/  __hyp_idmap_text_end ; 
 int /*<<< orphan*/  __hyp_idmap_text_start ; 
 int /*<<< orphan*/  __hyp_text_end ; 
 int /*<<< orphan*/  __hyp_text_start ; 
 int /*<<< orphan*/  __idmap_text_end ; 
 int /*<<< orphan*/  __idmap_text_start ; 
 int /*<<< orphan*/  __mmuoff_data_end ; 
 int /*<<< orphan*/  __mmuoff_data_start ; 
 int arm64_get_ssbd_state () ; 
 int /*<<< orphan*/  arm64_set_ssbd_mitigation (int) ; 
 scalar_t__ cpus_are_stuck_in_kernel () ; 
 int /*<<< orphan*/  crash_post_resume () ; 
 int /*<<< orphan*/  crash_prepare_suspend () ; 
 int /*<<< orphan*/  dcache_clean_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ el2_reset_needed () ; 
 scalar_t__ in_suspend ; 
 int /*<<< orphan*/  local_daif_restore (unsigned long) ; 
 unsigned long local_daif_save () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sleep_cpu ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int swsusp_save () ; 

int swsusp_arch_suspend(void)
{
	int ret = 0;
	unsigned long flags;
	struct sleep_stack_data state;

	if (cpus_are_stuck_in_kernel()) {
		pr_err("Can't hibernate: no mechanism to offline secondary CPUs.\n");
		return -EBUSY;
	}

	flags = local_daif_save();

	if (__cpu_suspend_enter(&state)) {
		/* make the crash dump kernel image visible/saveable */
		crash_prepare_suspend();

		sleep_cpu = smp_processor_id();
		ret = swsusp_save();
	} else {
		/* Clean kernel core startup/idle code to PoC*/
		dcache_clean_range(__mmuoff_data_start, __mmuoff_data_end);
		dcache_clean_range(__idmap_text_start, __idmap_text_end);

		/* Clean kvm setup code to PoC? */
		if (el2_reset_needed()) {
			dcache_clean_range(__hyp_idmap_text_start, __hyp_idmap_text_end);
			dcache_clean_range(__hyp_text_start, __hyp_text_end);
		}

		/* make the crash dump kernel image protected again */
		crash_post_resume();

		/*
		 * Tell the hibernation core that we've just restored
		 * the memory
		 */
		in_suspend = 0;

		sleep_cpu = -EINVAL;
		__cpu_suspend_exit();

		/*
		 * Just in case the boot kernel did turn the SSBD
		 * mitigation off behind our back, let's set the state
		 * to what we expect it to be.
		 */
		switch (arm64_get_ssbd_state()) {
		case ARM64_SSBD_FORCE_ENABLE:
		case ARM64_SSBD_KERNEL:
			arm64_set_ssbd_mitigation(true);
		}
	}

	local_daif_restore(flags);

	return ret;
}