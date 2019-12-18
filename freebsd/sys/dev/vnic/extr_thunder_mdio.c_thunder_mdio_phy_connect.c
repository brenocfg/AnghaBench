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
struct thunder_mdio_softc {int /*<<< orphan*/  phy_desc_head; } ;
struct phy_desc {int lmacid; int /*<<< orphan*/ * ifp; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MDIO_LOCK (struct thunder_mdio_softc*) ; 
 int /*<<< orphan*/  MDIO_UNLOCK (struct thunder_mdio_softc*) ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_THUNDER_MDIO ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct phy_desc*,int /*<<< orphan*/ ) ; 
 struct thunder_mdio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct phy_desc*,int /*<<< orphan*/ ) ; 
 struct phy_desc* get_phy_desc (struct thunder_mdio_softc*,int) ; 
 int /*<<< orphan*/ * if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 struct phy_desc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_desc_list ; 
 int /*<<< orphan*/  thunder_ifmedia_change_stub ; 
 int /*<<< orphan*/  thunder_ifmedia_status_stub ; 

__attribute__((used)) static int
thunder_mdio_phy_connect(device_t dev, int lmacid, int phy)
{
	struct thunder_mdio_softc *sc;
	struct phy_desc *pd;
	int err;

	sc = device_get_softc(dev);

	MDIO_LOCK(sc);
	pd = get_phy_desc(sc, lmacid);
	MDIO_UNLOCK(sc);
	if (pd == NULL) {
		pd = malloc(sizeof(*pd), M_THUNDER_MDIO, (M_NOWAIT | M_ZERO));
		if (pd == NULL)
			return (ENOMEM);
		pd->ifp = if_alloc(IFT_ETHER);
		if (pd->ifp == NULL) {
			free(pd, M_THUNDER_MDIO);
			return (ENOMEM);
		}
		pd->lmacid = lmacid;
	}

	err = mii_attach(dev, &pd->miibus, pd->ifp,
	    thunder_ifmedia_change_stub, thunder_ifmedia_status_stub,
	    BMSR_DEFCAPMASK, phy, MII_OFFSET_ANY, 0);

	if (err != 0) {
		device_printf(dev, "Could not attach PHY%d\n", phy);
		if_free(pd->ifp);
		free(pd, M_THUNDER_MDIO);
		return (ENXIO);
	}

	MDIO_LOCK(sc);
	TAILQ_INSERT_TAIL(&sc->phy_desc_head, pd, phy_desc_list);
	MDIO_UNLOCK(sc);

	return (0);
}