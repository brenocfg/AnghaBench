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
struct cpuinfo_x86 {scalar_t__ x86_vendor; int x86; int x86_model; } ;

/* Variables and functions */
 int PAT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UC ; 
 int /*<<< orphan*/  UC_MINUS ; 
 int /*<<< orphan*/  WB ; 
 int /*<<< orphan*/  WC ; 
 int /*<<< orphan*/  WP ; 
 int /*<<< orphan*/  WT ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 int boot_cpu_done ; 
 int /*<<< orphan*/  pat_ap_init (int) ; 
 int /*<<< orphan*/  pat_bsp_init (int) ; 
 scalar_t__ pat_disabled ; 

void pat_init(void)
{
	u64 pat;
	struct cpuinfo_x86 *c = &boot_cpu_data;

	if (pat_disabled)
		return;

	if ((c->x86_vendor == X86_VENDOR_INTEL) &&
	    (((c->x86 == 0x6) && (c->x86_model <= 0xd)) ||
	     ((c->x86 == 0xf) && (c->x86_model <= 0x6)))) {
		/*
		 * PAT support with the lower four entries. Intel Pentium 2,
		 * 3, M, and 4 are affected by PAT errata, which makes the
		 * upper four entries unusable. To be on the safe side, we don't
		 * use those.
		 *
		 *  PTE encoding:
		 *      PAT
		 *      |PCD
		 *      ||PWT  PAT
		 *      |||    slot
		 *      000    0    WB : _PAGE_CACHE_MODE_WB
		 *      001    1    WC : _PAGE_CACHE_MODE_WC
		 *      010    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *      011    3    UC : _PAGE_CACHE_MODE_UC
		 * PAT bit unused
		 *
		 * NOTE: When WT or WP is used, it is redirected to UC- per
		 * the default setup in __cachemode2pte_tbl[].
		 */
		pat = PAT(0, WB) | PAT(1, WC) | PAT(2, UC_MINUS) | PAT(3, UC) |
		      PAT(4, WB) | PAT(5, WC) | PAT(6, UC_MINUS) | PAT(7, UC);
	} else {
		/*
		 * Full PAT support.  We put WT in slot 7 to improve
		 * robustness in the presence of errata that might cause
		 * the high PAT bit to be ignored.  This way, a buggy slot 7
		 * access will hit slot 3, and slot 3 is UC, so at worst
		 * we lose performance without causing a correctness issue.
		 * Pentium 4 erratum N46 is an example for such an erratum,
		 * although we try not to use PAT at all on affected CPUs.
		 *
		 *  PTE encoding:
		 *      PAT
		 *      |PCD
		 *      ||PWT  PAT
		 *      |||    slot
		 *      000    0    WB : _PAGE_CACHE_MODE_WB
		 *      001    1    WC : _PAGE_CACHE_MODE_WC
		 *      010    2    UC-: _PAGE_CACHE_MODE_UC_MINUS
		 *      011    3    UC : _PAGE_CACHE_MODE_UC
		 *      100    4    WB : Reserved
		 *      101    5    WP : _PAGE_CACHE_MODE_WP
		 *      110    6    UC-: Reserved
		 *      111    7    WT : _PAGE_CACHE_MODE_WT
		 *
		 * The reserved slots are unused, but mapped to their
		 * corresponding types in the presence of PAT errata.
		 */
		pat = PAT(0, WB) | PAT(1, WC) | PAT(2, UC_MINUS) | PAT(3, UC) |
		      PAT(4, WB) | PAT(5, WP) | PAT(6, UC_MINUS) | PAT(7, WT);
	}

	if (!boot_cpu_done) {
		pat_bsp_init(pat);
		boot_cpu_done = true;
	} else {
		pat_ap_init(pat);
	}
}