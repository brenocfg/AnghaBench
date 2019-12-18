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
struct sdhci_slot {TYPE_1__* curcmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_ERR_TIMEOUT ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_req_done (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_slot*,int) ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*) ; 

__attribute__((used)) static void
sdhci_timeout(void *arg)
{
	struct sdhci_slot *slot = arg;

	if (slot->curcmd != NULL) {
		slot_printf(slot, "Controller timeout\n");
		sdhci_dumpregs(slot);
		sdhci_reset(slot, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
		slot->curcmd->error = MMC_ERR_TIMEOUT;
		sdhci_req_done(slot);
	} else {
		slot_printf(slot, "Spurious timeout - no active command\n");
	}
}