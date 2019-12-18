#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifnet {struct cpswp_softc* if_softc; } ;
struct cpswp_softc {TYPE_2__* mii; int /*<<< orphan*/  media_status; int /*<<< orphan*/  swsc; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifm_media; } ;
struct TYPE_4__ {TYPE_1__ mii_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_PORT_UNLOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  mii_mediachg (TYPE_2__*) ; 

__attribute__((used)) static int
cpswp_ifmedia_upd(struct ifnet *ifp)
{
	struct cpswp_softc *sc;

	sc = ifp->if_softc;
	CPSW_DEBUGF(sc->swsc, (""));
	CPSW_PORT_LOCK(sc);
	mii_mediachg(sc->mii);
	sc->media_status = sc->mii->mii_media.ifm_media;
	CPSW_PORT_UNLOCK(sc);

	return (0);
}