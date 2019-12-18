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
struct TYPE_3__ {int /*<<< orphan*/  wbinvd_dirty_mask; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ (* has_wbinvd_exit ) () ;} ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  need_emulate_wbinvd (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_many (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  wbinvd_ipi ; 

__attribute__((used)) static int kvm_emulate_wbinvd_noskip(struct kvm_vcpu *vcpu)
{
	if (!need_emulate_wbinvd(vcpu))
		return X86EMUL_CONTINUE;

	if (kvm_x86_ops->has_wbinvd_exit()) {
		int cpu = get_cpu();

		cpumask_set_cpu(cpu, vcpu->arch.wbinvd_dirty_mask);
		smp_call_function_many(vcpu->arch.wbinvd_dirty_mask,
				wbinvd_ipi, NULL, 1);
		put_cpu();
		cpumask_clear(vcpu->arch.wbinvd_dirty_mask);
	} else
		wbinvd();
	return X86EMUL_CONTINUE;
}