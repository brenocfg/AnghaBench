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
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm {int dummy; } ;
struct TYPE_2__ {int (* update_pi_irte ) (struct kvm*,unsigned int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm*,unsigned int,int /*<<< orphan*/ ,int) ; 

int kvm_arch_update_irqfd_routing(struct kvm *kvm, unsigned int host_irq,
				   uint32_t guest_irq, bool set)
{
	return kvm_x86_ops->update_pi_irte(kvm, host_irq, guest_irq, set);
}