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
struct vm_ioapic_irq {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_IOAPIC_PULSE_IRQ ; 
 int /*<<< orphan*/  bzero (struct vm_ioapic_irq*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_ioapic_irq*) ; 

int
vm_ioapic_pulse_irq(struct vmctx *ctx, int irq)
{
	struct vm_ioapic_irq ioapic_irq;

	bzero(&ioapic_irq, sizeof(struct vm_ioapic_irq));
	ioapic_irq.irq = irq;

	return (ioctl(ctx->fd, VM_IOAPIC_PULSE_IRQ, &ioapic_irq));
}