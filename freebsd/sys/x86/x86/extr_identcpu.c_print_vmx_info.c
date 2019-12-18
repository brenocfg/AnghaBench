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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int IA32_FEATURE_CONTROL_VMX_EN ; 
 int /*<<< orphan*/  MSR_IA32_FEATURE_CONTROL ; 
 int /*<<< orphan*/  MSR_VMX_BASIC ; 
 int /*<<< orphan*/  MSR_VMX_ENTRY_CTLS ; 
 int /*<<< orphan*/  MSR_VMX_EPT_VPID_CAP ; 
 int /*<<< orphan*/  MSR_VMX_EXIT_CTLS ; 
 int /*<<< orphan*/  MSR_VMX_PINBASED_CTLS ; 
 int /*<<< orphan*/  MSR_VMX_PROCBASED_CTLS ; 
 int /*<<< orphan*/  MSR_VMX_PROCBASED_CTLS2 ; 
 int /*<<< orphan*/  MSR_VMX_TRUE_ENTRY_CTLS ; 
 int /*<<< orphan*/  MSR_VMX_TRUE_EXIT_CTLS ; 
 int /*<<< orphan*/  MSR_VMX_TRUE_PINBASED_CTLS ; 
 int /*<<< orphan*/  MSR_VMX_TRUE_PROCBASED_CTLS ; 
 int PINBASED_POSTED_INTERRUPT ; 
 int PROCBASED2_APIC_REGISTER_VIRTUALIZATION ; 
 int PROCBASED2_ENABLE_EPT ; 
 int PROCBASED2_ENABLE_VPID ; 
 int PROCBASED2_UNRESTRICTED_GUEST ; 
 int PROCBASED2_VIRTUALIZE_APIC_ACCESSES ; 
 int PROCBASED2_VIRTUALIZE_X2APIC_MODE ; 
 int PROCBASED2_VIRTUAL_INTERRUPT_DELIVERY ; 
 int PROCBASED_HLT_EXITING ; 
 int PROCBASED_MTF ; 
 int PROCBASED_PAUSE_EXITING ; 
 int PROCBASED_SECONDARY_CONTROLS ; 
 int PROCBASED_USE_TPR_SHADOW ; 
 int VM_ENTRY_LOAD_PAT ; 
 int VM_EXIT_LOAD_PAT ; 
 int VM_EXIT_SAVE_PAT ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int vmx_settable (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_vmx_info(void)
{
	uint64_t basic, msr;
	uint32_t entry, exit, mask, pin, proc, proc2;
	int comma;

	printf("\n  VT-x: ");
	msr = rdmsr(MSR_IA32_FEATURE_CONTROL);
	if (!(msr & IA32_FEATURE_CONTROL_VMX_EN))
		printf("(disabled in BIOS) ");
	basic = rdmsr(MSR_VMX_BASIC);
	pin = vmx_settable(basic, MSR_VMX_PINBASED_CTLS,
	    MSR_VMX_TRUE_PINBASED_CTLS);
	proc = vmx_settable(basic, MSR_VMX_PROCBASED_CTLS,
	    MSR_VMX_TRUE_PROCBASED_CTLS);
	if (proc & PROCBASED_SECONDARY_CONTROLS)
		proc2 = vmx_settable(basic, MSR_VMX_PROCBASED_CTLS2,
		    MSR_VMX_PROCBASED_CTLS2);
	else
		proc2 = 0;
	exit = vmx_settable(basic, MSR_VMX_EXIT_CTLS, MSR_VMX_TRUE_EXIT_CTLS);
	entry = vmx_settable(basic, MSR_VMX_ENTRY_CTLS, MSR_VMX_TRUE_ENTRY_CTLS);

	if (!bootverbose) {
		comma = 0;
		if (exit & VM_EXIT_SAVE_PAT && exit & VM_EXIT_LOAD_PAT &&
		    entry & VM_ENTRY_LOAD_PAT) {
			printf("%sPAT", comma ? "," : "");
			comma = 1;
		}
		if (proc & PROCBASED_HLT_EXITING) {
			printf("%sHLT", comma ? "," : "");
			comma = 1;
		}
		if (proc & PROCBASED_MTF) {
			printf("%sMTF", comma ? "," : "");
			comma = 1;
		}
		if (proc & PROCBASED_PAUSE_EXITING) {
			printf("%sPAUSE", comma ? "," : "");
			comma = 1;
		}
		if (proc2 & PROCBASED2_ENABLE_EPT) {
			printf("%sEPT", comma ? "," : "");
			comma = 1;
		}
		if (proc2 & PROCBASED2_UNRESTRICTED_GUEST) {
			printf("%sUG", comma ? "," : "");
			comma = 1;
		}
		if (proc2 & PROCBASED2_ENABLE_VPID) {
			printf("%sVPID", comma ? "," : "");
			comma = 1;
		}
		if (proc & PROCBASED_USE_TPR_SHADOW &&
		    proc2 & PROCBASED2_VIRTUALIZE_APIC_ACCESSES &&
		    proc2 & PROCBASED2_VIRTUALIZE_X2APIC_MODE &&
		    proc2 & PROCBASED2_APIC_REGISTER_VIRTUALIZATION &&
		    proc2 & PROCBASED2_VIRTUAL_INTERRUPT_DELIVERY) {
			printf("%sVID", comma ? "," : "");
			comma = 1;
			if (pin & PINBASED_POSTED_INTERRUPT)
				printf(",PostIntr");
		}
		return;
	}

	mask = basic >> 32;
	printf("Basic Features=0x%b", mask,
	"\020"
	"\02132PA"		/* 32-bit physical addresses */
	"\022SMM"		/* SMM dual-monitor */
	"\027INS/OUTS"		/* VM-exit info for INS and OUTS */
	"\030TRUE"		/* TRUE_CTLS MSRs */
	);
	printf("\n        Pin-Based Controls=0x%b", pin,
	"\020"
	"\001ExtINT"		/* External-interrupt exiting */
	"\004NMI"		/* NMI exiting */
	"\006VNMI"		/* Virtual NMIs */
	"\007PreTmr"		/* Activate VMX-preemption timer */
	"\010PostIntr"		/* Process posted interrupts */
	);
	printf("\n        Primary Processor Controls=0x%b", proc,
	"\020"
	"\003INTWIN"		/* Interrupt-window exiting */
	"\004TSCOff"		/* Use TSC offsetting */
	"\010HLT"		/* HLT exiting */
	"\012INVLPG"		/* INVLPG exiting */
	"\013MWAIT"		/* MWAIT exiting */
	"\014RDPMC"		/* RDPMC exiting */
	"\015RDTSC"		/* RDTSC exiting */
	"\020CR3-LD"		/* CR3-load exiting */
	"\021CR3-ST"		/* CR3-store exiting */
	"\024CR8-LD"		/* CR8-load exiting */
	"\025CR8-ST"		/* CR8-store exiting */
	"\026TPR"		/* Use TPR shadow */
	"\027NMIWIN"		/* NMI-window exiting */
	"\030MOV-DR"		/* MOV-DR exiting */
	"\031IO"		/* Unconditional I/O exiting */
	"\032IOmap"		/* Use I/O bitmaps */
	"\034MTF"		/* Monitor trap flag */
	"\035MSRmap"		/* Use MSR bitmaps */
	"\036MONITOR"		/* MONITOR exiting */
	"\037PAUSE"		/* PAUSE exiting */
	);
	if (proc & PROCBASED_SECONDARY_CONTROLS)
		printf("\n        Secondary Processor Controls=0x%b", proc2,
		"\020"
		"\001APIC"		/* Virtualize APIC accesses */
		"\002EPT"		/* Enable EPT */
		"\003DT"		/* Descriptor-table exiting */
		"\004RDTSCP"		/* Enable RDTSCP */
		"\005x2APIC"		/* Virtualize x2APIC mode */
		"\006VPID"		/* Enable VPID */
		"\007WBINVD"		/* WBINVD exiting */
		"\010UG"		/* Unrestricted guest */
		"\011APIC-reg"		/* APIC-register virtualization */
		"\012VID"		/* Virtual-interrupt delivery */
		"\013PAUSE-loop"	/* PAUSE-loop exiting */
		"\014RDRAND"		/* RDRAND exiting */
		"\015INVPCID"		/* Enable INVPCID */
		"\016VMFUNC"		/* Enable VM functions */
		"\017VMCS"		/* VMCS shadowing */
		"\020EPT#VE"		/* EPT-violation #VE */
		"\021XSAVES"		/* Enable XSAVES/XRSTORS */
		);
	printf("\n        Exit Controls=0x%b", mask,
	"\020"
	"\003DR"		/* Save debug controls */
				/* Ignore Host address-space size */
	"\015PERF"		/* Load MSR_PERF_GLOBAL_CTRL */
	"\020AckInt"		/* Acknowledge interrupt on exit */
	"\023PAT-SV"		/* Save MSR_PAT */
	"\024PAT-LD"		/* Load MSR_PAT */
	"\025EFER-SV"		/* Save MSR_EFER */
	"\026EFER-LD"		/* Load MSR_EFER */
	"\027PTMR-SV"		/* Save VMX-preemption timer value */
	);
	printf("\n        Entry Controls=0x%b", mask,
	"\020"
	"\003DR"		/* Save debug controls */
				/* Ignore IA-32e mode guest */
				/* Ignore Entry to SMM */
				/* Ignore Deactivate dual-monitor treatment */
	"\016PERF"		/* Load MSR_PERF_GLOBAL_CTRL */
	"\017PAT"		/* Load MSR_PAT */
	"\020EFER"		/* Load MSR_EFER */
	);
	if (proc & PROCBASED_SECONDARY_CONTROLS &&
	    (proc2 & (PROCBASED2_ENABLE_EPT | PROCBASED2_ENABLE_VPID)) != 0) {
		msr = rdmsr(MSR_VMX_EPT_VPID_CAP);
		mask = msr;
		printf("\n        EPT Features=0x%b", mask,
		"\020"
		"\001XO"		/* Execute-only translations */
		"\007PW4"		/* Page-walk length of 4 */
		"\011UC"		/* EPT paging-structure mem can be UC */
		"\017WB"		/* EPT paging-structure mem can be WB */
		"\0212M"		/* EPT PDE can map a 2-Mbyte page */
		"\0221G"		/* EPT PDPTE can map a 1-Gbyte page */
		"\025INVEPT"		/* INVEPT is supported */
		"\026AD"		/* Accessed and dirty flags for EPT */
		"\032single"		/* INVEPT single-context type */
		"\033all"		/* INVEPT all-context type */
		);
		mask = msr >> 32;
		printf("\n        VPID Features=0x%b", mask,
		"\020"
		"\001INVVPID"		/* INVVPID is supported */
		"\011individual"	/* INVVPID individual-address type */
		"\012single"		/* INVVPID single-context type */
		"\013all"		/* INVVPID all-context type */
		 /* INVVPID single-context-retaining-globals type */
		"\014single-globals"
		);
	}
}