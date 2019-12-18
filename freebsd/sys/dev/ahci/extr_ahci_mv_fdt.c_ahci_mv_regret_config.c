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
struct ahci_controller {int /*<<< orphan*/  r_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_VENDOR_SPECIFIC_0_ADDR ; 
 int /*<<< orphan*/  AHCI_VENDOR_SPECIFIC_0_DATA ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahci_mv_regret_config(struct ahci_controller *ctlr)
{

	/*
	 * Enable the regret bit to allow the SATA unit to regret
	 * a request that didn't receive an acknowledge
	 * and a avoid deadlock
	 */
	ATA_OUTL(ctlr->r_mem, AHCI_VENDOR_SPECIFIC_0_ADDR, 0x4);
	ATA_OUTL(ctlr->r_mem, AHCI_VENDOR_SPECIFIC_0_DATA, 0x80);
}