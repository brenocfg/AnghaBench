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
struct ifnet {struct arge_softc* if_softc; } ;
struct ifmedia_entry {int /*<<< orphan*/  ifm_media; } ;
struct ifmedia {int /*<<< orphan*/  ifm_media; struct ifmedia_entry* ifm_cur; } ;
struct arge_softc {int /*<<< orphan*/  arge_dev; struct ifmedia arge_ifmedia; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IFM_AUTO ; 
 scalar_t__ IFM_ETHER ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

int
arge_multiphy_mediachange(struct ifnet *ifp)
{
	struct arge_softc *sc = ifp->if_softc;
	struct ifmedia *ifm = &sc->arge_ifmedia;
	struct ifmedia_entry *ife = ifm->ifm_cur;

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER)
		return (EINVAL);

	if (IFM_SUBTYPE(ife->ifm_media) == IFM_AUTO) {
		device_printf(sc->arge_dev,
		    "AUTO is not supported for multiphy MAC");
		return (EINVAL);
	}

	/*
	 * Ignore everything
	 */
	return (0);
}