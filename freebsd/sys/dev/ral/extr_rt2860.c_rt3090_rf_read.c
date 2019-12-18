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
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint8_t
rt3090_rf_read(struct rt2860_softc *sc, uint8_t reg)
{
	uint32_t tmp;
	int ntries;

	for (ntries = 0; ntries < 100; ntries++) {
		if (!(RAL_READ(sc, RT3070_RF_CSR_CFG) & RT3070_RF_KICK))
			break;
		DELAY(1);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "could not read RF register\n");
		return 0xff;
	}
	tmp = RT3070_RF_KICK | reg << 8;
	RAL_WRITE(sc, RT3070_RF_CSR_CFG, tmp);

	for (ntries = 0; ntries < 100; ntries++) {
		tmp = RAL_READ(sc, RT3070_RF_CSR_CFG);
		if (!(tmp & RT3070_RF_KICK))
			break;
		DELAY(1);
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev, "could not read RF register\n");
		return 0xff;
	}
	return tmp & 0xff;
}