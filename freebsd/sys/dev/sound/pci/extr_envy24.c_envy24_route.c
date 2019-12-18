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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_MT_PSDOUT ; 
 int /*<<< orphan*/  ENVY24_MT_RECORD ; 
 int /*<<< orphan*/  ENVY24_MT_SPDOUT ; 
 int ENVY24_ROUTE_CLASS_MIX ; 
 int ENVY24_ROUTE_DAC_1 ; 
 int ENVY24_ROUTE_DAC_SPDIF ; 
 int ENVY24_ROUTE_LEFT ; 
 int ENVY24_ROUTE_RIGHT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int envy24_rdmt (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  envy24_wrmt (struct sc_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
envy24_route(struct sc_info *sc, int dac, int class, int adc, int rev)
{
	u_int32_t reg, mask;
	u_int32_t left, right;

#if(0)
	device_printf(sc->dev, "envy24_route(sc, %d, %d, %d, %d)\n",
	    dac, class, adc, rev);
#endif
	/* parameter pattern check */
	if (dac < 0 || ENVY24_ROUTE_DAC_SPDIF < dac)
		return -1;
	if (class == ENVY24_ROUTE_CLASS_MIX &&
	    (dac != ENVY24_ROUTE_DAC_1 && dac != ENVY24_ROUTE_DAC_SPDIF))
		return -1;
	if (rev) {
		left = ENVY24_ROUTE_RIGHT;
		right = ENVY24_ROUTE_LEFT;
	}
	else {
		left = ENVY24_ROUTE_LEFT;
		right = ENVY24_ROUTE_RIGHT;
	}

	if (dac == ENVY24_ROUTE_DAC_SPDIF) {
		reg = class | class << 2 |
			((adc << 1 | left) | left << 3) << 8 |
			((adc << 1 | right) | right << 3) << 12;
#if(0)
		device_printf(sc->dev, "envy24_route(): MT_SPDOUT-->0x%04x\n", reg);
#endif
		envy24_wrmt(sc, ENVY24_MT_SPDOUT, reg, 2);
	}
	else {
		mask = ~(0x0303 << dac * 2);
		reg = envy24_rdmt(sc, ENVY24_MT_PSDOUT, 2);
		reg = (reg & mask) | ((class | class << 8) << dac * 2);
#if(0)
		device_printf(sc->dev, "envy24_route(): MT_PSDOUT-->0x%04x\n", reg);
#endif
		envy24_wrmt(sc, ENVY24_MT_PSDOUT, reg, 2);
		mask = ~(0xff << dac * 8);
		reg = envy24_rdmt(sc, ENVY24_MT_RECORD, 4);
		reg = (reg & mask) |
			(((adc << 1 | left) | left << 3) |
			 ((adc << 1 | right) | right << 3) << 4) << dac * 8;
#if(0)
		device_printf(sc->dev, "envy24_route(): MT_RECORD-->0x%08x\n", reg);
#endif
		envy24_wrmt(sc, ENVY24_MT_RECORD, reg, 4);

		/* 6fire rear input init test */
		envy24_wrmt(sc, ENVY24_MT_RECORD, 0x00, 4);
	}

	return 0;
}