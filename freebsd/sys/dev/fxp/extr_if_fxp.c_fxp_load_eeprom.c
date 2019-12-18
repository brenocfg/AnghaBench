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
typedef  scalar_t__ uint16_t ;
struct fxp_softc {scalar_t__* eeprom; int eeprom_size; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fxp_read_eeprom (struct fxp_softc*,scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fxp_load_eeprom(struct fxp_softc *sc)
{
	int i;
	uint16_t cksum;

	fxp_read_eeprom(sc, sc->eeprom, 0, 1 << sc->eeprom_size);
	cksum = 0;
	for (i = 0; i < (1 << sc->eeprom_size) - 1; i++)
		cksum += sc->eeprom[i];
	cksum = 0xBABA - cksum;
	if (cksum != sc->eeprom[(1 << sc->eeprom_size) - 1])
		device_printf(sc->dev,
		    "EEPROM checksum mismatch! (0x%04x -> 0x%04x)\n",
		    cksum, sc->eeprom[(1 << sc->eeprom_size) - 1]);
}