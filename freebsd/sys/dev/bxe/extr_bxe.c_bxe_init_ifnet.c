#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifm_media; TYPE_1__* ifm_cur; } ;
struct bxe_softc {int media; TYPE_2__ link_params; int /*<<< orphan*/ * ifp; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  mtu; int /*<<< orphan*/  dev; TYPE_3__ ifmedia; } ;
typedef  int /*<<< orphan*/ * if_t ;
struct TYPE_6__ {int /*<<< orphan*/  ifm_media; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int /*<<< orphan*/  DEBUGNET_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_JUMBO_MTU ; 
 int IFCAP_LRO ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWFILTER ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL_MAGIC ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  bxe ; 
 int /*<<< orphan*/  bxe_get_counter ; 
 int /*<<< orphan*/  bxe_ifmedia_status ; 
 int /*<<< orphan*/  bxe_ifmedia_update ; 
 int /*<<< orphan*/  bxe_init ; 
 int /*<<< orphan*/  bxe_ioctl ; 
 int /*<<< orphan*/  bxe_mq_flush ; 
 int /*<<< orphan*/  bxe_tx_mq_start ; 
 int /*<<< orphan*/  bxe_tx_start ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifattach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getcapabilities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * if_gethandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setbaudrate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilitiesbit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_setgetcounterfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwassist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  if_setinitfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setioctlfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setmtu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setqflushfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsendqlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsendqready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_setsoftc (int /*<<< orphan*/ *,struct bxe_softc*) ; 
 int /*<<< orphan*/  if_setstartfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_settimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_settransmitfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (TYPE_3__*,int) ; 

__attribute__((used)) static int
bxe_init_ifnet(struct bxe_softc *sc)
{
    if_t ifp;
    int capabilities;

    /* ifconfig entrypoint for media type/status reporting */
    ifmedia_init(&sc->ifmedia, IFM_IMASK,
                 bxe_ifmedia_update,
                 bxe_ifmedia_status);

    /* set the default interface values */
    ifmedia_add(&sc->ifmedia, (IFM_ETHER | IFM_FDX | sc->media), 0, NULL);
    ifmedia_add(&sc->ifmedia, (IFM_ETHER | IFM_AUTO), 0, NULL);
    ifmedia_set(&sc->ifmedia, (IFM_ETHER | IFM_AUTO));

    sc->ifmedia.ifm_media = sc->ifmedia.ifm_cur->ifm_media; /* XXX ? */
	BLOGI(sc, "IFMEDIA flags : %x\n", sc->ifmedia.ifm_media);

    /* allocate the ifnet structure */
    if ((ifp = if_gethandle(IFT_ETHER)) == NULL) {
        BLOGE(sc, "Interface allocation failed!\n");
        return (ENXIO);
    }

    if_setsoftc(ifp, sc);
    if_initname(ifp, device_get_name(sc->dev), device_get_unit(sc->dev));
    if_setflags(ifp, (IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST));
    if_setioctlfn(ifp, bxe_ioctl);
    if_setstartfn(ifp, bxe_tx_start);
    if_setgetcounterfn(ifp, bxe_get_counter);
#if __FreeBSD_version >= 901504
    if_settransmitfn(ifp, bxe_tx_mq_start);
    if_setqflushfn(ifp, bxe_mq_flush);
#endif
#ifdef FreeBSD8_0
    if_settimer(ifp, 0);
#endif
    if_setinitfn(ifp, bxe_init);
    if_setmtu(ifp, sc->mtu);
    if_sethwassist(ifp, (CSUM_IP      |
                        CSUM_TCP      |
                        CSUM_UDP      |
                        CSUM_TSO      |
                        CSUM_TCP_IPV6 |
                        CSUM_UDP_IPV6));

    capabilities =
#if __FreeBSD_version < 700000
        (IFCAP_VLAN_MTU       |
         IFCAP_VLAN_HWTAGGING |
         IFCAP_HWCSUM         |
         IFCAP_JUMBO_MTU      |
         IFCAP_LRO);
#else
        (IFCAP_VLAN_MTU       |
         IFCAP_VLAN_HWTAGGING |
         IFCAP_VLAN_HWTSO     |
         IFCAP_VLAN_HWFILTER  |
         IFCAP_VLAN_HWCSUM    |
         IFCAP_HWCSUM         |
         IFCAP_JUMBO_MTU      |
         IFCAP_LRO            |
         IFCAP_TSO4           |
         IFCAP_TSO6           |
         IFCAP_WOL_MAGIC);
#endif
    if_setcapabilitiesbit(ifp, capabilities, 0); /* XXX */
    if_setcapenable(ifp, if_getcapabilities(ifp));
    if_setbaudrate(ifp, IF_Gbps(10));
/* XXX */
    if_setsendqlen(ifp, sc->tx_ring_size);
    if_setsendqready(ifp);
/* XXX */

    sc->ifp = ifp;

    /* attach to the Ethernet interface list */
    ether_ifattach(ifp, sc->link_params.mac_addr);

    /* Attach driver debugnet methods. */
    DEBUGNET_SET(ifp, bxe);

    return (0);
}