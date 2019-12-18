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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct sdhci_slot {int quirks; scalar_t__ power; scalar_t__ clock; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RD1 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_GET_CARD_PRESENT (int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 int SDHCI_QUIRK_CLOCK_BEFORE_RESET ; 
 int SDHCI_QUIRK_NO_CARD_NO_RESET ; 
 int SDHCI_QUIRK_WAITFOR_RESET_ASSERTED ; 
 int SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_SOFTWARE_RESET ; 
 int /*<<< orphan*/  WR1 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_set_clock (struct sdhci_slot*,scalar_t__) ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*,int) ; 

__attribute__((used)) static void
sdhci_reset(struct sdhci_slot *slot, uint8_t mask)
{
	int timeout;
	uint32_t clock;

	if (slot->quirks & SDHCI_QUIRK_NO_CARD_NO_RESET) {
		if (!SDHCI_GET_CARD_PRESENT(slot->bus, slot))
			return;
	}

	/* Some controllers need this kick or reset won't work. */
	if ((mask & SDHCI_RESET_ALL) == 0 &&
	    (slot->quirks & SDHCI_QUIRK_CLOCK_BEFORE_RESET)) {
		/* This is to force an update */
		clock = slot->clock;
		slot->clock = 0;
		sdhci_set_clock(slot, clock);
	}

	if (mask & SDHCI_RESET_ALL) {
		slot->clock = 0;
		slot->power = 0;
	}

	WR1(slot, SDHCI_SOFTWARE_RESET, mask);

	if (slot->quirks & SDHCI_QUIRK_WAITFOR_RESET_ASSERTED) {
		/*
		 * Resets on TI OMAPs and AM335x are incompatible with SDHCI
		 * specification.  The reset bit has internal propagation delay,
		 * so a fast read after write returns 0 even if reset process is
		 * in progress.  The workaround is to poll for 1 before polling
		 * for 0.  In the worst case, if we miss seeing it asserted the
		 * time we spent waiting is enough to ensure the reset finishes.
		 */
		timeout = 10000;
		while ((RD1(slot, SDHCI_SOFTWARE_RESET) & mask) != mask) {
			if (timeout <= 0)
				break;
			timeout--;
			DELAY(1);
		}
	}

	/* Wait max 100 ms */
	timeout = 10000;
	/* Controller clears the bits when it's done */
	while (RD1(slot, SDHCI_SOFTWARE_RESET) & mask) {
		if (timeout <= 0) {
			slot_printf(slot, "Reset 0x%x never completed.\n",
			    mask);
			sdhci_dumpregs(slot);
			return;
		}
		timeout--;
		DELAY(10);
	}
}