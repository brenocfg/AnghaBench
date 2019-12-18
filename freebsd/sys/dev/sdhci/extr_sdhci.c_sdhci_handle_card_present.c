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
struct sdhci_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_LOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_UNLOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_handle_card_present_locked (struct sdhci_slot*,int) ; 

void
sdhci_handle_card_present(struct sdhci_slot *slot, bool is_present)
{

	SDHCI_LOCK(slot);
	sdhci_handle_card_present_locked(slot, is_present);
	SDHCI_UNLOCK(slot);
}