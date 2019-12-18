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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct otus_softc {int /*<<< orphan*/  eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CMD_RREG ; 
 int AR_EEPROM_OFFSET ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 int htole32 (int) ; 
 int otus_cmd (struct otus_softc*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int) ; 

int
otus_read_eeprom(struct otus_softc *sc)
{
	uint32_t regs[8], reg;
	uint8_t *eep;
	int i, j, error;

	OTUS_LOCK_ASSERT(sc);

	/* Read EEPROM by blocks of 32 bytes. */
	eep = (uint8_t *)&sc->eeprom;
	reg = AR_EEPROM_OFFSET;
	for (i = 0; i < sizeof (sc->eeprom) / 32; i++) {
		for (j = 0; j < 8; j++, reg += 4)
			regs[j] = htole32(reg);
		error = otus_cmd(sc, AR_CMD_RREG, regs, sizeof regs, eep, 32);
		if (error != 0)
			break;
		eep += 32;
	}
	return error;
}