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
struct ste_softc {int /*<<< orphan*/  ste_dev; } ;

/* Variables and functions */
 int CSR_READ_2 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int STE_EECTL_BUSY ; 
 int /*<<< orphan*/  STE_EEPROM_CTL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ste_eeprom_wait(struct ste_softc *sc)
{
	int i;

	DELAY(1000);

	for (i = 0; i < 100; i++) {
		if (CSR_READ_2(sc, STE_EEPROM_CTL) & STE_EECTL_BUSY)
			DELAY(1000);
		else
			break;
	}

	if (i == 100) {
		device_printf(sc->ste_dev, "eeprom failed to come ready\n");
		return (1);
	}

	return (0);
}