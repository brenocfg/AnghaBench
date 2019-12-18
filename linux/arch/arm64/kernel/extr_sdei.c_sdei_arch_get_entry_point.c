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
 int CONDUIT_HVC ; 
 int /*<<< orphan*/  CONFIG_VMAP_STACK ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDEI_EXIT_HVC ; 
 int /*<<< orphan*/  SDEI_EXIT_SMC ; 
 unsigned long TRAMP_VALIAS ; 
 scalar_t__ __entry_tramp_text_start ; 
 scalar_t__ __sdei_asm_entry_trampoline ; 
 scalar_t__ __sdei_asm_handler ; 
 scalar_t__ arm64_kernel_unmapped_at_el0 () ; 
 scalar_t__ init_sdei_stacks () ; 
 scalar_t__ is_hyp_mode_available () ; 
 int /*<<< orphan*/  is_kernel_in_hyp_mode () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sdei_exit_mode ; 

unsigned long sdei_arch_get_entry_point(int conduit)
{
	/*
	 * SDEI works between adjacent exception levels. If we booted at EL1 we
	 * assume a hypervisor is marshalling events. If we booted at EL2 and
	 * dropped to EL1 because we don't support VHE, then we can't support
	 * SDEI.
	 */
	if (is_hyp_mode_available() && !is_kernel_in_hyp_mode()) {
		pr_err("Not supported on this hardware/boot configuration\n");
		return 0;
	}

	if (IS_ENABLED(CONFIG_VMAP_STACK)) {
		if (init_sdei_stacks())
			return 0;
	}

	sdei_exit_mode = (conduit == CONDUIT_HVC) ? SDEI_EXIT_HVC : SDEI_EXIT_SMC;

#ifdef CONFIG_UNMAP_KERNEL_AT_EL0
	if (arm64_kernel_unmapped_at_el0()) {
		unsigned long offset;

		offset = (unsigned long)__sdei_asm_entry_trampoline -
			 (unsigned long)__entry_tramp_text_start;
		return TRAMP_VALIAS + offset;
	} else
#endif /* CONFIG_UNMAP_KERNEL_AT_EL0 */
		return (unsigned long)__sdei_asm_handler;

}