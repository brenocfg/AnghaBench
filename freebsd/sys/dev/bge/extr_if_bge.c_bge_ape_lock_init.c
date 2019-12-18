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
struct bge_softc {scalar_t__ bge_asicrev; int bge_func_addr; int bge_phy_ape_lock; int /*<<< orphan*/  bge_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APE_WRITE_4 (struct bge_softc*,int,int) ; 
 int BGE_APE_LOCK_GPIO ; 
 int BGE_APE_LOCK_GRANT ; 
 int BGE_APE_LOCK_GRANT_DRIVER0 ; 
#define  BGE_APE_LOCK_PHY0 131 
#define  BGE_APE_LOCK_PHY1 130 
#define  BGE_APE_LOCK_PHY2 129 
#define  BGE_APE_LOCK_PHY3 128 
 int BGE_APE_PER_LOCK_GRANT ; 
 scalar_t__ BGE_ASICREV_BCM5761 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bge_ape_lock_init(struct bge_softc *sc)
{
	uint32_t bit, regbase;
	int i;

	if (sc->bge_asicrev == BGE_ASICREV_BCM5761)
		regbase = BGE_APE_LOCK_GRANT;
	else
		regbase = BGE_APE_PER_LOCK_GRANT;

	/* Clear any stale locks. */
	for (i = BGE_APE_LOCK_PHY0; i <= BGE_APE_LOCK_GPIO; i++) {
		switch (i) {
		case BGE_APE_LOCK_PHY0:
		case BGE_APE_LOCK_PHY1:
		case BGE_APE_LOCK_PHY2:
		case BGE_APE_LOCK_PHY3:
			bit = BGE_APE_LOCK_GRANT_DRIVER0;
			break;
		default:
			if (sc->bge_func_addr == 0)
				bit = BGE_APE_LOCK_GRANT_DRIVER0;
			else
				bit = (1 << sc->bge_func_addr);
		}
		APE_WRITE_4(sc, regbase + 4 * i, bit);
	}

	/* Select the PHY lock based on the device's function number. */
	switch (sc->bge_func_addr) {
	case 0:
		sc->bge_phy_ape_lock = BGE_APE_LOCK_PHY0;
		break;
	case 1:
		sc->bge_phy_ape_lock = BGE_APE_LOCK_PHY1;
		break;
	case 2:
		sc->bge_phy_ape_lock = BGE_APE_LOCK_PHY2;
		break;
	case 3:
		sc->bge_phy_ape_lock = BGE_APE_LOCK_PHY3;
		break;
	default:
		device_printf(sc->bge_dev,
		    "PHY lock not supported on this function\n");
	}
}