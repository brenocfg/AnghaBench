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
typedef  int u_int ;
struct mii_softc {int /*<<< orphan*/  mii_dev; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int MII_BMCR ; 
 int PHY_READ (struct mii_softc*,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct mii_softc*,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
smcphy_reset(struct mii_softc *sc)
{
	u_int	bmcr;
	int	timeout;

	PHY_WRITE(sc, MII_BMCR, BMCR_RESET);

	for (timeout = 2; timeout > 0; timeout--) {
		DELAY(50000);
		bmcr = PHY_READ(sc, MII_BMCR);
		if ((bmcr & BMCR_RESET) == 0)
			break;
	}

	if (bmcr & BMCR_RESET)
		device_printf(sc->mii_dev, "reset failed\n");

	PHY_WRITE(sc, MII_BMCR, 0x3000);

	/* Mask interrupts, we poll instead. */
	PHY_WRITE(sc, 0x1e, 0xffc0);
}