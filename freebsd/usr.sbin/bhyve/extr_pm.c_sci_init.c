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
struct vmctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEVEL_TRIGGER ; 
 int /*<<< orphan*/  SCI_INT ; 
 int /*<<< orphan*/  pci_irq_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_isa_set_irq_trigger (struct vmctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sci_init(struct vmctx *ctx)
{

	/*
	 * Mark ACPI's SCI as level trigger and bump its use count
	 * in the PIRQ router.
	 */
	pci_irq_use(SCI_INT);
	vm_isa_set_irq_trigger(ctx, SCI_INT, LEVEL_TRIGGER);
}