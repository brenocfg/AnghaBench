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
typedef  int u32 ;
struct TYPE_6__ {int guest_debug_dr7; int dr7; int dr6; int /*<<< orphan*/  db; int /*<<< orphan*/  eff_db; } ;
struct kvm_vcpu {int guest_debug; TYPE_3__ arch; struct kvm_run* run; } ;
struct TYPE_4__ {int dr6; unsigned long pc; int /*<<< orphan*/  exception; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; TYPE_2__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_VECTOR ; 
 int DR6_FIXED_1 ; 
 int DR6_RTM ; 
 int DR7_BP_EN_MASK ; 
 int DR_TRAP_BITS ; 
 int /*<<< orphan*/  KVM_EXIT_DEBUG ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 int X86_EFLAGS_RF ; 
 unsigned long kvm_get_linear_rip (struct kvm_vcpu*) ; 
 int kvm_get_rflags (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvm_vcpu_check_hw_bp (unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool kvm_vcpu_check_breakpoint(struct kvm_vcpu *vcpu, int *r)
{
	if (unlikely(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP) &&
	    (vcpu->arch.guest_debug_dr7 & DR7_BP_EN_MASK)) {
		struct kvm_run *kvm_run = vcpu->run;
		unsigned long eip = kvm_get_linear_rip(vcpu);
		u32 dr6 = kvm_vcpu_check_hw_bp(eip, 0,
					   vcpu->arch.guest_debug_dr7,
					   vcpu->arch.eff_db);

		if (dr6 != 0) {
			kvm_run->debug.arch.dr6 = dr6 | DR6_FIXED_1 | DR6_RTM;
			kvm_run->debug.arch.pc = eip;
			kvm_run->debug.arch.exception = DB_VECTOR;
			kvm_run->exit_reason = KVM_EXIT_DEBUG;
			*r = 0;
			return true;
		}
	}

	if (unlikely(vcpu->arch.dr7 & DR7_BP_EN_MASK) &&
	    !(kvm_get_rflags(vcpu) & X86_EFLAGS_RF)) {
		unsigned long eip = kvm_get_linear_rip(vcpu);
		u32 dr6 = kvm_vcpu_check_hw_bp(eip, 0,
					   vcpu->arch.dr7,
					   vcpu->arch.db);

		if (dr6 != 0) {
			vcpu->arch.dr6 &= ~DR_TRAP_BITS;
			vcpu->arch.dr6 |= dr6 | DR6_RTM;
			kvm_queue_exception(vcpu, DB_VECTOR);
			*r = 1;
			return true;
		}
	}

	return false;
}