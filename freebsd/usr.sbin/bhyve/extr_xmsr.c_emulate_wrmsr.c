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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
#define  MSR_BIOS_SIGN 142 
#define  MSR_BIOS_UPDT_TRIG 141 
#define  MSR_HWCR 140 
#define  MSR_IC_CFG 139 
#define  MSR_K7_PERFCTR0 138 
#define  MSR_K7_PERFCTR1 137 
#define  MSR_K7_PERFCTR2 136 
#define  MSR_K7_PERFCTR3 135 
#define  MSR_LS_CFG 134 
#define  MSR_NB_CFG1 133 
#define  MSR_PERFEVSEL0 132 
#define  MSR_PERFEVSEL1 131 
#define  MSR_PERFEVSEL2 130 
#define  MSR_PERFEVSEL3 129 
#define  MSR_P_STATE_CONTROL 128 
 scalar_t__ cpu_vendor_amd ; 
 scalar_t__ cpu_vendor_intel ; 

int
emulate_wrmsr(struct vmctx *ctx, int vcpu, uint32_t num, uint64_t val)
{

	if (cpu_vendor_intel) {
		switch (num) {
		case 0xd04:		/* Sandy Bridge uncore PMCs */
		case 0xc24:
			return (0);
		case MSR_BIOS_UPDT_TRIG:
			return (0);
		case MSR_BIOS_SIGN:
			return (0);
		default:
			break;
		}
	} else if (cpu_vendor_amd) {
		switch (num) {
		case MSR_HWCR:
			/*
			 * Ignore writes to hardware configuration MSR.
			 */
			return (0);

		case MSR_NB_CFG1:
		case MSR_LS_CFG:
		case MSR_IC_CFG:
			return (0);	/* Ignore writes */

		case MSR_PERFEVSEL0:
		case MSR_PERFEVSEL1:
		case MSR_PERFEVSEL2:
		case MSR_PERFEVSEL3:
			/* Ignore writes to the PerfEvtSel MSRs */
			return (0);

		case MSR_K7_PERFCTR0:
		case MSR_K7_PERFCTR1:
		case MSR_K7_PERFCTR2:
		case MSR_K7_PERFCTR3:
			/* Ignore writes to the PerfCtr MSRs */
			return (0);

		case MSR_P_STATE_CONTROL:
			/* Ignore write to change the P-state */
			return (0);

		default:
			break;
		}
	}
	return (-1);
}