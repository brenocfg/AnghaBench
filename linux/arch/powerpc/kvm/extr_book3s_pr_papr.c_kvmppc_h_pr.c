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
struct TYPE_4__ {int /*<<< orphan*/  halt_wakeup; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_1__ stat; } ;
struct TYPE_5__ {int /*<<< orphan*/  rtas_tokens; int /*<<< orphan*/  enabled_hcalls; } ;
struct TYPE_6__ {int /*<<< orphan*/  srcu; TYPE_2__ arch; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
#define  H_BULK_REMOVE 144 
#define  H_CEDE 143 
#define  H_CPPR 142 
#define  H_ENTER 141 
#define  H_EOI 140 
#define  H_IPI 139 
#define  H_IPOLL 138 
#define  H_LOGICAL_CI_LOAD 137 
#define  H_LOGICAL_CI_STORE 136 
#define  H_PROTECT 135 
#define  H_PUT_TCE 134 
#define  H_PUT_TCE_INDIRECT 133 
#define  H_REMOVE 132 
#define  H_RTAS 131 
#define  H_STUFF_TCE 130 
#define  H_XIRR 129 
#define  H_XIRR_X 128 
 int /*<<< orphan*/  KVM_REQ_UNHALT ; 
 unsigned long MAX_HCALL_OPCODE ; 
 int MSR_EE ; 
 int /*<<< orphan*/  kvm_clear_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_bulk_remove (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_enter (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_logical_ci_load (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_logical_ci_store (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_protect (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_put_tce (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_put_tce_indirect (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_remove (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_stuff_tce (struct kvm_vcpu*) ; 
 int kvmppc_h_pr_xics_hcall (struct kvm_vcpu*,unsigned long) ; 
 int kvmppc_rtas_hcall (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_msr_fast (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_xics_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (unsigned long,int /*<<< orphan*/ ) ; 

int kvmppc_h_pr(struct kvm_vcpu *vcpu, unsigned long cmd)
{
	int rc, idx;

	if (cmd <= MAX_HCALL_OPCODE &&
	    !test_bit(cmd/4, vcpu->kvm->arch.enabled_hcalls))
		return EMULATE_FAIL;

	switch (cmd) {
	case H_ENTER:
		return kvmppc_h_pr_enter(vcpu);
	case H_REMOVE:
		return kvmppc_h_pr_remove(vcpu);
	case H_PROTECT:
		return kvmppc_h_pr_protect(vcpu);
	case H_BULK_REMOVE:
		return kvmppc_h_pr_bulk_remove(vcpu);
	case H_PUT_TCE:
		return kvmppc_h_pr_put_tce(vcpu);
	case H_PUT_TCE_INDIRECT:
		return kvmppc_h_pr_put_tce_indirect(vcpu);
	case H_STUFF_TCE:
		return kvmppc_h_pr_stuff_tce(vcpu);
	case H_CEDE:
		kvmppc_set_msr_fast(vcpu, kvmppc_get_msr(vcpu) | MSR_EE);
		kvm_vcpu_block(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
		vcpu->stat.halt_wakeup++;
		return EMULATE_DONE;
	case H_LOGICAL_CI_LOAD:
		return kvmppc_h_pr_logical_ci_load(vcpu);
	case H_LOGICAL_CI_STORE:
		return kvmppc_h_pr_logical_ci_store(vcpu);
	case H_XIRR:
	case H_CPPR:
	case H_EOI:
	case H_IPI:
	case H_IPOLL:
	case H_XIRR_X:
		if (kvmppc_xics_enabled(vcpu))
			return kvmppc_h_pr_xics_hcall(vcpu, cmd);
		break;
	case H_RTAS:
		if (list_empty(&vcpu->kvm->arch.rtas_tokens))
			break;
		idx = srcu_read_lock(&vcpu->kvm->srcu);
		rc = kvmppc_rtas_hcall(vcpu);
		srcu_read_unlock(&vcpu->kvm->srcu, idx);
		if (rc)
			break;
		kvmppc_set_gpr(vcpu, 3, 0);
		return EMULATE_DONE;
	}

	return EMULATE_FAIL;
}