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
struct sdhci_slot {int /*<<< orphan*/  card_poll_callout; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_CARD_PRESENT_TICKS ; 
 int /*<<< orphan*/  SDHCI_GET_CARD_PRESENT (int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_handle_card_present (struct sdhci_slot*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdhci_card_poll(void *arg)
{
	struct sdhci_slot *slot = arg;

	sdhci_handle_card_present(slot,
	    SDHCI_GET_CARD_PRESENT(slot->bus, slot));
	callout_reset(&slot->card_poll_callout, SDHCI_CARD_PRESENT_TICKS,
	    sdhci_card_poll, slot);
}