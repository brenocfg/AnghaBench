#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long guest_owned_ext; int /*<<< orphan*/  vr; int /*<<< orphan*/  fp; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_6__ {TYPE_1__* regs; } ;
struct TYPE_8__ {TYPE_2__ thread; } ;
struct TYPE_5__ {unsigned long msr; } ;

/* Variables and functions */
 unsigned long MSR_FP ; 
 unsigned long MSR_VEC ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  disable_kernel_altivec () ; 
 int /*<<< orphan*/  disable_kernel_fp () ; 
 int /*<<< orphan*/  enable_kernel_altivec () ; 
 int /*<<< orphan*/  enable_kernel_fp () ; 
 int /*<<< orphan*/  load_fp_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_vr_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static void kvmppc_handle_lost_ext(struct kvm_vcpu *vcpu)
{
	unsigned long lost_ext;

	lost_ext = vcpu->arch.guest_owned_ext & ~current->thread.regs->msr;
	if (!lost_ext)
		return;

	if (lost_ext & MSR_FP) {
		preempt_disable();
		enable_kernel_fp();
		load_fp_state(&vcpu->arch.fp);
		disable_kernel_fp();
		preempt_enable();
	}
#ifdef CONFIG_ALTIVEC
	if (lost_ext & MSR_VEC) {
		preempt_disable();
		enable_kernel_altivec();
		load_vr_state(&vcpu->arch.vr);
		disable_kernel_altivec();
		preempt_enable();
	}
#endif
	current->thread.regs->msr |= lost_ext;
}