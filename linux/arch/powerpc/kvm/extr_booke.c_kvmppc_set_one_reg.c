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
typedef  void* u32 ;
struct TYPE_6__ {void* dac2; void* dac1; void* iac4; void* iac3; void* iac2; void* iac1; } ;
struct TYPE_7__ {void* vrsave; TYPE_1__ dbg_reg; } ;
struct kvm_vcpu {TYPE_5__* kvm; TYPE_2__ arch; } ;
struct TYPE_9__ {TYPE_3__* kvm_ops; } ;
struct TYPE_10__ {TYPE_4__ arch; } ;
struct TYPE_8__ {int (* set_one_reg ) (struct kvm_vcpu*,int,union kvmppc_one_reg*) ;} ;

/* Variables and functions */
#define  KVM_REG_PPC_CLEAR_TSR 140 
#define  KVM_REG_PPC_DAC1 139 
#define  KVM_REG_PPC_DAC2 138 
#define  KVM_REG_PPC_EPCR 137 
#define  KVM_REG_PPC_EPR 136 
#define  KVM_REG_PPC_IAC1 135 
#define  KVM_REG_PPC_IAC2 134 
#define  KVM_REG_PPC_IAC3 133 
#define  KVM_REG_PPC_IAC4 132 
#define  KVM_REG_PPC_OR_TSR 131 
#define  KVM_REG_PPC_TCR 130 
#define  KVM_REG_PPC_TSR 129 
#define  KVM_REG_PPC_VRSAVE 128 
 int /*<<< orphan*/  kvmppc_clr_tsr_bits (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  kvmppc_set_epcr (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  kvmppc_set_epr (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  kvmppc_set_tcr (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  kvmppc_set_tsr (struct kvm_vcpu*,void*) ; 
 int /*<<< orphan*/  kvmppc_set_tsr_bits (struct kvm_vcpu*,void*) ; 
 void* set_reg_val (int,union kvmppc_one_reg) ; 
 int stub1 (struct kvm_vcpu*,int,union kvmppc_one_reg*) ; 

int kvmppc_set_one_reg(struct kvm_vcpu *vcpu, u64 id,
			union kvmppc_one_reg *val)
{
	int r = 0;

	switch (id) {
	case KVM_REG_PPC_IAC1:
		vcpu->arch.dbg_reg.iac1 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_IAC2:
		vcpu->arch.dbg_reg.iac2 = set_reg_val(id, *val);
		break;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	case KVM_REG_PPC_IAC3:
		vcpu->arch.dbg_reg.iac3 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_IAC4:
		vcpu->arch.dbg_reg.iac4 = set_reg_val(id, *val);
		break;
#endif
	case KVM_REG_PPC_DAC1:
		vcpu->arch.dbg_reg.dac1 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_DAC2:
		vcpu->arch.dbg_reg.dac2 = set_reg_val(id, *val);
		break;
	case KVM_REG_PPC_EPR: {
		u32 new_epr = set_reg_val(id, *val);
		kvmppc_set_epr(vcpu, new_epr);
		break;
	}
#if defined(CONFIG_64BIT)
	case KVM_REG_PPC_EPCR: {
		u32 new_epcr = set_reg_val(id, *val);
		kvmppc_set_epcr(vcpu, new_epcr);
		break;
	}
#endif
	case KVM_REG_PPC_OR_TSR: {
		u32 tsr_bits = set_reg_val(id, *val);
		kvmppc_set_tsr_bits(vcpu, tsr_bits);
		break;
	}
	case KVM_REG_PPC_CLEAR_TSR: {
		u32 tsr_bits = set_reg_val(id, *val);
		kvmppc_clr_tsr_bits(vcpu, tsr_bits);
		break;
	}
	case KVM_REG_PPC_TSR: {
		u32 tsr = set_reg_val(id, *val);
		kvmppc_set_tsr(vcpu, tsr);
		break;
	}
	case KVM_REG_PPC_TCR: {
		u32 tcr = set_reg_val(id, *val);
		kvmppc_set_tcr(vcpu, tcr);
		break;
	}
	case KVM_REG_PPC_VRSAVE:
		vcpu->arch.vrsave = set_reg_val(id, *val);
		break;
	default:
		r = vcpu->kvm->arch.kvm_ops->set_one_reg(vcpu, id, val);
		break;
	}

	return r;
}