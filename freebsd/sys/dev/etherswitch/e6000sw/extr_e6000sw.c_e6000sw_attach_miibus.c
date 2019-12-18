#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ phy_base; int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * miibus; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  e6000sw_ifmedia_sts ; 
 int /*<<< orphan*/  e6000sw_ifmedia_upd ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e6000sw_attach_miibus(e6000sw_softc_t *sc, int port)
{
	int err;

	err = mii_attach(sc->dev, &sc->miibus[port], sc->ifp[port],
	    e6000sw_ifmedia_upd, e6000sw_ifmedia_sts, BMSR_DEFCAPMASK,
	    port + sc->phy_base, MII_OFFSET_ANY, 0);
	if (err != 0)
		return (err);

	return (0);
}