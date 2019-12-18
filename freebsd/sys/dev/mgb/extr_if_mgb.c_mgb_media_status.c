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
struct mii_data {int /*<<< orphan*/  mii_media_status; int /*<<< orphan*/  mii_media_active; } ;
struct mgb_softc {int /*<<< orphan*/  miibus; } ;
struct ifmediareq {int /*<<< orphan*/  ifm_status; int /*<<< orphan*/  ifm_active; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int IFF_UP ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getsoftc (int /*<<< orphan*/ ) ; 
 struct mgb_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_pollstat (struct mii_data*) ; 

__attribute__((used)) static void
mgb_media_status(if_t ifp, struct ifmediareq *ifmr)
{
	struct mgb_softc *sc;
	struct mii_data *miid;

	sc = iflib_get_softc(if_getsoftc(ifp));
	miid = device_get_softc(sc->miibus);
	if ((if_getflags(ifp) & IFF_UP) == 0)
		return;

	mii_pollstat(miid);
	ifmr->ifm_active = miid->mii_media_active;
	ifmr->ifm_status = miid->mii_media_status;
}