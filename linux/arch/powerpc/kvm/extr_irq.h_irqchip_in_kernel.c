#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * xive; int /*<<< orphan*/ * xics; int /*<<< orphan*/ * mpic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline int irqchip_in_kernel(struct kvm *kvm)
{
	int ret = 0;

#ifdef CONFIG_KVM_MPIC
	ret = ret || (kvm->arch.mpic != NULL);
#endif
#ifdef CONFIG_KVM_XICS
	ret = ret || (kvm->arch.xics != NULL);
	ret = ret || (kvm->arch.xive != NULL);
#endif
	smp_rmb();
	return ret;
}