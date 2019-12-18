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
struct sis_softc {scalar_t__ sis_type; scalar_t__ sis_rev; int /*<<< orphan*/  sis_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_4 (struct sis_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ NS_BMCR ; 
 scalar_t__ NS_BMSR ; 
 scalar_t__ SIS_PHYCTL ; 
 int SIS_PHYCTL_ACCESS ; 
 int SIS_PHYOP_READ ; 
 scalar_t__ SIS_REV_635 ; 
 int /*<<< orphan*/  SIS_SETBIT (struct sis_softc*,scalar_t__,int) ; 
 int SIS_TIMEOUT ; 
 scalar_t__ SIS_TYPE_83815 ; 
 scalar_t__ SIS_TYPE_900 ; 
 struct sis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mii_bitbang_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sis_mii_bitbang_ops ; 

__attribute__((used)) static int
sis_miibus_readreg(device_t dev, int phy, int reg)
{
	struct sis_softc	*sc;

	sc = device_get_softc(dev);

	if (sc->sis_type == SIS_TYPE_83815) {
		if (phy != 0)
			return (0);
		/*
		 * The NatSemi chip can take a while after
		 * a reset to come ready, during which the BMSR
		 * returns a value of 0. This is *never* supposed
		 * to happen: some of the BMSR bits are meant to
		 * be hardwired in the on position, and this can
		 * confuse the miibus code a bit during the probe
		 * and attach phase. So we make an effort to check
		 * for this condition and wait for it to clear.
		 */
		if (!CSR_READ_4(sc, NS_BMSR))
			DELAY(1000);
		return CSR_READ_4(sc, NS_BMCR + (reg * 4));
	}

	/*
	 * Chipsets < SIS_635 seem not to be able to read/write
	 * through mdio. Use the enhanced PHY access register
	 * again for them.
	 */
	if (sc->sis_type == SIS_TYPE_900 &&
	    sc->sis_rev < SIS_REV_635) {
		int i, val = 0;

		if (phy != 0)
			return (0);

		CSR_WRITE_4(sc, SIS_PHYCTL,
		    (phy << 11) | (reg << 6) | SIS_PHYOP_READ);
		SIS_SETBIT(sc, SIS_PHYCTL, SIS_PHYCTL_ACCESS);

		for (i = 0; i < SIS_TIMEOUT; i++) {
			if (!(CSR_READ_4(sc, SIS_PHYCTL) & SIS_PHYCTL_ACCESS))
				break;
		}

		if (i == SIS_TIMEOUT) {
			device_printf(sc->sis_dev,
			    "PHY failed to come ready\n");
			return (0);
		}

		val = (CSR_READ_4(sc, SIS_PHYCTL) >> 16) & 0xFFFF;

		if (val == 0xFFFF)
			return (0);

		return (val);
	} else
		return (mii_bitbang_readreg(dev, &sis_mii_bitbang_ops, phy,
		    reg));
}