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
struct ip_moptions {int imo_multicast_vif; scalar_t__ imo_multicast_loop; int /*<<< orphan*/  imo_multicast_ttl; struct ifnet* imo_multicast_ifp; int /*<<< orphan*/  imo_head; } ;
struct pfsync_softc {int /*<<< orphan*/  sc_sync_peer; struct ip_moptions sc_imo; } ;
struct in_mfilter {int /*<<< orphan*/  imf_inm; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  PFSYNC_DFLTTL ; 
 int in_joingroup (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mfilter_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_mfilter_insert (int /*<<< orphan*/ *,struct in_mfilter*) ; 

__attribute__((used)) static int
pfsync_multicast_setup(struct pfsync_softc *sc, struct ifnet *ifp,
    struct in_mfilter *imf)
{
	struct ip_moptions *imo = &sc->sc_imo;
	int error;

	if (!(ifp->if_flags & IFF_MULTICAST))
		return (EADDRNOTAVAIL);

	imo->imo_multicast_vif = -1;

	if ((error = in_joingroup(ifp, &sc->sc_sync_peer, NULL,
	    &imf->imf_inm)) != 0)
		return (error);

	ip_mfilter_init(&imo->imo_head);
	ip_mfilter_insert(&imo->imo_head, imf);
	imo->imo_multicast_ifp = ifp;
	imo->imo_multicast_ttl = PFSYNC_DFLTTL;
	imo->imo_multicast_loop = 0;

	return (0);
}