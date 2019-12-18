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
typedef  unsigned long u32 ;
struct TYPE_3__ {int /*<<< orphan*/  hypercalls; } ;
struct kvm_vcpu {TYPE_1__ stat; int /*<<< orphan*/  kvm; } ;
struct TYPE_4__ {scalar_t__ (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 unsigned long KVM_ENOSYS ; 
 unsigned long KVM_EPERM ; 
#define  KVM_HC_CLOCK_PAIRING 132 
#define  KVM_HC_KICK_CPU 131 
#define  KVM_HC_SCHED_YIELD 130 
#define  KVM_HC_SEND_IPI 129 
#define  KVM_HC_VAPIC_POLL_IRQ 128 
 int is_64_bit_mode (struct kvm_vcpu*) ; 
 int kvm_hv_hypercall (struct kvm_vcpu*) ; 
 scalar_t__ kvm_hv_hypercall_enabled (int /*<<< orphan*/ ) ; 
 unsigned long kvm_pv_clock_pairing (struct kvm_vcpu*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kvm_pv_kick_cpu_op (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long kvm_pv_send_ipi (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,int) ; 
 unsigned long kvm_rax_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rax_write (struct kvm_vcpu*,unsigned long) ; 
 unsigned long kvm_rbx_read (struct kvm_vcpu*) ; 
 unsigned long kvm_rcx_read (struct kvm_vcpu*) ; 
 unsigned long kvm_rdx_read (struct kvm_vcpu*) ; 
 unsigned long kvm_rsi_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_sched_yield (int /*<<< orphan*/ ,unsigned long) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_hypercall (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

int kvm_emulate_hypercall(struct kvm_vcpu *vcpu)
{
	unsigned long nr, a0, a1, a2, a3, ret;
	int op_64_bit;

	if (kvm_hv_hypercall_enabled(vcpu->kvm))
		return kvm_hv_hypercall(vcpu);

	nr = kvm_rax_read(vcpu);
	a0 = kvm_rbx_read(vcpu);
	a1 = kvm_rcx_read(vcpu);
	a2 = kvm_rdx_read(vcpu);
	a3 = kvm_rsi_read(vcpu);

	trace_kvm_hypercall(nr, a0, a1, a2, a3);

	op_64_bit = is_64_bit_mode(vcpu);
	if (!op_64_bit) {
		nr &= 0xFFFFFFFF;
		a0 &= 0xFFFFFFFF;
		a1 &= 0xFFFFFFFF;
		a2 &= 0xFFFFFFFF;
		a3 &= 0xFFFFFFFF;
	}

	if (kvm_x86_ops->get_cpl(vcpu) != 0) {
		ret = -KVM_EPERM;
		goto out;
	}

	switch (nr) {
	case KVM_HC_VAPIC_POLL_IRQ:
		ret = 0;
		break;
	case KVM_HC_KICK_CPU:
		kvm_pv_kick_cpu_op(vcpu->kvm, a0, a1);
		kvm_sched_yield(vcpu->kvm, a1);
		ret = 0;
		break;
#ifdef CONFIG_X86_64
	case KVM_HC_CLOCK_PAIRING:
		ret = kvm_pv_clock_pairing(vcpu, a0, a1);
		break;
#endif
	case KVM_HC_SEND_IPI:
		ret = kvm_pv_send_ipi(vcpu->kvm, a0, a1, a2, a3, op_64_bit);
		break;
	case KVM_HC_SCHED_YIELD:
		kvm_sched_yield(vcpu->kvm, a0);
		ret = 0;
		break;
	default:
		ret = -KVM_ENOSYS;
		break;
	}
out:
	if (!op_64_bit)
		ret = (u32)ret;
	kvm_rax_write(vcpu, ret);

	++vcpu->stat.hypercalls;
	return kvm_skip_emulated_instruction(vcpu);
}