#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_isa_irq_trigger {int atpic_irq; int trigger; } ;
typedef  enum vm_intr_trigger { ____Placeholder_vm_intr_trigger } vm_intr_trigger ;

/* Variables and functions */
 int /*<<< orphan*/  VM_ISA_SET_IRQ_TRIGGER ; 
 int /*<<< orphan*/  bzero (struct vm_isa_irq_trigger*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_isa_irq_trigger*) ; 

int
vm_isa_set_irq_trigger(struct vmctx *ctx, int atpic_irq,
    enum vm_intr_trigger trigger)
{
	struct vm_isa_irq_trigger isa_irq_trigger;

	bzero(&isa_irq_trigger, sizeof(struct vm_isa_irq_trigger));
	isa_irq_trigger.atpic_irq = atpic_irq;
	isa_irq_trigger.trigger = trigger;

	return (ioctl(ctx->fd, VM_ISA_SET_IRQ_TRIGGER, &isa_irq_trigger));
}