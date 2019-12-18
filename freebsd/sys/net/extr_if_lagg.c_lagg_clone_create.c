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
typedef  int /*<<< orphan*/  u_char ;
struct lagg_softc {int sc_flags; void* vlan_detach; void* vlan_attach; int /*<<< orphan*/  sc_media; int /*<<< orphan*/  sc_ports; int /*<<< orphan*/  flowid_shift; int /*<<< orphan*/  sc_opts; struct ifnet* sc_ifp; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_ratelimit_query; int /*<<< orphan*/  if_snd_tag_free; int /*<<< orphan*/  if_snd_tag_query; int /*<<< orphan*/  if_snd_tag_modify; int /*<<< orphan*/  if_snd_tag_alloc; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; struct lagg_softc* if_softc; } ;
struct if_clone {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CK_SLIST_INIT (int /*<<< orphan*/ *) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EVENTHANDLER_PRI_FIRST ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lagg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCAP_HWSTATS ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  LAGG_LIST_LOCK () ; 
 int /*<<< orphan*/  LAGG_LIST_UNLOCK () ; 
 int /*<<< orphan*/  LAGG_OPT_USE_FLOWID ; 
 int /*<<< orphan*/  LAGG_OPT_USE_NUMA ; 
 int /*<<< orphan*/  LAGG_PROTO_DEFAULT ; 
 int /*<<< orphan*/  LAGG_SX_INIT (struct lagg_softc*) ; 
 int /*<<< orphan*/  LAGG_XLOCK (struct lagg_softc*) ; 
 int /*<<< orphan*/  LAGG_XUNLOCK (struct lagg_softc*) ; 
 int MBUF_HASHFLAG_L2 ; 
 int MBUF_HASHFLAG_L3 ; 
 int MBUF_HASHFLAG_L4 ; 
 int /*<<< orphan*/  M_LAGG ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct lagg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_def_flowid_shift ; 
 scalar_t__ V_def_use_flowid ; 
 scalar_t__ V_def_use_numa ; 
 int /*<<< orphan*/  V_lagg_list ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (struct lagg_softc*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lagg_get_counter ; 
 int /*<<< orphan*/  lagg_init ; 
 int /*<<< orphan*/  lagg_ioctl ; 
 int /*<<< orphan*/  lagg_media_change ; 
 int /*<<< orphan*/  lagg_media_status ; 
 int /*<<< orphan*/  lagg_proto_attach (struct lagg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lagg_qflush ; 
 int /*<<< orphan*/  lagg_ratelimit_query ; 
 int /*<<< orphan*/  lagg_register_vlan ; 
 int /*<<< orphan*/  lagg_snd_tag_alloc ; 
 int /*<<< orphan*/  lagg_snd_tag_free ; 
 int /*<<< orphan*/  lagg_snd_tag_modify ; 
 int /*<<< orphan*/  lagg_snd_tag_query ; 
 int /*<<< orphan*/  lagg_transmit ; 
 int /*<<< orphan*/  lagg_unregister_vlan ; 
 int /*<<< orphan*/  laggname ; 
 struct lagg_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc_entries ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static int
lagg_clone_create(struct if_clone *ifc, int unit, caddr_t params)
{
	struct lagg_softc *sc;
	struct ifnet *ifp;
	static const u_char eaddr[6];	/* 00:00:00:00:00:00 */

	sc = malloc(sizeof(*sc), M_LAGG, M_WAITOK|M_ZERO);
	ifp = sc->sc_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		free(sc, M_LAGG);
		return (ENOSPC);
	}
	LAGG_SX_INIT(sc);

	LAGG_XLOCK(sc);
	if (V_def_use_flowid)
		sc->sc_opts |= LAGG_OPT_USE_FLOWID;
	if (V_def_use_numa)
		sc->sc_opts |= LAGG_OPT_USE_NUMA;
	sc->flowid_shift = V_def_flowid_shift;

	/* Hash all layers by default */
	sc->sc_flags = MBUF_HASHFLAG_L2|MBUF_HASHFLAG_L3|MBUF_HASHFLAG_L4;

	lagg_proto_attach(sc, LAGG_PROTO_DEFAULT);

	CK_SLIST_INIT(&sc->sc_ports);

	/* Initialise pseudo media types */
	ifmedia_init(&sc->sc_media, 0, lagg_media_change,
	    lagg_media_status);
	ifmedia_add(&sc->sc_media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->sc_media, IFM_ETHER | IFM_AUTO);

	if_initname(ifp, laggname, unit);
	ifp->if_softc = sc;
	ifp->if_transmit = lagg_transmit;
	ifp->if_qflush = lagg_qflush;
	ifp->if_init = lagg_init;
	ifp->if_ioctl = lagg_ioctl;
	ifp->if_get_counter = lagg_get_counter;
	ifp->if_flags = IFF_SIMPLEX | IFF_BROADCAST | IFF_MULTICAST;
#if defined(KERN_TLS) || defined(RATELIMIT)
	ifp->if_snd_tag_alloc = lagg_snd_tag_alloc;
	ifp->if_snd_tag_modify = lagg_snd_tag_modify;
	ifp->if_snd_tag_query = lagg_snd_tag_query;
	ifp->if_snd_tag_free = lagg_snd_tag_free;
	ifp->if_ratelimit_query = lagg_ratelimit_query;
#endif
	ifp->if_capenable = ifp->if_capabilities = IFCAP_HWSTATS;

	/*
	 * Attach as an ordinary ethernet device, children will be attached
	 * as special device IFT_IEEE8023ADLAG.
	 */
	ether_ifattach(ifp, eaddr);

	sc->vlan_attach = EVENTHANDLER_REGISTER(vlan_config,
		lagg_register_vlan, sc, EVENTHANDLER_PRI_FIRST);
	sc->vlan_detach = EVENTHANDLER_REGISTER(vlan_unconfig,
		lagg_unregister_vlan, sc, EVENTHANDLER_PRI_FIRST);

	/* Insert into the global list of laggs */
	LAGG_LIST_LOCK();
	SLIST_INSERT_HEAD(&V_lagg_list, sc, sc_entries);
	LAGG_LIST_UNLOCK();
	LAGG_XUNLOCK(sc);

	return (0);
}