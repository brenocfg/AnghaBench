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
struct vtnet_softc {struct ifmedia vtnet_media; } ;
struct ifnet {struct vtnet_softc* if_softc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IFM_ETHER ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtnet_ifmedia_upd(struct ifnet *ifp)
{
	struct vtnet_softc *sc;
	struct ifmedia *ifm;

	sc = ifp->if_softc;
	ifm = &sc->vtnet_media;

	if (IFM_TYPE(ifm->ifm_media) != IFM_ETHER)
		return (EINVAL);

	return (0);
}