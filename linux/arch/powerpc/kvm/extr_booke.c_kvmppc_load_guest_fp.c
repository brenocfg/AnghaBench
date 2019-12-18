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
struct TYPE_5__ {int /*<<< orphan*/  fp; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_6__ {TYPE_3__* regs; int /*<<< orphan*/ * fp_save_area; } ;
struct TYPE_8__ {TYPE_2__ thread; } ;
struct TYPE_7__ {int msr; } ;

/* Variables and functions */
 int MSR_FP ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  disable_kernel_fp () ; 
 int /*<<< orphan*/  enable_kernel_fp () ; 
 int /*<<< orphan*/  load_fp_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void kvmppc_load_guest_fp(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_PPC_FPU
	if (!(current->thread.regs->msr & MSR_FP)) {
		enable_kernel_fp();
		load_fp_state(&vcpu->arch.fp);
		disable_kernel_fp();
		current->thread.fp_save_area = &vcpu->arch.fp;
		current->thread.regs->msr |= MSR_FP;
	}
#endif
}