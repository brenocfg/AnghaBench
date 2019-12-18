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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_CR_PAT ; 
 int PAT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UC ; 
 int /*<<< orphan*/  UC_MINUS ; 
 int /*<<< orphan*/  WB ; 
 int /*<<< orphan*/  WT ; 
 int /*<<< orphan*/  X86_FEATURE_PAT ; 
 int /*<<< orphan*/  __init_cache_modes (int) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ init_cm_done ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

void init_cache_modes(void)
{
	u64 pat = 0;

	if (init_cm_done)
		return;

	if (boot_cpu_has(X86_FEATURE_PAT)) {
		/*
		 * CPU supports PAT. Set PAT table to be consistent with
		 * PAT MSR. This case supports "nopat" boot option, and
		 * virtual machine environments which support PAT without
		 * MTRRs. In specific, Xen has unique setup to PAT MSR.
		 *
		 * If PAT MSR returns 0, it is considered invalid and emulates
		 * as No PAT.
		 */
		rdmsrl(MSR_IA32_CR_PAT, pat);
	}

	if (!pat) {
		/*
		 * No PAT. Emulate the PAT table that corresponds to the two
		 * cache bits, PWT (Write Through) and PCD (Cache Disable).
		 * This setup is also the same as the BIOS default setup.
		 *
		 * PTE encoding:
		 *
		 *       PCD
		 *       |PWT  PAT
		 *       ||    slot
		 *       00    0    WB : _PAGE_CACHE_MODE_WB
		 *       01    1    WT : _PAGE_CACHE_MODE_WT
		 *       10    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *       11    3    UC : _PAGE_CACHE_MODE_UC
		 *
		 * NOTE: When WC or WP is used, it is redirected to UC- per
		 * the default setup in __cachemode2pte_tbl[].
		 */
		pat = PAT(0, WB) | PAT(1, WT) | PAT(2, UC_MINUS) | PAT(3, UC) |
		      PAT(4, WB) | PAT(5, WT) | PAT(6, UC_MINUS) | PAT(7, UC);
	}

	__init_cache_modes(pat);
}