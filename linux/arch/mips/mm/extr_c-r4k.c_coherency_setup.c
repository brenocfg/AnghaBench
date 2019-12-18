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
 int CONF_CM_CMASK ; 
 int /*<<< orphan*/  CONF_CU ; 
#define  CPU_ALCHEMY 135 
#define  CPU_R4000MC 134 
#define  CPU_R4000PC 133 
#define  CPU_R4000SC 132 
#define  CPU_R4400MC 131 
#define  CPU_R4400PC 130 
#define  CPU_R4400SC 129 
#define  PRID_IMP_PR4450 128 
 int _CACHE_SHIFT ; 
 int _page_cachable_default ; 
 int /*<<< orphan*/  au1x00_fixup_config_od () ; 
 int cca ; 
 int /*<<< orphan*/  change_c0_config (int,int) ; 
 int /*<<< orphan*/  clear_c0_config (int /*<<< orphan*/ ) ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  nxp_pr4450_fixup_config () ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int read_c0_config () ; 

__attribute__((used)) static void coherency_setup(void)
{
	if (cca < 0 || cca > 7)
		cca = read_c0_config() & CONF_CM_CMASK;
	_page_cachable_default = cca << _CACHE_SHIFT;

	pr_debug("Using cache attribute %d\n", cca);
	change_c0_config(CONF_CM_CMASK, cca);

	/*
	 * c0_status.cu=0 specifies that updates by the sc instruction use
	 * the coherency mode specified by the TLB; 1 means cachable
	 * coherent update on write will be used.  Not all processors have
	 * this bit and; some wire it to zero, others like Toshiba had the
	 * silly idea of putting something else there ...
	 */
	switch (current_cpu_type()) {
	case CPU_R4000PC:
	case CPU_R4000SC:
	case CPU_R4000MC:
	case CPU_R4400PC:
	case CPU_R4400SC:
	case CPU_R4400MC:
		clear_c0_config(CONF_CU);
		break;
	/*
	 * We need to catch the early Alchemy SOCs with
	 * the write-only co_config.od bit and set it back to one on:
	 * Au1000 rev DA, HA, HB;  Au1100 AB, BA, BC, Au1500 AB
	 */
	case CPU_ALCHEMY:
		au1x00_fixup_config_od();
		break;

	case PRID_IMP_PR4450:
		nxp_pr4450_fixup_config();
		break;
	}
}