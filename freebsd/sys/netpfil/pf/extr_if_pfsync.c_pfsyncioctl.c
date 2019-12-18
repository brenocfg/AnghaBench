#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct pfsyncreq {int pfsyncr_maxupdates; int pfsyncr_defer; int ip_hl; TYPE_2__ ip_dst; TYPE_1__ ip_src; int /*<<< orphan*/  ip_p; int /*<<< orphan*/  ip_ttl; int /*<<< orphan*/  ip_off; int /*<<< orphan*/  ip_tos; int /*<<< orphan*/  ip_v; TYPE_3__ pfsyncr_syncpeer; int /*<<< orphan*/ * pfsyncr_syncdev; } ;
struct pfsync_softc {int sc_maxupdates; int sc_flags; int /*<<< orphan*/  sc_bulkfail_tmo; int /*<<< orphan*/  sc_ureq_sent; TYPE_6__* sc_buckets; TYPE_3__ sc_sync_peer; struct pfsyncreq sc_template; struct ifnet* sc_sync_if; TYPE_4__* sc_ifp; } ;
struct ip {int pfsyncr_maxupdates; int pfsyncr_defer; int ip_hl; TYPE_2__ ip_dst; TYPE_1__ ip_src; int /*<<< orphan*/  ip_p; int /*<<< orphan*/  ip_ttl; int /*<<< orphan*/  ip_off; int /*<<< orphan*/  ip_tos; int /*<<< orphan*/  ip_v; TYPE_3__ pfsyncr_syncpeer; int /*<<< orphan*/ * pfsyncr_syncdev; } ;
struct in_mfilter {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_xname; int /*<<< orphan*/  if_drv_flags; struct pfsync_softc* if_softc; } ;
typedef  int /*<<< orphan*/  pfsyncr ;
typedef  scalar_t__ caddr_t ;
struct TYPE_13__ {int /*<<< orphan*/  b_len; } ;
struct TYPE_12__ {int /*<<< orphan*/  debug; } ;
struct TYPE_11__ {int /*<<< orphan*/  if_mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_PFSYNC_GROUP ; 
 int /*<<< orphan*/  IPPROTO_PFSYNC ; 
 int /*<<< orphan*/  IPTOS_LOWDELAY ; 
 int /*<<< orphan*/  IPVERSION ; 
 int /*<<< orphan*/  IP_DF ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PFSYNCF_DEFER ; 
 int PFSYNCF_OK ; 
 int /*<<< orphan*/  PFSYNC_BLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_LOCK (TYPE_6__*) ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_UNLOCK (TYPE_6__*) ; 
 int /*<<< orphan*/  PFSYNC_BUNLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_DFLTTL ; 
 int /*<<< orphan*/  PFSYNC_LOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PFSYNC_MINPKT ; 
 int /*<<< orphan*/  PFSYNC_UNLOCK (struct pfsync_softc*) ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 int /*<<< orphan*/  PRIV_NETINET_PF ; 
#define  SIOCGETPFSYNC 131 
#define  SIOCSETPFSYNC 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMTU 128 
 TYPE_5__ V_pf_status ; 
 int /*<<< orphan*/  V_pfsync_carp_adj ; 
 int /*<<< orphan*/ * V_pfsync_defer_ptr ; 
 int /*<<< orphan*/  bzero (struct pfsyncreq*,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct pfsync_softc*) ; 
 int /*<<< orphan*/  carp_demote_adj_p (int /*<<< orphan*/ ,char*) ; 
 int copyin (int /*<<< orphan*/ ,struct pfsyncreq*,int) ; 
 int copyout (struct pfsyncreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  if_rele (struct ifnet*) ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 struct ifnet* ifunit_ref (int /*<<< orphan*/ *) ; 
 struct in_mfilter* ip_mfilter_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_mfilter_free (struct in_mfilter*) ; 
 int pfsync_buckets ; 
 int /*<<< orphan*/  pfsync_bulk_fail ; 
 int /*<<< orphan*/ * pfsync_defer ; 
 int /*<<< orphan*/  pfsync_multicast_cleanup (struct pfsync_softc*) ; 
 int pfsync_multicast_setup (struct pfsync_softc*,struct ifnet*,struct in_mfilter*) ; 
 int /*<<< orphan*/  pfsync_pointers_init () ; 
 int /*<<< orphan*/  pfsync_pointers_uninit () ; 
 int /*<<< orphan*/  pfsync_request_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfsync_sendout (int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int priv_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static int
pfsyncioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct pfsync_softc *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	struct pfsyncreq pfsyncr;
	int error;
	int c;

	switch (cmd) {
	case SIOCSIFFLAGS:
		PFSYNC_LOCK(sc);
		if (ifp->if_flags & IFF_UP) {
			ifp->if_drv_flags |= IFF_DRV_RUNNING;
			PFSYNC_UNLOCK(sc);
			pfsync_pointers_init();
		} else {
			ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			PFSYNC_UNLOCK(sc);
			pfsync_pointers_uninit();
		}
		break;
	case SIOCSIFMTU:
		if (!sc->sc_sync_if ||
		    ifr->ifr_mtu <= PFSYNC_MINPKT ||
		    ifr->ifr_mtu > sc->sc_sync_if->if_mtu)
			return (EINVAL);
		if (ifr->ifr_mtu < ifp->if_mtu) {
			for (c = 0; c < pfsync_buckets; c++) {
				PFSYNC_BUCKET_LOCK(&sc->sc_buckets[c]);
				if (sc->sc_buckets[c].b_len > PFSYNC_MINPKT)
					pfsync_sendout(1, c);
				PFSYNC_BUCKET_UNLOCK(&sc->sc_buckets[c]);
			}
		}
		ifp->if_mtu = ifr->ifr_mtu;
		break;
	case SIOCGETPFSYNC:
		bzero(&pfsyncr, sizeof(pfsyncr));
		PFSYNC_LOCK(sc);
		if (sc->sc_sync_if) {
			strlcpy(pfsyncr.pfsyncr_syncdev,
			    sc->sc_sync_if->if_xname, IFNAMSIZ);
		}
		pfsyncr.pfsyncr_syncpeer = sc->sc_sync_peer;
		pfsyncr.pfsyncr_maxupdates = sc->sc_maxupdates;
		pfsyncr.pfsyncr_defer = (PFSYNCF_DEFER ==
		    (sc->sc_flags & PFSYNCF_DEFER));
		PFSYNC_UNLOCK(sc);
		return (copyout(&pfsyncr, ifr_data_get_ptr(ifr),
		    sizeof(pfsyncr)));

	case SIOCSETPFSYNC:
	    {
		struct in_mfilter *imf = NULL;
		struct ifnet *sifp;
		struct ip *ip;

		if ((error = priv_check(curthread, PRIV_NETINET_PF)) != 0)
			return (error);
		if ((error = copyin(ifr_data_get_ptr(ifr), &pfsyncr,
		    sizeof(pfsyncr))))
			return (error);

		if (pfsyncr.pfsyncr_maxupdates > 255)
			return (EINVAL);

		if (pfsyncr.pfsyncr_syncdev[0] == 0)
			sifp = NULL;
		else if ((sifp = ifunit_ref(pfsyncr.pfsyncr_syncdev)) == NULL)
			return (EINVAL);

		if (sifp != NULL && (
		    pfsyncr.pfsyncr_syncpeer.s_addr == 0 ||
		    pfsyncr.pfsyncr_syncpeer.s_addr ==
		    htonl(INADDR_PFSYNC_GROUP)))
			imf = ip_mfilter_alloc(M_WAITOK, 0, 0);

		PFSYNC_LOCK(sc);
		if (pfsyncr.pfsyncr_syncpeer.s_addr == 0)
			sc->sc_sync_peer.s_addr = htonl(INADDR_PFSYNC_GROUP);
		else
			sc->sc_sync_peer.s_addr =
			    pfsyncr.pfsyncr_syncpeer.s_addr;

		sc->sc_maxupdates = pfsyncr.pfsyncr_maxupdates;
		if (pfsyncr.pfsyncr_defer) {
			sc->sc_flags |= PFSYNCF_DEFER;
			V_pfsync_defer_ptr = pfsync_defer;
		} else {
			sc->sc_flags &= ~PFSYNCF_DEFER;
			V_pfsync_defer_ptr = NULL;
		}

		if (sifp == NULL) {
			if (sc->sc_sync_if)
				if_rele(sc->sc_sync_if);
			sc->sc_sync_if = NULL;
			pfsync_multicast_cleanup(sc);
			PFSYNC_UNLOCK(sc);
			break;
		}

		for (c = 0; c < pfsync_buckets; c++) {
			PFSYNC_BUCKET_LOCK(&sc->sc_buckets[c]);
			if (sc->sc_buckets[c].b_len > PFSYNC_MINPKT &&
			    (sifp->if_mtu < sc->sc_ifp->if_mtu ||
			    (sc->sc_sync_if != NULL &&
			    sifp->if_mtu < sc->sc_sync_if->if_mtu) ||
			    sifp->if_mtu < MCLBYTES - sizeof(struct ip)))
				pfsync_sendout(1, c);
			PFSYNC_BUCKET_UNLOCK(&sc->sc_buckets[c]);
		}

		pfsync_multicast_cleanup(sc);

		if (sc->sc_sync_peer.s_addr == htonl(INADDR_PFSYNC_GROUP)) {
			error = pfsync_multicast_setup(sc, sifp, imf);
			if (error) {
				if_rele(sifp);
				ip_mfilter_free(imf);
				PFSYNC_UNLOCK(sc);
				return (error);
			}
		}
		if (sc->sc_sync_if)
			if_rele(sc->sc_sync_if);
		sc->sc_sync_if = sifp;

		ip = &sc->sc_template;
		bzero(ip, sizeof(*ip));
		ip->ip_v = IPVERSION;
		ip->ip_hl = sizeof(sc->sc_template) >> 2;
		ip->ip_tos = IPTOS_LOWDELAY;
		/* len and id are set later. */
		ip->ip_off = htons(IP_DF);
		ip->ip_ttl = PFSYNC_DFLTTL;
		ip->ip_p = IPPROTO_PFSYNC;
		ip->ip_src.s_addr = INADDR_ANY;
		ip->ip_dst.s_addr = sc->sc_sync_peer.s_addr;

		/* Request a full state table update. */
		if ((sc->sc_flags & PFSYNCF_OK) && carp_demote_adj_p)
			(*carp_demote_adj_p)(V_pfsync_carp_adj,
			    "pfsync bulk start");
		sc->sc_flags &= ~PFSYNCF_OK;
		if (V_pf_status.debug >= PF_DEBUG_MISC)
			printf("pfsync: requesting bulk update\n");
		PFSYNC_UNLOCK(sc);
		PFSYNC_BUCKET_LOCK(&sc->sc_buckets[0]);
		pfsync_request_update(0, 0);
		PFSYNC_BUCKET_UNLOCK(&sc->sc_buckets[0]);
		PFSYNC_BLOCK(sc);
		sc->sc_ureq_sent = time_uptime;
		callout_reset(&sc->sc_bulkfail_tmo, 5 * hz, pfsync_bulk_fail,
		    sc);
		PFSYNC_BUNLOCK(sc);

		break;
	    }
	default:
		return (ENOTTY);
	}

	return (0);
}