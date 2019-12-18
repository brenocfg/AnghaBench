#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fp_save_area; TYPE_1__* regs; } ;
struct TYPE_7__ {TYPE_2__ thread; } ;
struct TYPE_5__ {int msr; } ;

/* Variables and functions */
 int MSR_FP ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  giveup_fpu (TYPE_3__*) ; 

__attribute__((used)) static inline void kvmppc_save_guest_fp(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_PPC_FPU
	if (current->thread.regs->msr & MSR_FP)
		giveup_fpu(current);
	current->thread.fp_save_area = NULL;
#endif
}