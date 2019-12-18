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
struct TYPE_2__ {int /*<<< orphan*/  sysregs_loaded_on_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  ACTLR_EL1 150 
#define  AFSR0_EL1 149 
#define  AFSR1_EL1 148 
#define  AMAIR_EL1 147 
#define  CNTKCTL_EL1 146 
#define  CONTEXTIDR_EL1 145 
#define  CPACR_EL1 144 
#define  CSSELR_EL1 143 
#define  DACR32_EL2 142 
#define  DBGVCR32_EL2 141 
#define  ESR_EL1 140 
#define  FAR_EL1 139 
#define  IFSR32_EL2 138 
#define  MAIR_EL1 137 
#define  PAR_EL1 136 
#define  SCTLR_EL1 135 
 int /*<<< orphan*/  SYS_ACTLR_EL1 ; 
 int /*<<< orphan*/  SYS_AFSR0_EL12 ; 
 int /*<<< orphan*/  SYS_AFSR1_EL12 ; 
 int /*<<< orphan*/  SYS_AMAIR_EL12 ; 
 int /*<<< orphan*/  SYS_CNTKCTL_EL12 ; 
 int /*<<< orphan*/  SYS_CONTEXTIDR_EL12 ; 
 int /*<<< orphan*/  SYS_CPACR_EL12 ; 
 int /*<<< orphan*/  SYS_CSSELR_EL1 ; 
 int /*<<< orphan*/  SYS_DACR32_EL2 ; 
 int /*<<< orphan*/  SYS_DBGVCR32_EL2 ; 
 int /*<<< orphan*/  SYS_ESR_EL12 ; 
 int /*<<< orphan*/  SYS_FAR_EL12 ; 
 int /*<<< orphan*/  SYS_IFSR32_EL2 ; 
 int /*<<< orphan*/  SYS_MAIR_EL12 ; 
 int /*<<< orphan*/  SYS_PAR_EL1 ; 
 int /*<<< orphan*/  SYS_SCTLR_EL12 ; 
 int /*<<< orphan*/  SYS_TCR_EL12 ; 
 int /*<<< orphan*/  SYS_TPIDRRO_EL0 ; 
 int /*<<< orphan*/  SYS_TPIDR_EL0 ; 
 int /*<<< orphan*/  SYS_TPIDR_EL1 ; 
 int /*<<< orphan*/  SYS_TTBR0_EL12 ; 
 int /*<<< orphan*/  SYS_TTBR1_EL12 ; 
 int /*<<< orphan*/  SYS_VBAR_EL12 ; 
#define  TCR_EL1 134 
#define  TPIDRRO_EL0 133 
#define  TPIDR_EL0 132 
#define  TPIDR_EL1 131 
#define  TTBR0_EL1 130 
#define  TTBR1_EL1 129 
#define  VBAR_EL1 128 
 int /*<<< orphan*/  __vcpu_sys_reg (struct kvm_vcpu const*,int) ; 
 int /*<<< orphan*/  read_sysreg_s (int /*<<< orphan*/ ) ; 

u64 vcpu_read_sys_reg(const struct kvm_vcpu *vcpu, int reg)
{
	if (!vcpu->arch.sysregs_loaded_on_cpu)
		goto immediate_read;

	/*
	 * System registers listed in the switch are not saved on every
	 * exit from the guest but are only saved on vcpu_put.
	 *
	 * Note that MPIDR_EL1 for the guest is set by KVM via VMPIDR_EL2 but
	 * should never be listed below, because the guest cannot modify its
	 * own MPIDR_EL1 and MPIDR_EL1 is accessed for VCPU A from VCPU B's
	 * thread when emulating cross-VCPU communication.
	 */
	switch (reg) {
	case CSSELR_EL1:	return read_sysreg_s(SYS_CSSELR_EL1);
	case SCTLR_EL1:		return read_sysreg_s(SYS_SCTLR_EL12);
	case ACTLR_EL1:		return read_sysreg_s(SYS_ACTLR_EL1);
	case CPACR_EL1:		return read_sysreg_s(SYS_CPACR_EL12);
	case TTBR0_EL1:		return read_sysreg_s(SYS_TTBR0_EL12);
	case TTBR1_EL1:		return read_sysreg_s(SYS_TTBR1_EL12);
	case TCR_EL1:		return read_sysreg_s(SYS_TCR_EL12);
	case ESR_EL1:		return read_sysreg_s(SYS_ESR_EL12);
	case AFSR0_EL1:		return read_sysreg_s(SYS_AFSR0_EL12);
	case AFSR1_EL1:		return read_sysreg_s(SYS_AFSR1_EL12);
	case FAR_EL1:		return read_sysreg_s(SYS_FAR_EL12);
	case MAIR_EL1:		return read_sysreg_s(SYS_MAIR_EL12);
	case VBAR_EL1:		return read_sysreg_s(SYS_VBAR_EL12);
	case CONTEXTIDR_EL1:	return read_sysreg_s(SYS_CONTEXTIDR_EL12);
	case TPIDR_EL0:		return read_sysreg_s(SYS_TPIDR_EL0);
	case TPIDRRO_EL0:	return read_sysreg_s(SYS_TPIDRRO_EL0);
	case TPIDR_EL1:		return read_sysreg_s(SYS_TPIDR_EL1);
	case AMAIR_EL1:		return read_sysreg_s(SYS_AMAIR_EL12);
	case CNTKCTL_EL1:	return read_sysreg_s(SYS_CNTKCTL_EL12);
	case PAR_EL1:		return read_sysreg_s(SYS_PAR_EL1);
	case DACR32_EL2:	return read_sysreg_s(SYS_DACR32_EL2);
	case IFSR32_EL2:	return read_sysreg_s(SYS_IFSR32_EL2);
	case DBGVCR32_EL2:	return read_sysreg_s(SYS_DBGVCR32_EL2);
	}

immediate_read:
	return __vcpu_sys_reg(vcpu, reg);
}