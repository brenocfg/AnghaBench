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
struct ahci_controller_irq {int r_irq_rid; struct ahci_controller* ctlr; } ;
struct ahci_controller {int /*<<< orphan*/  r_mem; TYPE_1__* interrupt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* function ) (void*) ;void* argument; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_IS ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_RBL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void
ahci_intr_one(void *data)
{
	struct ahci_controller_irq *irq = data;
	struct ahci_controller *ctlr = irq->ctlr;
	void *arg;
	int unit;

	unit = irq->r_irq_rid - 1;
	if ((arg = ctlr->interrupt[unit].argument))
	    ctlr->interrupt[unit].function(arg);
	/* AHCI declares level triggered IS. */
	ATA_OUTL(ctlr->r_mem, AHCI_IS, 1 << unit);
	ATA_RBL(ctlr->r_mem, AHCI_IS);
}