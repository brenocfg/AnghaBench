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
typedef  int /*<<< orphan*/  vmirq ;
struct vmctx {int /*<<< orphan*/  fd; } ;
struct vm_lapic_irq {int cpuid; int vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_LAPIC_IRQ ; 
 int /*<<< orphan*/  bzero (struct vm_lapic_irq*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_lapic_irq*) ; 

int
vm_lapic_irq(struct vmctx *ctx, int vcpu, int vector)
{
	struct vm_lapic_irq vmirq;

	bzero(&vmirq, sizeof(vmirq));
	vmirq.cpuid = vcpu;
	vmirq.vector = vector;

	return (ioctl(ctx->fd, VM_LAPIC_IRQ, &vmirq));
}