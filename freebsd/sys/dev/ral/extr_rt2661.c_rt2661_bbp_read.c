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
struct rt2661_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2661_BBP_BUSY ; 
 int RT2661_BBP_READ ; 
 int /*<<< orphan*/  RT2661_PHY_CSR3 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint8_t
rt2661_bbp_read(struct rt2661_softc *sc, uint8_t reg)
{
	uint32_t val;
	int ntries;

	for (ntries = 0; ntries < 100; ntries++) {
		if (!(RAL_READ(sc, RT2661_PHY_CSR3) & RT2661_BBP_BUSY))
			break;
		DELAY(1);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "could not read from BBP\n");
		return 0;
	}

	val = RT2661_BBP_BUSY | RT2661_BBP_READ | reg << 8;
	RAL_WRITE(sc, RT2661_PHY_CSR3, val);

	for (ntries = 0; ntries < 100; ntries++) {
		val = RAL_READ(sc, RT2661_PHY_CSR3);
		if (!(val & RT2661_BBP_BUSY))
			return val & 0xff;
		DELAY(1);
	}

	device_printf(sc->sc_dev, "could not read from BBP\n");
	return 0;
}