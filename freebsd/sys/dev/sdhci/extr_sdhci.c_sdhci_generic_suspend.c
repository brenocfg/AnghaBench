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
struct sdhci_slot {int /*<<< orphan*/  opt; int /*<<< orphan*/  retune_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_LOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_TUNING_ENABLED ; 
 int /*<<< orphan*/  SDHCI_UNLOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_slot*,int /*<<< orphan*/ ) ; 

int
sdhci_generic_suspend(struct sdhci_slot *slot)
{

	/*
	 * We expect the MMC layer to issue initial tuning after resume.
	 * Otherwise, we'd need to indicate re-tuning including circuit reset
	 * being required at least for re-tuning modes 1 and 2 ourselves.
	 */
	callout_drain(&slot->retune_callout);
	SDHCI_LOCK(slot);
	slot->opt &= ~SDHCI_TUNING_ENABLED;
	sdhci_reset(slot, SDHCI_RESET_ALL);
	SDHCI_UNLOCK(slot);

	return (0);
}