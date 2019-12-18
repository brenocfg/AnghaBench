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
struct stge_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int EC_EepromAddress (int) ; 
 int EC_EepromOpcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_OP_RR ; 
 int /*<<< orphan*/  STGE_EepromCtrl ; 
 int /*<<< orphan*/  STGE_EepromData ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stge_eeprom_wait (struct stge_softc*) ; 

__attribute__((used)) static void
stge_read_eeprom(struct stge_softc *sc, int offset, uint16_t *data)
{

	if (stge_eeprom_wait(sc))
		device_printf(sc->sc_dev, "EEPROM failed to come ready\n");

	CSR_WRITE_2(sc, STGE_EepromCtrl,
	    EC_EepromAddress(offset) | EC_EepromOpcode(EC_OP_RR));
	if (stge_eeprom_wait(sc))
		device_printf(sc->sc_dev, "EEPROM read timed out\n");
	*data = CSR_READ_2(sc, STGE_EepromData);
}