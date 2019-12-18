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
struct TYPE_2__ {int irqchip_mode; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int KVM_IRQCHIP_KERNEL ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline int irqchip_kernel(struct kvm *kvm)
{
	int mode = kvm->arch.irqchip_mode;

	/* Matches smp_wmb() when setting irqchip_mode */
	smp_rmb();
	return mode == KVM_IRQCHIP_KERNEL;
}