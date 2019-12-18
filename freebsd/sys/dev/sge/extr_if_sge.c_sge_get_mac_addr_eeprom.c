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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct sge_softc {int /*<<< orphan*/  sge_flags; int /*<<< orphan*/  sge_dev; } ;

/* Variables and functions */
 scalar_t__ EEPROMInfo ; 
 scalar_t__ EEPROMMACAddr ; 
 scalar_t__ EEPROMSignature ; 
 int EINVAL ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  SGE_FLAG_RGMII ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int sge_read_eeprom (struct sge_softc*,scalar_t__) ; 

__attribute__((used)) static int
sge_get_mac_addr_eeprom(struct sge_softc *sc, uint8_t *dest)
{
	uint16_t val;
	int i;

	val = sge_read_eeprom(sc, EEPROMSignature);
	if (val == 0xffff || val == 0) {
		device_printf(sc->sge_dev,
		    "invalid EEPROM signature : 0x%04x\n", val);
		return (EINVAL);
	}

	for (i = 0; i < ETHER_ADDR_LEN; i += 2) {
		val = sge_read_eeprom(sc, EEPROMMACAddr + i / 2);
		dest[i + 0] = (uint8_t)val;
		dest[i + 1] = (uint8_t)(val >> 8);
	}

	if ((sge_read_eeprom(sc, EEPROMInfo) & 0x80) != 0)
		sc->sge_flags |= SGE_FLAG_RGMII;
	return (0);
}