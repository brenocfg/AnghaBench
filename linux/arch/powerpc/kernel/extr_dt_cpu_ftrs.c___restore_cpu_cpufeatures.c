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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  fscr; int /*<<< orphan*/  hfscr; int /*<<< orphan*/  lpcr_clear; int /*<<< orphan*/  lpcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCR_MASK ; 
 int /*<<< orphan*/  SPRN_FSCR ; 
 int /*<<< orphan*/  SPRN_HFSCR ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  SPRN_LPID ; 
 int /*<<< orphan*/  SPRN_PCR ; 
 scalar_t__ hv_mode ; 
 int /*<<< orphan*/  init_pmu_registers () ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ system_registers ; 

__attribute__((used)) static void __restore_cpu_cpufeatures(void)
{
	u64 lpcr;

	/*
	 * LPCR is restored by the power on engine already. It can be changed
	 * after early init e.g., by radix enable, and we have no unified API
	 * for saving and restoring such SPRs.
	 *
	 * This ->restore hook should really be removed from idle and register
	 * restore moved directly into the idle restore code, because this code
	 * doesn't know how idle is implemented or what it needs restored here.
	 *
	 * The best we can do to accommodate secondary boot and idle restore
	 * for now is "or" LPCR with existing.
	 */
	lpcr = mfspr(SPRN_LPCR);
	lpcr |= system_registers.lpcr;
	lpcr &= ~system_registers.lpcr_clear;
	mtspr(SPRN_LPCR, lpcr);
	if (hv_mode) {
		mtspr(SPRN_LPID, 0);
		mtspr(SPRN_HFSCR, system_registers.hfscr);
		mtspr(SPRN_PCR, PCR_MASK);
	}
	mtspr(SPRN_FSCR, system_registers.fscr);

	if (init_pmu_registers)
		init_pmu_registers();
}