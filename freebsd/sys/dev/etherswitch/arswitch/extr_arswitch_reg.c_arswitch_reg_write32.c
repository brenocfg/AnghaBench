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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct arswitch_softc {scalar_t__ mii_lo_first; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MDIO_WRITEREG (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct arswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arswitch_reg_write32(device_t dev, int phy, int reg, uint32_t value)
{
	struct arswitch_softc *sc;
	int r;
	uint16_t lo, hi;

	sc = device_get_softc(dev);
	lo = value & 0xffff;
	hi = (uint16_t) (value >> 16);

	if (sc->mii_lo_first) {
		r = MDIO_WRITEREG(device_get_parent(dev),
		    phy, reg, lo);
		r |= MDIO_WRITEREG(device_get_parent(dev),
		    phy, reg + 1, hi);
	} else {
		r = MDIO_WRITEREG(device_get_parent(dev),
		    phy, reg + 1, hi);
		r |= MDIO_WRITEREG(device_get_parent(dev),
		    phy, reg, lo);
	}

	return r;
}