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
typedef  int u_char ;
struct sdhci_slot {int power; int quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
#define  MMC_OCR_290_300 132 
#define  MMC_OCR_300_310 131 
#define  MMC_OCR_320_330 130 
#define  MMC_OCR_330_340 129 
#define  MMC_OCR_LOW_VOLTAGE 128 
 int RD1 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int SDHCI_POWER_180 ; 
 int SDHCI_POWER_300 ; 
 int SDHCI_POWER_330 ; 
 int /*<<< orphan*/  SDHCI_POWER_CONTROL ; 
 int SDHCI_POWER_ON ; 
 int SDHCI_QUIRK_INTEL_POWER_UP_RESET ; 
 int /*<<< orphan*/  WR1 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*) ; 

__attribute__((used)) static void
sdhci_set_power(struct sdhci_slot *slot, u_char power)
{
	int i;
	uint8_t pwr;

	if (slot->power == power)
		return;

	slot->power = power;

	/* Turn off the power. */
	pwr = 0;
	WR1(slot, SDHCI_POWER_CONTROL, pwr);
	/* If power down requested - leave it so. */
	if (power == 0)
		return;
	/* Set voltage. */
	switch (1 << power) {
	case MMC_OCR_LOW_VOLTAGE:
		pwr |= SDHCI_POWER_180;
		break;
	case MMC_OCR_290_300:
	case MMC_OCR_300_310:
		pwr |= SDHCI_POWER_300;
		break;
	case MMC_OCR_320_330:
	case MMC_OCR_330_340:
		pwr |= SDHCI_POWER_330;
		break;
	}
	WR1(slot, SDHCI_POWER_CONTROL, pwr);
	/*
	 * Turn on VDD1 power.  Note that at least some Intel controllers can
	 * fail to enable bus power on the first try after transiting from D3
	 * to D0, so we give them up to 2 ms.
	 */
	pwr |= SDHCI_POWER_ON;
	for (i = 0; i < 20; i++) {
		WR1(slot, SDHCI_POWER_CONTROL, pwr);
		if (RD1(slot, SDHCI_POWER_CONTROL) & SDHCI_POWER_ON)
			break;
		DELAY(100);
	}
	if (!(RD1(slot, SDHCI_POWER_CONTROL) & SDHCI_POWER_ON))
		slot_printf(slot, "Bus power failed to enable\n");

	if (slot->quirks & SDHCI_QUIRK_INTEL_POWER_UP_RESET) {
		WR1(slot, SDHCI_POWER_CONTROL, pwr | 0x10);
		DELAY(10);
		WR1(slot, SDHCI_POWER_CONTROL, pwr);
		DELAY(300);
	}
}