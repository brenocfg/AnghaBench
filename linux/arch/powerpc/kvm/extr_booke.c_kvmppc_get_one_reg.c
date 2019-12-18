#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union kvmppc_one_reg {int dummy; } kvmppc_one_reg ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  dac2; int /*<<< orphan*/  dac1; int /*<<< orphan*/  iac4; int /*<<< orphan*/  iac3; int /*<<< orphan*/  iac2; int /*<<< orphan*/  iac1; } ;
struct TYPE_7__ {int /*<<< orphan*/  vrsave; int /*<<< orphan*/  tsr; int /*<<< orphan*/  tcr; int /*<<< orphan*/  epcr; TYPE_1__ dbg_reg; } ;
struct kvm_vcpu {TYPE_5__* kvm; TYPE_2__ arch; } ;
struct TYPE_9__ {TYPE_3__* kvm_ops; } ;
struct TYPE_10__ {TYPE_4__ arch; } ;
struct TYPE_8__ {int (* get_one_reg ) (struct kvm_vcpu*,int,union kvmppc_one_reg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KVMPPC_INST_SW_BREAKPOINT ; 
#define  KVM_REG_PPC_DAC1 139 
#define  KVM_REG_PPC_DAC2 138 
#define  KVM_REG_PPC_DEBUG_INST 137 
#define  KVM_REG_PPC_EPCR 136 
#define  KVM_REG_PPC_EPR 135 
#define  KVM_REG_PPC_IAC1 134 
#define  KVM_REG_PPC_IAC2 133 
#define  KVM_REG_PPC_IAC3 132 
#define  KVM_REG_PPC_IAC4 131 
#define  KVM_REG_PPC_TCR 130 
#define  KVM_REG_PPC_TSR 129 
#define  KVM_REG_PPC_VRSAVE 128 
 union kvmppc_one_reg get_reg_val (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_get_epr (struct kvm_vcpu*) ; 
 int stub1 (struct kvm_vcpu*,int,union kvmppc_one_reg*) ; 

int kvmppc_get_one_reg(struct kvm_vcpu *vcpu, u64 id,
			union kvmppc_one_reg *val)
{
	int r = 0;

	switch (id) {
	case KVM_REG_PPC_IAC1:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac1);
		break;
	case KVM_REG_PPC_IAC2:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac2);
		break;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	case KVM_REG_PPC_IAC3:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac3);
		break;
	case KVM_REG_PPC_IAC4:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.iac4);
		break;
#endif
	case KVM_REG_PPC_DAC1:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.dac1);
		break;
	case KVM_REG_PPC_DAC2:
		*val = get_reg_val(id, vcpu->arch.dbg_reg.dac2);
		break;
	case KVM_REG_PPC_EPR: {
		u32 epr = kvmppc_get_epr(vcpu);
		*val = get_reg_val(id, epr);
		break;
	}
#if defined(CONFIG_64BIT)
	case KVM_REG_PPC_EPCR:
		*val = get_reg_val(id, vcpu->arch.epcr);
		break;
#endif
	case KVM_REG_PPC_TCR:
		*val = get_reg_val(id, vcpu->arch.tcr);
		break;
	case KVM_REG_PPC_TSR:
		*val = get_reg_val(id, vcpu->arch.tsr);
		break;
	case KVM_REG_PPC_DEBUG_INST:
		*val = get_reg_val(id, KVMPPC_INST_SW_BREAKPOINT);
		break;
	case KVM_REG_PPC_VRSAVE:
		*val = get_reg_val(id, vcpu->arch.vrsave);
		break;
	default:
		r = vcpu->kvm->arch.kvm_ops->get_one_reg(vcpu, id, val);
		break;
	}

	return r;
}