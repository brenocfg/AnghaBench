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
typedef  int uint16_t ;
struct sge_softc {int /*<<< orphan*/  sge_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct sge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EI_DATA ; 
 int EI_DATA_SHIFT ; 
 int EI_OFFSET ; 
 int EI_OFFSET_SHIFT ; 
 int EI_OP_RD ; 
 int EI_REQ ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ROMInterface ; 
 int SGE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint16_t
sge_read_eeprom(struct sge_softc *sc, int offset)
{
	uint32_t val;
	int i;

	KASSERT(offset <= EI_OFFSET, ("EEPROM offset too big"));
	CSR_WRITE_4(sc, ROMInterface,
	    EI_REQ | EI_OP_RD | (offset << EI_OFFSET_SHIFT));
	DELAY(500);
	for (i = 0; i < SGE_TIMEOUT; i++) {
		val = CSR_READ_4(sc, ROMInterface);
		if ((val & EI_REQ) == 0)
			break;
		DELAY(100);
	}
	if (i == SGE_TIMEOUT) {
		device_printf(sc->sge_dev,
		    "EEPROM read timeout : 0x%08x\n", val);
		return (0xffff);
	}

	return ((val & EI_DATA) >> EI_DATA_SHIFT);
}