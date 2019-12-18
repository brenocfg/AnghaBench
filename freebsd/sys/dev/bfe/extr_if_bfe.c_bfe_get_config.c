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
typedef  int u_int8_t ;
struct bfe_softc {int* bfe_enaddr; int bfe_phyaddr; int bfe_mdc_port; int /*<<< orphan*/  bfe_dma_offset; scalar_t__ bfe_core_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFE_PCI_DMA ; 
 int /*<<< orphan*/  bfe_read_eeprom (struct bfe_softc*,int*) ; 

__attribute__((used)) static void
bfe_get_config(struct bfe_softc *sc)
{
	u_int8_t eeprom[128];

	bfe_read_eeprom(sc, eeprom);

	sc->bfe_enaddr[0] = eeprom[79];
	sc->bfe_enaddr[1] = eeprom[78];
	sc->bfe_enaddr[2] = eeprom[81];
	sc->bfe_enaddr[3] = eeprom[80];
	sc->bfe_enaddr[4] = eeprom[83];
	sc->bfe_enaddr[5] = eeprom[82];

	sc->bfe_phyaddr = eeprom[90] & 0x1f;
	sc->bfe_mdc_port = (eeprom[90] >> 14) & 0x1;

	sc->bfe_core_unit = 0;
	sc->bfe_dma_offset = BFE_PCI_DMA;
}