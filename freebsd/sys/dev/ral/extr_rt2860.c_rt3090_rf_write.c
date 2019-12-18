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
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT3070_RF_CSR_CFG ; 
 int RT3070_RF_KICK ; 
 int RT3070_RF_WRITE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

void
rt3090_rf_write(struct rt2860_softc *sc, uint8_t reg, uint8_t val)
{
	uint32_t tmp;
	int ntries;

	for (ntries = 0; ntries < 10; ntries++) {
		if (!(RAL_READ(sc, RT3070_RF_CSR_CFG) & RT3070_RF_KICK))
			break;
		DELAY(10);
	}
	if (ntries == 10) {
		device_printf(sc->sc_dev, "could not write to RF\n");
		return;
	}

	tmp = RT3070_RF_WRITE | RT3070_RF_KICK | reg << 8 | val;
	RAL_WRITE(sc, RT3070_RF_CSR_CFG, tmp);
}