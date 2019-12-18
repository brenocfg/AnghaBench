#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct TYPE_6__ {int doorbell_request; TYPE_2__* vcore; } ;
struct kvm_vcpu {int vcpu_id; TYPE_3__ arch; struct kvm* kvm; } ;
struct TYPE_4__ {int emul_smt_mode; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  dpdes; } ;

/* Variables and functions */
 scalar_t__ EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int /*<<< orphan*/  INST_GENERIC ; 
#define  OP_31_XOP_MFSPR 132 
#define  OP_31_XOP_MSGCLRP 131 
#define  OP_31_XOP_MSGSNDP 130 
 unsigned long PPC_DBELL_SERVER ; 
 int RESUME_GUEST ; 
#define  SPRN_DPDES 129 
#define  SPRN_TIR 128 
 int get_op (unsigned long) ; 
 unsigned long get_rb (unsigned long) ; 
 int /*<<< orphan*/  get_rt (unsigned long) ; 
 int /*<<< orphan*/  get_sprn (unsigned long) ; 
 int get_xop (unsigned long) ; 
 int /*<<< orphan*/  kvmppc_fast_vcpu_kick_hv (struct kvm_vcpu*) ; 
 struct kvm_vcpu* kvmppc_find_vcpu (struct kvm*,int /*<<< orphan*/ ) ; 
 unsigned long kvmppc_get_gpr (struct kvm_vcpu*,unsigned long) ; 
 scalar_t__ kvmppc_get_last_inst (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ kvmppc_get_pc (struct kvm_vcpu*) ; 
 unsigned long kvmppc_read_dpdes (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_set_pc (struct kvm_vcpu*,scalar_t__) ; 

__attribute__((used)) static int kvmppc_emulate_doorbell_instr(struct kvm_vcpu *vcpu)
{
	u32 inst, rb, thr;
	unsigned long arg;
	struct kvm *kvm = vcpu->kvm;
	struct kvm_vcpu *tvcpu;

	if (kvmppc_get_last_inst(vcpu, INST_GENERIC, &inst) != EMULATE_DONE)
		return RESUME_GUEST;
	if (get_op(inst) != 31)
		return EMULATE_FAIL;
	rb = get_rb(inst);
	thr = vcpu->vcpu_id & (kvm->arch.emul_smt_mode - 1);
	switch (get_xop(inst)) {
	case OP_31_XOP_MSGSNDP:
		arg = kvmppc_get_gpr(vcpu, rb);
		if (((arg >> 27) & 0xf) != PPC_DBELL_SERVER)
			break;
		arg &= 0x3f;
		if (arg >= kvm->arch.emul_smt_mode)
			break;
		tvcpu = kvmppc_find_vcpu(kvm, vcpu->vcpu_id - thr + arg);
		if (!tvcpu)
			break;
		if (!tvcpu->arch.doorbell_request) {
			tvcpu->arch.doorbell_request = 1;
			kvmppc_fast_vcpu_kick_hv(tvcpu);
		}
		break;
	case OP_31_XOP_MSGCLRP:
		arg = kvmppc_get_gpr(vcpu, rb);
		if (((arg >> 27) & 0xf) != PPC_DBELL_SERVER)
			break;
		vcpu->arch.vcore->dpdes = 0;
		vcpu->arch.doorbell_request = 0;
		break;
	case OP_31_XOP_MFSPR:
		switch (get_sprn(inst)) {
		case SPRN_TIR:
			arg = thr;
			break;
		case SPRN_DPDES:
			arg = kvmppc_read_dpdes(vcpu);
			break;
		default:
			return EMULATE_FAIL;
		}
		kvmppc_set_gpr(vcpu, get_rt(inst), arg);
		break;
	default:
		return EMULATE_FAIL;
	}
	kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);
	return RESUME_GUEST;
}