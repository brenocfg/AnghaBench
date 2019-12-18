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
typedef  int /*<<< orphan*/  uint16_t ;
struct sdhci_slot {int /*<<< orphan*/  curcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdhci_acmd_irq(struct sdhci_slot *slot, uint16_t acmd_err)
{

	if (!slot->curcmd) {
		slot_printf(slot, "Got AutoCMD12 error 0x%04x, but "
		    "there is no active command.\n", acmd_err);
		sdhci_dumpregs(slot);
		return;
	}
	slot_printf(slot, "Got AutoCMD12 error 0x%04x\n", acmd_err);
	sdhci_reset(slot, SDHCI_RESET_CMD);
}