#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u64 ;
struct TYPE_12__ {int /*<<< orphan*/  complete_userspace_io; } ;
struct kvm_vcpu {TYPE_5__ arch; TYPE_4__* run; } ;
struct TYPE_14__ {scalar_t__ (* get_cpl ) (struct kvm_vcpu*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  active; } ;
struct TYPE_8__ {int input; int* params; } ;
struct TYPE_9__ {TYPE_1__ hcall; } ;
struct TYPE_10__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {TYPE_3__ hyperv; int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
#define  HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST 136 
#define  HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX 135 
#define  HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE 134 
#define  HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX 133 
#define  HVCALL_NOTIFY_LONG_SPIN_WAIT 132 
#define  HVCALL_POST_MESSAGE 131 
#define  HVCALL_SEND_IPI 130 
#define  HVCALL_SEND_IPI_EX 129 
#define  HVCALL_SIGNAL_EVENT 128 
 int HV_HYPERCALL_FAST_BIT ; 
 int HV_HYPERCALL_REP_COMP_OFFSET ; 
 int HV_HYPERCALL_REP_START_OFFSET ; 
 int HV_STATUS_INVALID_HYPERCALL_CODE ; 
 int HV_STATUS_INVALID_HYPERCALL_INPUT ; 
 int HV_STATUS_INVALID_PORT_ID ; 
 int HV_STATUS_SUCCESS ; 
 int /*<<< orphan*/  KVM_EXIT_HYPERV ; 
 int /*<<< orphan*/  KVM_EXIT_HYPERV_HCALL ; 
 int /*<<< orphan*/  UD_VECTOR ; 
 scalar_t__ is_64_bit_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_protmode (struct kvm_vcpu*) ; 
 int kvm_hv_flush_tlb (struct kvm_vcpu*,int,int,int) ; 
 int kvm_hv_hypercall_complete (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_hv_hypercall_complete_userspace ; 
 int kvm_hv_send_ipi (struct kvm_vcpu*,int,int,int,int) ; 
 int kvm_hvcall_signal_event (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_r8_read (struct kvm_vcpu*) ; 
 int kvm_rax_read (struct kvm_vcpu*) ; 
 scalar_t__ kvm_rbx_read (struct kvm_vcpu*) ; 
 int kvm_rcx_read (struct kvm_vcpu*) ; 
 scalar_t__ kvm_rdi_read (struct kvm_vcpu*) ; 
 int kvm_rdx_read (struct kvm_vcpu*) ; 
 int kvm_rsi_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_on_spin (struct kvm_vcpu*,int) ; 
 TYPE_7__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_hv_hypercall (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 TYPE_6__* vcpu_to_synic (struct kvm_vcpu*) ; 

int kvm_hv_hypercall(struct kvm_vcpu *vcpu)
{
	u64 param, ingpa, outgpa, ret = HV_STATUS_SUCCESS;
	uint16_t code, rep_idx, rep_cnt;
	bool fast, rep;

	/*
	 * hypercall generates UD from non zero cpl and real mode
	 * per HYPER-V spec
	 */
	if (kvm_x86_ops->get_cpl(vcpu) != 0 || !is_protmode(vcpu)) {
		kvm_queue_exception(vcpu, UD_VECTOR);
		return 1;
	}

#ifdef CONFIG_X86_64
	if (is_64_bit_mode(vcpu)) {
		param = kvm_rcx_read(vcpu);
		ingpa = kvm_rdx_read(vcpu);
		outgpa = kvm_r8_read(vcpu);
	} else
#endif
	{
		param = ((u64)kvm_rdx_read(vcpu) << 32) |
			(kvm_rax_read(vcpu) & 0xffffffff);
		ingpa = ((u64)kvm_rbx_read(vcpu) << 32) |
			(kvm_rcx_read(vcpu) & 0xffffffff);
		outgpa = ((u64)kvm_rdi_read(vcpu) << 32) |
			(kvm_rsi_read(vcpu) & 0xffffffff);
	}

	code = param & 0xffff;
	fast = !!(param & HV_HYPERCALL_FAST_BIT);
	rep_cnt = (param >> HV_HYPERCALL_REP_COMP_OFFSET) & 0xfff;
	rep_idx = (param >> HV_HYPERCALL_REP_START_OFFSET) & 0xfff;
	rep = !!(rep_cnt || rep_idx);

	trace_kvm_hv_hypercall(code, fast, rep_cnt, rep_idx, ingpa, outgpa);

	switch (code) {
	case HVCALL_NOTIFY_LONG_SPIN_WAIT:
		if (unlikely(rep)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		kvm_vcpu_on_spin(vcpu, true);
		break;
	case HVCALL_SIGNAL_EVENT:
		if (unlikely(rep)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		ret = kvm_hvcall_signal_event(vcpu, fast, ingpa);
		if (ret != HV_STATUS_INVALID_PORT_ID)
			break;
		/* fall through - maybe userspace knows this conn_id. */
	case HVCALL_POST_MESSAGE:
		/* don't bother userspace if it has no way to handle it */
		if (unlikely(rep || !vcpu_to_synic(vcpu)->active)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		vcpu->run->exit_reason = KVM_EXIT_HYPERV;
		vcpu->run->hyperv.type = KVM_EXIT_HYPERV_HCALL;
		vcpu->run->hyperv.u.hcall.input = param;
		vcpu->run->hyperv.u.hcall.params[0] = ingpa;
		vcpu->run->hyperv.u.hcall.params[1] = outgpa;
		vcpu->arch.complete_userspace_io =
				kvm_hv_hypercall_complete_userspace;
		return 0;
	case HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST:
		if (unlikely(fast || !rep_cnt || rep_idx)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, false);
		break;
	case HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE:
		if (unlikely(fast || rep)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, false);
		break;
	case HVCALL_FLUSH_VIRTUAL_ADDRESS_LIST_EX:
		if (unlikely(fast || !rep_cnt || rep_idx)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, true);
		break;
	case HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX:
		if (unlikely(fast || rep)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		ret = kvm_hv_flush_tlb(vcpu, ingpa, rep_cnt, true);
		break;
	case HVCALL_SEND_IPI:
		if (unlikely(rep)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		ret = kvm_hv_send_ipi(vcpu, ingpa, outgpa, false, fast);
		break;
	case HVCALL_SEND_IPI_EX:
		if (unlikely(fast || rep)) {
			ret = HV_STATUS_INVALID_HYPERCALL_INPUT;
			break;
		}
		ret = kvm_hv_send_ipi(vcpu, ingpa, outgpa, true, false);
		break;
	default:
		ret = HV_STATUS_INVALID_HYPERCALL_CODE;
		break;
	}

	return kvm_hv_hypercall_complete(vcpu, ret);
}