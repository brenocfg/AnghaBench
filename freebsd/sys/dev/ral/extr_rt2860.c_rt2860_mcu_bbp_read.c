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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct rt2860_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RAL_BARRIER_WRITE (struct rt2860_softc*) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2860_BBP_CSR_KICK ; 
 int RT2860_BBP_CSR_READ ; 
 int RT2860_BBP_RW_PARALLEL ; 
 int /*<<< orphan*/  RT2860_H2M_BBPAGENT ; 
 int /*<<< orphan*/  RT2860_MCU_CMD_BBP ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rt2860_mcu_cmd (struct rt2860_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint8_t
rt2860_mcu_bbp_read(struct rt2860_softc *sc, uint8_t reg)
{
	uint32_t val;
	int ntries;

	for (ntries = 0; ntries < 100; ntries++) {
		if (!(RAL_READ(sc, RT2860_H2M_BBPAGENT) & RT2860_BBP_CSR_KICK))
			break;
		DELAY(1);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev,
		    "could not read from BBP through MCU\n");
		return 0;
	}

	RAL_WRITE(sc, RT2860_H2M_BBPAGENT, RT2860_BBP_RW_PARALLEL |
	    RT2860_BBP_CSR_KICK | RT2860_BBP_CSR_READ | reg << 8);
	RAL_BARRIER_WRITE(sc);

	rt2860_mcu_cmd(sc, RT2860_MCU_CMD_BBP, 0, 0);
	DELAY(1000);

	for (ntries = 0; ntries < 100; ntries++) {
		val = RAL_READ(sc, RT2860_H2M_BBPAGENT);
		if (!(val & RT2860_BBP_CSR_KICK))
			return val & 0xff;
		DELAY(1);
	}
	device_printf(sc->sc_dev, "could not read from BBP through MCU\n");

	return 0;
}