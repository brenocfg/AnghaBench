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
typedef  int uint32_t ;

/* Variables and functions */
 int ARCHITECTURE_NOT_PRESENT ; 
 int CPU_ID_ARM1176JZS ; 
 int CPU_ID_ARM926EJS ; 
 int CPU_ID_ARM_88SV581X_V7 ; 
#define  CPU_ID_CORTEXA12 137 
#define  CPU_ID_CORTEXA15 136 
#define  CPU_ID_CORTEXA5 135 
#define  CPU_ID_CORTEXA53 134 
#define  CPU_ID_CORTEXA57 133 
#define  CPU_ID_CORTEXA7 132 
#define  CPU_ID_CORTEXA72 131 
#define  CPU_ID_CORTEXA8 130 
#define  CPU_ID_CORTEXA9 129 
 int CPU_ID_CPU_MASK ; 
#define  CPU_ID_KRAIT300 128 
 int CPU_ID_MV88FR131 ; 
 int CPU_ID_MV88FR571_41 ; 
 int CPU_ID_MV88FR571_VD ; 
 int CPU_ID_MV88SV581X_V7 ; 
 int CPU_ID_MV88SV584X_V7 ; 
 int CPU_ID_SCHEME_MASK ; 
 int MV_BTB_DISABLE ; 
 int MV_DC_STREAM_ENABLE ; 
 int MV_L2_ENABLE ; 
 int MV_L2_PREFETCH_DISABLE ; 
 int MV_WA_ENABLE ; 
 int /*<<< orphan*/  arm1176_cpufuncs ; 
 int /*<<< orphan*/  arm_dcache_align_mask ; 
 int /*<<< orphan*/  armv5_ec_cpufuncs ; 
 int /*<<< orphan*/  cortexa_cpufuncs ; 
 int cp15_midr_get () ; 
 int /*<<< orphan*/  cpufuncs ; 
 int cputype ; 
 int /*<<< orphan*/  get_cachetype_cp15 () ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  pj4bv7_cpufuncs ; 
 int /*<<< orphan*/  pmap_pte_init_generic () ; 
 int /*<<< orphan*/  sheeva_control_ext (int,int) ; 
 int /*<<< orphan*/  sheeva_cpufuncs ; 
 int /*<<< orphan*/  uma_set_align (int /*<<< orphan*/ ) ; 

int
set_cpufuncs(void)
{
	cputype = cp15_midr_get();
	cputype &= CPU_ID_CPU_MASK;

#if defined(CPU_ARM9E)
	if (cputype == CPU_ID_MV88FR131 || cputype == CPU_ID_MV88FR571_VD ||
	    cputype == CPU_ID_MV88FR571_41) {
		uint32_t sheeva_ctrl;

		sheeva_ctrl = (MV_DC_STREAM_ENABLE | MV_BTB_DISABLE |
		    MV_L2_ENABLE);
		/*
		 * Workaround for Marvell MV78100 CPU: Cache prefetch
		 * mechanism may affect the cache coherency validity,
		 * so it needs to be disabled.
		 *
		 * Refer to errata document MV-S501058-00C.pdf (p. 3.1
		 * L2 Prefetching Mechanism) for details.
		 */
		if (cputype == CPU_ID_MV88FR571_VD ||
		    cputype == CPU_ID_MV88FR571_41)
			sheeva_ctrl |= MV_L2_PREFETCH_DISABLE;

		sheeva_control_ext(0xffffffff & ~MV_WA_ENABLE, sheeva_ctrl);

		cpufuncs = sheeva_cpufuncs;
		get_cachetype_cp15();
		pmap_pte_init_generic();
		goto out;
	} else if (cputype == CPU_ID_ARM926EJS) {
		cpufuncs = armv5_ec_cpufuncs;
		get_cachetype_cp15();
		pmap_pte_init_generic();
		goto out;
	}
#endif /* CPU_ARM9E */
#if defined(CPU_ARM1176)
	if (cputype == CPU_ID_ARM1176JZS) {
		cpufuncs = arm1176_cpufuncs;
		get_cachetype_cp15();
		goto out;
	}
#endif /* CPU_ARM1176 */
#if defined(CPU_CORTEXA) || defined(CPU_KRAIT)
	switch(cputype & CPU_ID_SCHEME_MASK) {
	case CPU_ID_CORTEXA5:
	case CPU_ID_CORTEXA7:
	case CPU_ID_CORTEXA8:
	case CPU_ID_CORTEXA9:
	case CPU_ID_CORTEXA12:
	case CPU_ID_CORTEXA15:
	case CPU_ID_CORTEXA53:
	case CPU_ID_CORTEXA57:
	case CPU_ID_CORTEXA72:
	case CPU_ID_KRAIT300:
		cpufuncs = cortexa_cpufuncs;
		get_cachetype_cp15();
		goto out;
	default:
		break;
	}
#endif /* CPU_CORTEXA || CPU_KRAIT */

#if defined(CPU_MV_PJ4B)
	if (cputype == CPU_ID_MV88SV581X_V7 ||
	    cputype == CPU_ID_MV88SV584X_V7 ||
	    cputype == CPU_ID_ARM_88SV581X_V7) {
		cpufuncs = pj4bv7_cpufuncs;
		get_cachetype_cp15();
		goto out;
	}
#endif /* CPU_MV_PJ4B */

	/*
	 * Bzzzz. And the answer was ...
	 */
	panic("No support for this CPU type (%08x) in kernel", cputype);
	return(ARCHITECTURE_NOT_PRESENT);
out:
	uma_set_align(arm_dcache_align_mask);
	return (0);
}