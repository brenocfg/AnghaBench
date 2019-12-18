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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct urtw_softc {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int URTW_BB_HOST_BANG_CLK ; 
 int URTW_BB_HOST_BANG_EN ; 
 int URTW_BB_HOST_BANG_RW ; 
 int /*<<< orphan*/  URTW_RF_PINS_ENABLE ; 
 int /*<<< orphan*/  URTW_RF_PINS_INPUT ; 
 int URTW_RF_PINS_MAGIC4 ; 
 int /*<<< orphan*/  URTW_RF_PINS_OUTPUT ; 
 int URTW_RF_PINS_OUTPUT_MAGIC1 ; 
 int /*<<< orphan*/  URTW_RF_PINS_SELECT ; 
 int /*<<< orphan*/  urtw_read16_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_write16_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225_read(struct urtw_softc *sc, uint8_t addr, uint32_t *data)
{
	int i;
	int16_t bit;
	uint8_t rlen = 12, wlen = 6;
	uint16_t o1, o2, o3, tmp;
	uint32_t d2w = ((uint32_t)(addr & 0x1f)) << 27;
	uint32_t mask = 0x80000000, value = 0;
	usb_error_t error;

	urtw_read16_m(sc, URTW_RF_PINS_OUTPUT, &o1);
	urtw_read16_m(sc, URTW_RF_PINS_ENABLE, &o2);
	urtw_read16_m(sc, URTW_RF_PINS_SELECT, &o3);
	urtw_write16_m(sc, URTW_RF_PINS_ENABLE, o2 | URTW_RF_PINS_MAGIC4);
	urtw_write16_m(sc, URTW_RF_PINS_SELECT, o3 | URTW_RF_PINS_MAGIC4);
	o1 &= ~URTW_RF_PINS_MAGIC4;
	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, o1 | URTW_BB_HOST_BANG_EN);
	DELAY(5);
	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, o1);
	DELAY(5);

	for (i = 0; i < (wlen / 2); i++, mask = mask >> 1) {
		bit = ((d2w & mask) != 0) ? 1 : 0;

		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1);
		DELAY(2);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1 |
		    URTW_BB_HOST_BANG_CLK);
		DELAY(2);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1 |
		    URTW_BB_HOST_BANG_CLK);
		DELAY(2);
		mask = mask >> 1;
		if (i == 2)
			break;
		bit = ((d2w & mask) != 0) ? 1 : 0;
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1 |
		    URTW_BB_HOST_BANG_CLK);
		DELAY(2);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1 |
		    URTW_BB_HOST_BANG_CLK);
		DELAY(2);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1);
		DELAY(1);
	}
	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1 | URTW_BB_HOST_BANG_RW |
	    URTW_BB_HOST_BANG_CLK);
	DELAY(2);
	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, bit | o1 | URTW_BB_HOST_BANG_RW);
	DELAY(2);
	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, o1 | URTW_BB_HOST_BANG_RW);
	DELAY(2);

	mask = 0x800;
	for (i = 0; i < rlen; i++, mask = mask >> 1) {
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT,
		    o1 | URTW_BB_HOST_BANG_RW);
		DELAY(2);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT,
		    o1 | URTW_BB_HOST_BANG_RW | URTW_BB_HOST_BANG_CLK);
		DELAY(2);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT,
		    o1 | URTW_BB_HOST_BANG_RW | URTW_BB_HOST_BANG_CLK);
		DELAY(2);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT,
		    o1 | URTW_BB_HOST_BANG_RW | URTW_BB_HOST_BANG_CLK);
		DELAY(2);

		urtw_read16_m(sc, URTW_RF_PINS_INPUT, &tmp);
		value |= ((tmp & URTW_BB_HOST_BANG_CLK) ? mask : 0);
		urtw_write16_m(sc, URTW_RF_PINS_OUTPUT,
		    o1 | URTW_BB_HOST_BANG_RW);
		DELAY(2);
	}

	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, o1 | URTW_BB_HOST_BANG_EN |
	    URTW_BB_HOST_BANG_RW);
	DELAY(2);

	urtw_write16_m(sc, URTW_RF_PINS_ENABLE, o2);
	urtw_write16_m(sc, URTW_RF_PINS_SELECT, o3);
	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, URTW_RF_PINS_OUTPUT_MAGIC1);

	if (data != NULL)
		*data = value;
fail:
	return (error);
}