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
struct mii_softc {scalar_t__ mii_media_active; scalar_t__ mii_media_status; int /*<<< orphan*/  mii_dev; struct mii_data* mii_pdata; } ;
struct mii_data {scalar_t__ mii_media_active; scalar_t__ mii_media_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIIBUS_LINKCHG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIIBUS_STATCHG (int /*<<< orphan*/ ) ; 
 int MII_MEDIACHG ; 

void
mii_phy_update(struct mii_softc *sc, int cmd)
{
	struct mii_data *mii = sc->mii_pdata;

	if (sc->mii_media_active != mii->mii_media_active ||
	    cmd == MII_MEDIACHG) {
		MIIBUS_STATCHG(sc->mii_dev);
		sc->mii_media_active = mii->mii_media_active;
	}
	if (sc->mii_media_status != mii->mii_media_status) {
		MIIBUS_LINKCHG(sc->mii_dev);
		sc->mii_media_status = mii->mii_media_status;
	}
}