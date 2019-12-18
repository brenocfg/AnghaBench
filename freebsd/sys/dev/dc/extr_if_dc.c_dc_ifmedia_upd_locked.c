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
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct mii_data {struct ifmedia mii_media; } ;
struct dc_softc {int /*<<< orphan*/  dc_miibus; scalar_t__ dc_link; } ;

/* Variables and functions */
 scalar_t__ DC_IS_DAVICOM (struct dc_softc*) ; 
 scalar_t__ DC_IS_INTEL (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_LOCK_ASSERT (struct dc_softc*) ; 
 scalar_t__ IFM_HPNA_1 ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_setcfg (struct dc_softc*,int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
dc_ifmedia_upd_locked(struct dc_softc *sc)
{
	struct mii_data *mii;
	struct ifmedia *ifm;
	int error;

	DC_LOCK_ASSERT(sc);

	sc->dc_link = 0;
	mii = device_get_softc(sc->dc_miibus);
	error = mii_mediachg(mii);
	if (error == 0) {
		ifm = &mii->mii_media;
		if (DC_IS_INTEL(sc))
			dc_setcfg(sc, ifm->ifm_media);
		else if (DC_IS_DAVICOM(sc) &&
		    IFM_SUBTYPE(ifm->ifm_media) == IFM_HPNA_1)
			dc_setcfg(sc, ifm->ifm_media);
	}

	return (error);
}