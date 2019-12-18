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
struct TYPE_6__ {int /*<<< orphan*/  vr; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_5__ {TYPE_3__* regs; int /*<<< orphan*/ * vr_save_area; } ;
struct TYPE_8__ {TYPE_1__ thread; } ;
struct TYPE_7__ {int msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ALTIVEC ; 
 int MSR_VEC ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  disable_kernel_altivec () ; 
 int /*<<< orphan*/  enable_kernel_altivec () ; 
 int /*<<< orphan*/  load_vr_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void kvmppc_load_guest_altivec(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_ALTIVEC
	if (cpu_has_feature(CPU_FTR_ALTIVEC)) {
		if (!(current->thread.regs->msr & MSR_VEC)) {
			enable_kernel_altivec();
			load_vr_state(&vcpu->arch.vr);
			disable_kernel_altivec();
			current->thread.vr_save_area = &vcpu->arch.vr;
			current->thread.regs->msr |= MSR_VEC;
		}
	}
#endif
}