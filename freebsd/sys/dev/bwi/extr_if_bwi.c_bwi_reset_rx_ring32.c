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
typedef  scalar_t__ uint32_t ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 scalar_t__ BWI_RX32_CTRL ; 
 scalar_t__ BWI_RX32_RINGINFO ; 
 scalar_t__ BWI_RX32_STATUS ; 
 scalar_t__ BWI_RX32_STATUS_STATE_DISABLED ; 
 int /*<<< orphan*/  BWI_RX32_STATUS_STATE_MASK ; 
 scalar_t__ CSR_READ_4 (struct bwi_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int NRETRY ; 
 scalar_t__ __SHIFTOUT (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bwi_reset_rx_ring32(struct bwi_softc *sc, uint32_t rx_ctrl)
{
	int i;

	CSR_WRITE_4(sc, rx_ctrl + BWI_RX32_CTRL, 0);

#define NRETRY 10

	for (i = 0; i < NRETRY; ++i) {
		uint32_t status;

		status = CSR_READ_4(sc, rx_ctrl + BWI_RX32_STATUS);
		if (__SHIFTOUT(status, BWI_RX32_STATUS_STATE_MASK) ==
		    BWI_RX32_STATUS_STATE_DISABLED)
			break;

		DELAY(1000);
	}
	if (i == NRETRY)
		device_printf(sc->sc_dev, "reset rx ring timedout\n");

#undef NRETRY

	CSR_WRITE_4(sc, rx_ctrl + BWI_RX32_RINGINFO, 0);
}