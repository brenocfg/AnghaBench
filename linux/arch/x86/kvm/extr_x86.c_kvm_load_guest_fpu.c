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
struct TYPE_4__ {TYPE_1__* guest_fpu; int /*<<< orphan*/  user_fpu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFEATURE_MASK_PKRU ; 
 int /*<<< orphan*/  __copy_kernel_to_fpregs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_fpregs_to_fpstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpregs_lock () ; 
 int /*<<< orphan*/  fpregs_mark_activate () ; 
 int /*<<< orphan*/  fpregs_unlock () ; 
 int /*<<< orphan*/  trace_kvm_fpu (int) ; 

__attribute__((used)) static void kvm_load_guest_fpu(struct kvm_vcpu *vcpu)
{
	fpregs_lock();

	copy_fpregs_to_fpstate(vcpu->arch.user_fpu);
	/* PKRU is separately restored in kvm_x86_ops->run.  */
	__copy_kernel_to_fpregs(&vcpu->arch.guest_fpu->state,
				~XFEATURE_MASK_PKRU);

	fpregs_mark_activate();
	fpregs_unlock();

	trace_kvm_fpu(1);
}