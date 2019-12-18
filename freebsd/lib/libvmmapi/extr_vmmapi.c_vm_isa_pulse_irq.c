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
struct vm_isa_irq {int atpic_irq; int ioapic_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_ISA_PULSE_IRQ ; 
 int /*<<< orphan*/  bzero (struct vm_isa_irq*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_isa_irq*) ; 

int
vm_isa_pulse_irq(struct vmctx *ctx, int atpic_irq, int ioapic_irq)
{
	struct vm_isa_irq isa_irq;

	bzero(&isa_irq, sizeof(struct vm_isa_irq));
	isa_irq.atpic_irq = atpic_irq;
	isa_irq.ioapic_irq = ioapic_irq;

	return (ioctl(ctx->fd, VM_ISA_PULSE_IRQ, &isa_irq));
}