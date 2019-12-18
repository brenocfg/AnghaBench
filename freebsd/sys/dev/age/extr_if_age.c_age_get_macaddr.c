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
typedef  int uint32_t ;
struct age_softc {int* age_eaddr; int /*<<< orphan*/  age_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_PAR0 ; 
 int /*<<< orphan*/  AGE_PAR1 ; 
 int /*<<< orphan*/  AGE_SPI_CTRL ; 
 int /*<<< orphan*/  AGE_TWSI_CTRL ; 
 int CSR_READ_4 (struct age_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PCIY_VPD ; 
 int SPI_VPD_ENB ; 
 int TWSI_CTRL_SW_LD_START ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
age_get_macaddr(struct age_softc *sc)
{
	uint32_t ea[2], reg;
	int i, vpdc;

	reg = CSR_READ_4(sc, AGE_SPI_CTRL);
	if ((reg & SPI_VPD_ENB) != 0) {
		/* Get VPD stored in TWSI EEPROM. */
		reg &= ~SPI_VPD_ENB;
		CSR_WRITE_4(sc, AGE_SPI_CTRL, reg);
	}

	if (pci_find_cap(sc->age_dev, PCIY_VPD, &vpdc) == 0) {
		/*
		 * PCI VPD capability found, let TWSI reload EEPROM.
		 * This will set ethernet address of controller.
		 */
		CSR_WRITE_4(sc, AGE_TWSI_CTRL, CSR_READ_4(sc, AGE_TWSI_CTRL) |
		    TWSI_CTRL_SW_LD_START);
		for (i = 100; i > 0; i--) {
			DELAY(1000);
			reg = CSR_READ_4(sc, AGE_TWSI_CTRL);
			if ((reg & TWSI_CTRL_SW_LD_START) == 0)
				break;
		}
		if (i == 0)
			device_printf(sc->age_dev,
			    "reloading EEPROM timeout!\n");
	} else {
		if (bootverbose)
			device_printf(sc->age_dev,
			    "PCI VPD capability not found!\n");
	}

	ea[0] = CSR_READ_4(sc, AGE_PAR0);
	ea[1] = CSR_READ_4(sc, AGE_PAR1);
	sc->age_eaddr[0] = (ea[1] >> 8) & 0xFF;
	sc->age_eaddr[1] = (ea[1] >> 0) & 0xFF;
	sc->age_eaddr[2] = (ea[0] >> 24) & 0xFF;
	sc->age_eaddr[3] = (ea[0] >> 16) & 0xFF;
	sc->age_eaddr[4] = (ea[0] >> 8) & 0xFF;
	sc->age_eaddr[5] = (ea[0] >> 0) & 0xFF;
}