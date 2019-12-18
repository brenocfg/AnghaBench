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
struct awg_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BASIC_CTL_SOFT_RST ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EMAC_BASIC_CTL_1 ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int RD4 (struct awg_softc*,int /*<<< orphan*/ ) ; 
 int SOFT_RST_RETRY ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  awg_dump_regs (int /*<<< orphan*/ ) ; 
 scalar_t__ awg_phy_reset (int /*<<< orphan*/ ) ; 
 struct awg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
awg_reset(device_t dev)
{
	struct awg_softc *sc;
	int retry;

	sc = device_get_softc(dev);

	/* Reset PHY if necessary */
	if (awg_phy_reset(dev) != 0) {
		device_printf(dev, "failed to reset PHY\n");
		return (ENXIO);
	}

	/* Soft reset all registers and logic */
	WR4(sc, EMAC_BASIC_CTL_1, BASIC_CTL_SOFT_RST);

	/* Wait for soft reset bit to self-clear */
	for (retry = SOFT_RST_RETRY; retry > 0; retry--) {
		if ((RD4(sc, EMAC_BASIC_CTL_1) & BASIC_CTL_SOFT_RST) == 0)
			break;
		DELAY(10);
	}
	if (retry == 0) {
		device_printf(dev, "soft reset timed out\n");
#ifdef AWG_DEBUG
		awg_dump_regs(dev);
#endif
		return (ETIMEDOUT);
	}

	return (0);
}