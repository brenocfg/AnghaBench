#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {struct ifmedia_entry* ifm_cur; } ;
struct sfxge_softc {int /*<<< orphan*/  enp; TYPE_1__ media; } ;
struct ifnet {struct sfxge_softc* if_softc; } ;
struct ifmedia_entry {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_UNLOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_RUNNING (struct sfxge_softc*) ; 
 int efx_mac_fcntl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_phy_adv_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sfxge_phy_cap_mask (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_port_wanted_fc (struct sfxge_softc*) ; 

__attribute__((used)) static int
sfxge_media_change(struct ifnet *ifp)
{
	struct sfxge_softc *sc;
	struct ifmedia_entry *ifm;
	int rc;
	uint32_t phy_cap_mask;

	sc = ifp->if_softc;
	ifm = sc->media.ifm_cur;

	SFXGE_ADAPTER_LOCK(sc);

	if (!SFXGE_RUNNING(sc)) {
		rc = 0;
		goto out;
	}

	rc = efx_mac_fcntl_set(sc->enp, sfxge_port_wanted_fc(sc), B_TRUE);
	if (rc != 0)
		goto out;

	if ((rc = sfxge_phy_cap_mask(sc, ifm->ifm_media, &phy_cap_mask)) != 0)
		goto out;

	rc = efx_phy_adv_cap_set(sc->enp, phy_cap_mask);
out:
	SFXGE_ADAPTER_UNLOCK(sc);

	return (rc);
}