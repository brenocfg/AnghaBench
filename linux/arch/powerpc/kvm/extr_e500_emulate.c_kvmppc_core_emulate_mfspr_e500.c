#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int u32 ;
struct kvmppc_vcpu_e500 {int* pid; int l1csr0; int l1csr1; int hid0; int hid1; int svr; } ;
struct TYPE_4__ {int decar; int* tlbcfg; int* tlbps; int mmucfg; int eptcfg; int pwrmgtcr0; int* ivor; TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int mas0; int mas1; int mas2; int mas7_3; int mas4; int mas6; } ;

/* Variables and functions */
 size_t BOOKE_IRQPRIO_ALTIVEC_ASSIST ; 
 size_t BOOKE_IRQPRIO_ALTIVEC_UNAVAIL ; 
 size_t BOOKE_IRQPRIO_DBELL ; 
 size_t BOOKE_IRQPRIO_DBELL_CRIT ; 
 size_t BOOKE_IRQPRIO_PERFORMANCE_MONITOR ; 
 size_t BOOKE_IRQPRIO_SPE_FP_DATA ; 
 size_t BOOKE_IRQPRIO_SPE_FP_ROUND ; 
 size_t BOOKE_IRQPRIO_SPE_UNAVAIL ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
#define  SPRN_DECAR 157 
#define  SPRN_EPTCFG 156 
#define  SPRN_HID0 155 
#define  SPRN_HID1 154 
#define  SPRN_IVOR32 153 
#define  SPRN_IVOR33 152 
#define  SPRN_IVOR34 151 
#define  SPRN_IVOR35 150 
#define  SPRN_IVOR36 149 
#define  SPRN_IVOR37 148 
#define  SPRN_L1CSR0 147 
#define  SPRN_L1CSR1 146 
#define  SPRN_MAS0 145 
#define  SPRN_MAS1 144 
#define  SPRN_MAS2 143 
#define  SPRN_MAS3 142 
#define  SPRN_MAS4 141 
#define  SPRN_MAS6 140 
#define  SPRN_MAS7 139 
#define  SPRN_MMUCFG 138 
#define  SPRN_MMUCSR0 137 
#define  SPRN_PID 136 
#define  SPRN_PID1 135 
#define  SPRN_PID2 134 
#define  SPRN_PWRMGTCR0 133 
#define  SPRN_SVR 132 
#define  SPRN_TLB0CFG 131 
#define  SPRN_TLB0PS 130 
#define  SPRN_TLB1CFG 129 
#define  SPRN_TLB1PS 128 
 int /*<<< orphan*/  VCPU_FTR_MMU_V2 ; 
 int /*<<< orphan*/  has_feature (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_booke_emulate_mfspr (struct kvm_vcpu*,int,int*) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

int kvmppc_core_emulate_mfspr_e500(struct kvm_vcpu *vcpu, int sprn, ulong *spr_val)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int emulated = EMULATE_DONE;

	switch (sprn) {
#ifndef CONFIG_KVM_BOOKE_HV
	case SPRN_PID:
		*spr_val = vcpu_e500->pid[0];
		break;
	case SPRN_PID1:
		*spr_val = vcpu_e500->pid[1];
		break;
	case SPRN_PID2:
		*spr_val = vcpu_e500->pid[2];
		break;
	case SPRN_MAS0:
		*spr_val = vcpu->arch.shared->mas0;
		break;
	case SPRN_MAS1:
		*spr_val = vcpu->arch.shared->mas1;
		break;
	case SPRN_MAS2:
		*spr_val = vcpu->arch.shared->mas2;
		break;
	case SPRN_MAS3:
		*spr_val = (u32)vcpu->arch.shared->mas7_3;
		break;
	case SPRN_MAS4:
		*spr_val = vcpu->arch.shared->mas4;
		break;
	case SPRN_MAS6:
		*spr_val = vcpu->arch.shared->mas6;
		break;
	case SPRN_MAS7:
		*spr_val = vcpu->arch.shared->mas7_3 >> 32;
		break;
#endif
	case SPRN_DECAR:
		*spr_val = vcpu->arch.decar;
		break;
	case SPRN_TLB0CFG:
		*spr_val = vcpu->arch.tlbcfg[0];
		break;
	case SPRN_TLB1CFG:
		*spr_val = vcpu->arch.tlbcfg[1];
		break;
	case SPRN_TLB0PS:
		if (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			return EMULATE_FAIL;
		*spr_val = vcpu->arch.tlbps[0];
		break;
	case SPRN_TLB1PS:
		if (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			return EMULATE_FAIL;
		*spr_val = vcpu->arch.tlbps[1];
		break;
	case SPRN_L1CSR0:
		*spr_val = vcpu_e500->l1csr0;
		break;
	case SPRN_L1CSR1:
		*spr_val = vcpu_e500->l1csr1;
		break;
	case SPRN_HID0:
		*spr_val = vcpu_e500->hid0;
		break;
	case SPRN_HID1:
		*spr_val = vcpu_e500->hid1;
		break;
	case SPRN_SVR:
		*spr_val = vcpu_e500->svr;
		break;

	case SPRN_MMUCSR0:
		*spr_val = 0;
		break;

	case SPRN_MMUCFG:
		*spr_val = vcpu->arch.mmucfg;
		break;
	case SPRN_EPTCFG:
		if (!has_feature(vcpu, VCPU_FTR_MMU_V2))
			return EMULATE_FAIL;
		/*
		 * Legacy Linux guests access EPTCFG register even if the E.PT
		 * category is disabled in the VM. Give them a chance to live.
		 */
		*spr_val = vcpu->arch.eptcfg;
		break;

	case SPRN_PWRMGTCR0:
		*spr_val = vcpu->arch.pwrmgtcr0;
		break;

	/* extra exceptions */
#ifdef CONFIG_SPE_POSSIBLE
	case SPRN_IVOR32:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_UNAVAIL];
		break;
	case SPRN_IVOR33:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_DATA];
		break;
	case SPRN_IVOR34:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_SPE_FP_ROUND];
		break;
#endif
#ifdef CONFIG_ALTIVEC
	case SPRN_IVOR32:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_UNAVAIL];
		break;
	case SPRN_IVOR33:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_ALTIVEC_ASSIST];
		break;
#endif
	case SPRN_IVOR35:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_PERFORMANCE_MONITOR];
		break;
#ifdef CONFIG_KVM_BOOKE_HV
	case SPRN_IVOR36:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL];
		break;
	case SPRN_IVOR37:
		*spr_val = vcpu->arch.ivor[BOOKE_IRQPRIO_DBELL_CRIT];
		break;
#endif
	default:
		emulated = kvmppc_booke_emulate_mfspr(vcpu, sprn, spr_val);
	}

	return emulated;
}