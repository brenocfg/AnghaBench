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
struct TYPE_6__ {int /*<<< orphan*/  fpu_reload; } ;
struct TYPE_5__ {TYPE_1__* user_fpu; int /*<<< orphan*/  guest_fpu; } ;
struct kvm_vcpu {TYPE_3__ stat; TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_fpregs_to_fpstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_kernel_to_fpregs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpregs_lock () ; 
 int /*<<< orphan*/  fpregs_mark_activate () ; 
 int /*<<< orphan*/  fpregs_unlock () ; 
 int /*<<< orphan*/  trace_kvm_fpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_put_guest_fpu(struct kvm_vcpu *vcpu)
{
	fpregs_lock();

	copy_fpregs_to_fpstate(vcpu->arch.guest_fpu);
	copy_kernel_to_fpregs(&vcpu->arch.user_fpu->state);

	fpregs_mark_activate();
	fpregs_unlock();

	++vcpu->stat.fpu_reload;
	trace_kvm_fpu(0);
}