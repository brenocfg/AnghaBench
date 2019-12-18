#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * gpr; } ;
struct TYPE_8__ {int prodded; scalar_t__ hcall_needed; TYPE_2__ regs; int /*<<< orphan*/  ceded; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_4__* kvm; } ;
struct TYPE_6__ {int /*<<< orphan*/  rtas_tokens; int /*<<< orphan*/  enabled_hcalls; } ;
struct TYPE_9__ {int /*<<< orphan*/  srcu; TYPE_1__ arch; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOENT ; 
#define  H_CEDE 153 
#define  H_CONFER 152 
#define  H_COPY_TOFROM_GUEST 151 
#define  H_CPPR 150 
#define  H_ENTER_NESTED 149 
#define  H_EOI 148 
 unsigned long H_FUNCTION ; 
#define  H_GET_TCE 147 
 unsigned long H_HARDWARE ; 
 unsigned long H_INTERRUPT ; 
#define  H_IPI 146 
#define  H_IPOLL 145 
#define  H_LOGICAL_CI_LOAD 144 
#define  H_LOGICAL_CI_STORE 143 
 unsigned long H_NOT_AVAILABLE ; 
#define  H_PAGE_INIT 142 
 unsigned long H_PARAMETER ; 
#define  H_PROD 141 
#define  H_PUT_TCE 140 
#define  H_PUT_TCE_INDIRECT 139 
#define  H_RANDOM 138 
#define  H_REGISTER_VPA 137 
#define  H_RTAS 136 
#define  H_SET_DABR 135 
#define  H_SET_MODE 134 
#define  H_SET_PARTITION_TABLE 133 
#define  H_SET_XDABR 132 
#define  H_STUFF_TCE 131 
 unsigned long H_SUCCESS ; 
#define  H_TLB_INVALIDATE 130 
 unsigned long H_TOO_HARD ; 
#define  H_XIRR 129 
#define  H_XIRR_X 128 
 unsigned long MAX_HCALL_OPCODE ; 
 int RESUME_GUEST ; 
 int RESUME_HOST ; 
 unsigned long do_h_register_vpa (struct kvm_vcpu*,void*,void*,void*) ; 
 int /*<<< orphan*/  kvm_arch_vcpu_yield_to (struct kvm_vcpu*) ; 
 unsigned long kvmhv_copy_tofrom_guest_nested (struct kvm_vcpu*) ; 
 unsigned long kvmhv_do_nested_tlbie (struct kvm_vcpu*) ; 
 unsigned long kvmhv_enter_nested_guest (struct kvm_vcpu*) ; 
 unsigned long kvmhv_set_partition_table (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_fast_vcpu_kick_hv (struct kvm_vcpu*) ; 
 struct kvm_vcpu* kvmppc_find_vcpu (TYPE_4__*,unsigned long) ; 
 void* kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int kvmppc_get_yield_count (struct kvm_vcpu*) ; 
 unsigned long kvmppc_h_get_tce (struct kvm_vcpu*,void*,void*) ; 
 unsigned long kvmppc_h_logical_ci_load (struct kvm_vcpu*) ; 
 unsigned long kvmppc_h_logical_ci_store (struct kvm_vcpu*) ; 
 unsigned long kvmppc_h_page_init (struct kvm_vcpu*,void*,void*,void*) ; 
 unsigned long kvmppc_h_put_tce (struct kvm_vcpu*,void*,void*,void*) ; 
 unsigned long kvmppc_h_put_tce_indirect (struct kvm_vcpu*,void*,void*,void*,void*) ; 
 unsigned long kvmppc_h_set_dabr (struct kvm_vcpu*,void*) ; 
 unsigned long kvmppc_h_set_mode (struct kvm_vcpu*,void*,void*,void*,void*) ; 
 unsigned long kvmppc_h_set_xdabr (struct kvm_vcpu*,void*,void*) ; 
 unsigned long kvmppc_h_stuff_tce (struct kvm_vcpu*,void*,void*,void*,void*) ; 
 int kvmppc_rtas_hcall (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_xics_enabled (struct kvm_vcpu*) ; 
 unsigned long kvmppc_xics_hcall (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nesting_enabled (TYPE_4__*) ; 
 int /*<<< orphan*/  powernv_get_random_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xics_on_xive () ; 

int kvmppc_pseries_do_hcall(struct kvm_vcpu *vcpu)
{
	unsigned long req = kvmppc_get_gpr(vcpu, 3);
	unsigned long target, ret = H_SUCCESS;
	int yield_count;
	struct kvm_vcpu *tvcpu;
	int idx, rc;

	if (req <= MAX_HCALL_OPCODE &&
	    !test_bit(req/4, vcpu->kvm->arch.enabled_hcalls))
		return RESUME_HOST;

	switch (req) {
	case H_CEDE:
		break;
	case H_PROD:
		target = kvmppc_get_gpr(vcpu, 4);
		tvcpu = kvmppc_find_vcpu(vcpu->kvm, target);
		if (!tvcpu) {
			ret = H_PARAMETER;
			break;
		}
		tvcpu->arch.prodded = 1;
		smp_mb();
		if (tvcpu->arch.ceded)
			kvmppc_fast_vcpu_kick_hv(tvcpu);
		break;
	case H_CONFER:
		target = kvmppc_get_gpr(vcpu, 4);
		if (target == -1)
			break;
		tvcpu = kvmppc_find_vcpu(vcpu->kvm, target);
		if (!tvcpu) {
			ret = H_PARAMETER;
			break;
		}
		yield_count = kvmppc_get_gpr(vcpu, 5);
		if (kvmppc_get_yield_count(tvcpu) != yield_count)
			break;
		kvm_arch_vcpu_yield_to(tvcpu);
		break;
	case H_REGISTER_VPA:
		ret = do_h_register_vpa(vcpu, kvmppc_get_gpr(vcpu, 4),
					kvmppc_get_gpr(vcpu, 5),
					kvmppc_get_gpr(vcpu, 6));
		break;
	case H_RTAS:
		if (list_empty(&vcpu->kvm->arch.rtas_tokens))
			return RESUME_HOST;

		idx = srcu_read_lock(&vcpu->kvm->srcu);
		rc = kvmppc_rtas_hcall(vcpu);
		srcu_read_unlock(&vcpu->kvm->srcu, idx);

		if (rc == -ENOENT)
			return RESUME_HOST;
		else if (rc == 0)
			break;

		/* Send the error out to userspace via KVM_RUN */
		return rc;
	case H_LOGICAL_CI_LOAD:
		ret = kvmppc_h_logical_ci_load(vcpu);
		if (ret == H_TOO_HARD)
			return RESUME_HOST;
		break;
	case H_LOGICAL_CI_STORE:
		ret = kvmppc_h_logical_ci_store(vcpu);
		if (ret == H_TOO_HARD)
			return RESUME_HOST;
		break;
	case H_SET_MODE:
		ret = kvmppc_h_set_mode(vcpu, kvmppc_get_gpr(vcpu, 4),
					kvmppc_get_gpr(vcpu, 5),
					kvmppc_get_gpr(vcpu, 6),
					kvmppc_get_gpr(vcpu, 7));
		if (ret == H_TOO_HARD)
			return RESUME_HOST;
		break;
	case H_XIRR:
	case H_CPPR:
	case H_EOI:
	case H_IPI:
	case H_IPOLL:
	case H_XIRR_X:
		if (kvmppc_xics_enabled(vcpu)) {
			if (xics_on_xive()) {
				ret = H_NOT_AVAILABLE;
				return RESUME_GUEST;
			}
			ret = kvmppc_xics_hcall(vcpu, req);
			break;
		}
		return RESUME_HOST;
	case H_SET_DABR:
		ret = kvmppc_h_set_dabr(vcpu, kvmppc_get_gpr(vcpu, 4));
		break;
	case H_SET_XDABR:
		ret = kvmppc_h_set_xdabr(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5));
		break;
#ifdef CONFIG_SPAPR_TCE_IOMMU
	case H_GET_TCE:
		ret = kvmppc_h_get_tce(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5));
		if (ret == H_TOO_HARD)
			return RESUME_HOST;
		break;
	case H_PUT_TCE:
		ret = kvmppc_h_put_tce(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5),
						kvmppc_get_gpr(vcpu, 6));
		if (ret == H_TOO_HARD)
			return RESUME_HOST;
		break;
	case H_PUT_TCE_INDIRECT:
		ret = kvmppc_h_put_tce_indirect(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5),
						kvmppc_get_gpr(vcpu, 6),
						kvmppc_get_gpr(vcpu, 7));
		if (ret == H_TOO_HARD)
			return RESUME_HOST;
		break;
	case H_STUFF_TCE:
		ret = kvmppc_h_stuff_tce(vcpu, kvmppc_get_gpr(vcpu, 4),
						kvmppc_get_gpr(vcpu, 5),
						kvmppc_get_gpr(vcpu, 6),
						kvmppc_get_gpr(vcpu, 7));
		if (ret == H_TOO_HARD)
			return RESUME_HOST;
		break;
#endif
	case H_RANDOM:
		if (!powernv_get_random_long(&vcpu->arch.regs.gpr[4]))
			ret = H_HARDWARE;
		break;

	case H_SET_PARTITION_TABLE:
		ret = H_FUNCTION;
		if (nesting_enabled(vcpu->kvm))
			ret = kvmhv_set_partition_table(vcpu);
		break;
	case H_ENTER_NESTED:
		ret = H_FUNCTION;
		if (!nesting_enabled(vcpu->kvm))
			break;
		ret = kvmhv_enter_nested_guest(vcpu);
		if (ret == H_INTERRUPT) {
			kvmppc_set_gpr(vcpu, 3, 0);
			vcpu->arch.hcall_needed = 0;
			return -EINTR;
		} else if (ret == H_TOO_HARD) {
			kvmppc_set_gpr(vcpu, 3, 0);
			vcpu->arch.hcall_needed = 0;
			return RESUME_HOST;
		}
		break;
	case H_TLB_INVALIDATE:
		ret = H_FUNCTION;
		if (nesting_enabled(vcpu->kvm))
			ret = kvmhv_do_nested_tlbie(vcpu);
		break;
	case H_COPY_TOFROM_GUEST:
		ret = H_FUNCTION;
		if (nesting_enabled(vcpu->kvm))
			ret = kvmhv_copy_tofrom_guest_nested(vcpu);
		break;
	case H_PAGE_INIT:
		ret = kvmppc_h_page_init(vcpu, kvmppc_get_gpr(vcpu, 4),
					 kvmppc_get_gpr(vcpu, 5),
					 kvmppc_get_gpr(vcpu, 6));
		break;
	default:
		return RESUME_HOST;
	}
	kvmppc_set_gpr(vcpu, 3, ret);
	vcpu->arch.hcall_needed = 0;
	return RESUME_GUEST;
}