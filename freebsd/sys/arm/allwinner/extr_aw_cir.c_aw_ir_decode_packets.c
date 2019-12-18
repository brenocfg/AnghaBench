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
struct aw_ir_softc {int dcnt; unsigned char* buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AW_IR_ACTIVE_T ; 
 scalar_t__ AW_IR_ACTIVE_T_C ; 
 unsigned long AW_IR_DMAX ; 
 unsigned long AW_IR_DMID ; 
 unsigned long AW_IR_ERROR_CODE ; 
 unsigned long AW_IR_L0_MIN ; 
 unsigned long AW_IR_L1_MIN ; 
 unsigned long AW_IR_PMAX ; 
 unsigned char PERIOD_MASK ; 
 unsigned char VAL_MASK ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static unsigned long
aw_ir_decode_packets(struct aw_ir_softc *sc)
{
	unsigned long len, code;
	unsigned char val, last;
	unsigned int active_delay;
	int i, bitcount;

	if (bootverbose)
		device_printf(sc->dev, "sc->dcnt = %d\n", sc->dcnt);

	/* Find Lead 1 (bit separator) */
	active_delay = (AW_IR_ACTIVE_T + 1) * (AW_IR_ACTIVE_T_C ? 128 : 1);
	len = 0;
	len += (active_delay >> 1);
	if (bootverbose)
		device_printf(sc->dev, "Initial len: %ld\n", len);
	for (i = 0;  i < sc->dcnt; i++) {
		val = sc->buf[i];
		if (val & VAL_MASK)
			len += val & PERIOD_MASK;
		else {
			if (len > AW_IR_L1_MIN)
				break;
			len = 0;
		}
	}
	if (bootverbose)
		device_printf(sc->dev, "len = %ld\n", len);
	if ((val & VAL_MASK) || (len <= AW_IR_L1_MIN)) {
		if (bootverbose)
			device_printf(sc->dev, "Bit separator error\n");
		goto error_code;
	}

	/* Find Lead 0 (bit length) */
	len = 0;
	for (; i < sc->dcnt; i++) {
		val = sc->buf[i];
		if (val & VAL_MASK) {
			if(len > AW_IR_L0_MIN)
				break;
			len = 0;
		} else
			len += val & PERIOD_MASK;
	}
	if ((!(val & VAL_MASK)) || (len <= AW_IR_L0_MIN)) {
		if (bootverbose)
			device_printf(sc->dev, "Bit length error\n");
		goto error_code;
	}

	/* Start decoding */
	code = 0;
	bitcount = 0;
	last = 1;
	len = 0;
	for (; i < sc->dcnt; i++) {
		val = sc->buf[i];
		if (last) {
			if (val & VAL_MASK)
				len += val & PERIOD_MASK;
			else {
				if (len > AW_IR_PMAX) {
					if (bootverbose)
						device_printf(sc->dev,
						    "Pulse error\n");
					goto error_code;
				}
				last = 0;
				len = val & PERIOD_MASK;
			}
		} else {
			if (val & VAL_MASK) {
				if (len > AW_IR_DMAX) {
					if (bootverbose)
						device_printf(sc->dev,
						    "Distant error\n");
					goto error_code;
				} else {
					if (len > AW_IR_DMID) {
						/* Decode */
						code |= 1 << bitcount;
					}
					bitcount++;
					if (bitcount == 32)
						break;  /* Finish decoding */
				}
				last = 1;
				len = val & PERIOD_MASK;
			} else
				len += val & PERIOD_MASK;
		}
	}
	return (code);

error_code:

	return (AW_IR_ERROR_CODE);
}