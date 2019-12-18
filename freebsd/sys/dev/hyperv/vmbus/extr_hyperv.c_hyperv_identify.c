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
typedef  int u_int ;

/* Variables and functions */
 int CPUID_HV_IFACE_HYPERV ; 
 int CPUID_HV_MSR_HYPERCALL ; 
 unsigned int CPUID_LEAF_HV_FEATURES ; 
 unsigned int CPUID_LEAF_HV_HWFEATURES ; 
 unsigned int CPUID_LEAF_HV_IDENTITY ; 
 unsigned int CPUID_LEAF_HV_INTERFACE ; 
 unsigned int CPUID_LEAF_HV_LIMITS ; 
 unsigned int CPUID_LEAF_HV_MAXLEAF ; 
 unsigned int CPUID_LEAF_HV_RECOMMENDS ; 
 int /*<<< orphan*/  CPUPM_HV_CSTATE (int) ; 
 int CPUPM_HV_CSTATE_MASK ; 
 scalar_t__ VM_GUEST_HV ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  do_cpuid (unsigned int,int*) ; 
 int hyperv_features ; 
 int hyperv_features3 ; 
 int hyperv_pm_features ; 
 int hyperv_recommends ; 
 int hyperv_ver_major ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 scalar_t__ vm_guest ; 

__attribute__((used)) static bool
hyperv_identify(void)
{
	u_int regs[4];
	unsigned int maxleaf;

	if (vm_guest != VM_GUEST_HV)
		return (false);

	do_cpuid(CPUID_LEAF_HV_MAXLEAF, regs);
	maxleaf = regs[0];
	if (maxleaf < CPUID_LEAF_HV_LIMITS)
		return (false);

	do_cpuid(CPUID_LEAF_HV_INTERFACE, regs);
	if (regs[0] != CPUID_HV_IFACE_HYPERV)
		return (false);

	do_cpuid(CPUID_LEAF_HV_FEATURES, regs);
	if ((regs[0] & CPUID_HV_MSR_HYPERCALL) == 0) {
		/*
		 * Hyper-V w/o Hypercall is impossible; someone
		 * is faking Hyper-V.
		 */
		return (false);
	}
	hyperv_features = regs[0];
	hyperv_pm_features = regs[2];
	hyperv_features3 = regs[3];

	do_cpuid(CPUID_LEAF_HV_IDENTITY, regs);
	hyperv_ver_major = regs[1] >> 16;
	printf("Hyper-V Version: %d.%d.%d [SP%d]\n",
	    hyperv_ver_major, regs[1] & 0xffff, regs[0], regs[2]);

	printf("  Features=0x%b\n", hyperv_features,
	    "\020"
	    "\001VPRUNTIME"	/* MSR_HV_VP_RUNTIME */
	    "\002TMREFCNT"	/* MSR_HV_TIME_REF_COUNT */
	    "\003SYNIC"		/* MSRs for SynIC */
	    "\004SYNTM"		/* MSRs for SynTimer */
	    "\005APIC"		/* MSR_HV_{EOI,ICR,TPR} */
	    "\006HYPERCALL"	/* MSR_HV_{GUEST_OS_ID,HYPERCALL} */
	    "\007VPINDEX"	/* MSR_HV_VP_INDEX */
	    "\010RESET"		/* MSR_HV_RESET */
	    "\011STATS"		/* MSR_HV_STATS_ */
	    "\012REFTSC"	/* MSR_HV_REFERENCE_TSC */
	    "\013IDLE"		/* MSR_HV_GUEST_IDLE */
	    "\014TMFREQ"	/* MSR_HV_{TSC,APIC}_FREQUENCY */
	    "\015DEBUG");	/* MSR_HV_SYNTH_DEBUG_ */
	printf("  PM Features=0x%b [C%u]\n",
	    (hyperv_pm_features & ~CPUPM_HV_CSTATE_MASK),
	    "\020"
	    "\005C3HPET",	/* HPET is required for C3 state */
	    CPUPM_HV_CSTATE(hyperv_pm_features));
	printf("  Features3=0x%b\n", hyperv_features3,
	    "\020"
	    "\001MWAIT"		/* MWAIT */
	    "\002DEBUG"		/* guest debug support */
	    "\003PERFMON"	/* performance monitor */
	    "\004PCPUDPE"	/* physical CPU dynamic partition event */
	    "\005XMMHC"		/* hypercall input through XMM regs */
	    "\006IDLE"		/* guest idle support */
	    "\007SLEEP"		/* hypervisor sleep support */
	    "\010NUMA"		/* NUMA distance query support */
	    "\011TMFREQ"	/* timer frequency query (TSC, LAPIC) */
	    "\012SYNCMC"	/* inject synthetic machine checks */
	    "\013CRASH"		/* MSRs for guest crash */
	    "\014DEBUGMSR"	/* MSRs for guest debug */
	    "\015NPIEP"		/* NPIEP */
	    "\016HVDIS");	/* disabling hypervisor */

	do_cpuid(CPUID_LEAF_HV_RECOMMENDS, regs);
	hyperv_recommends = regs[0];
	if (bootverbose)
		printf("  Recommends: %08x %08x\n", regs[0], regs[1]);

	do_cpuid(CPUID_LEAF_HV_LIMITS, regs);
	if (bootverbose) {
		printf("  Limits: Vcpu:%d Lcpu:%d Int:%d\n",
		    regs[0], regs[1], regs[2]);
	}

	if (maxleaf >= CPUID_LEAF_HV_HWFEATURES) {
		do_cpuid(CPUID_LEAF_HV_HWFEATURES, regs);
		if (bootverbose) {
			printf("  HW Features: %08x, AMD: %08x\n",
			    regs[0], regs[3]);
		}
	}

	return (true);
}