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
struct phy_desc {int /*<<< orphan*/  ifp; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_LOCK (struct thunder_mdio_softc*) ; 
 int /*<<< orphan*/  MDIO_UNLOCK (struct thunder_mdio_softc*) ; 
 int /*<<< orphan*/  M_THUNDER_MDIO ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct phy_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct thunder_mdio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct phy_desc*,int /*<<< orphan*/ ) ; 
 struct phy_desc* get_phy_desc (struct thunder_mdio_softc*,int) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_desc_list ; 

__attribute__((used)) static int
thunder_mdio_phy_disconnect(device_t dev, int lmacid, int phy)
{
	struct thunder_mdio_softc *sc;
	struct phy_desc *pd;

	sc = device_get_softc(dev);
	MDIO_LOCK(sc);

	pd = get_phy_desc(sc, lmacid);
	if (pd == NULL) {
		MDIO_UNLOCK(sc);
		return (EINVAL);
	}

	/* Remove this PHY descriptor from the list */
	TAILQ_REMOVE(&sc->phy_desc_head, pd, phy_desc_list);

	/* Detach miibus */
	bus_generic_detach(dev);
	device_delete_child(dev, pd->miibus);
	/* Free fake ifnet */
	if_free(pd->ifp);
	/* Free memory under phy descriptor */
	free(pd, M_THUNDER_MDIO);
	MDIO_UNLOCK(sc);

	return (0);
}