#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ ifq_drv_maxlen; } ;
struct TYPE_11__ {int if_flags; int if_hwassist; int if_hw_tsomaxsegsize; int /*<<< orphan*/  if_hw_tsomaxsegcount; scalar_t__ if_hw_tsomax; int /*<<< orphan*/  if_baudrate; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_7__ if_snd; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; TYPE_2__* if_softc; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; } ;
struct TYPE_9__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_10__ {TYPE_1__ macaddr; TYPE_4__* ifp; int /*<<< orphan*/  dev; int /*<<< orphan*/  media; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETHERMTU ; 
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ ETHER_VLAN_ENCAP_LEN ; 
 int /*<<< orphan*/  IFCAP_HWCSUM ; 
 int /*<<< orphan*/  IFCAP_LRO ; 
 int /*<<< orphan*/  IFCAP_TSO ; 
 int /*<<< orphan*/  IFCAP_VLAN_HWFILTER ; 
 int /*<<< orphan*/  IFCAP_VLAN_HWTSO ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_7__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  OCE_IF_CAPABILITIES ; 
 int OCE_IF_HWASSIST ; 
 scalar_t__ OCE_MAX_TX_DESC ; 
 int /*<<< orphan*/  OCE_MAX_TX_ELEMENTS ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifattach (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oce_init ; 
 int /*<<< orphan*/  oce_ioctl ; 
 int /*<<< orphan*/  oce_media_change ; 
 int /*<<< orphan*/  oce_media_status ; 
 int /*<<< orphan*/  oce_multiq_flush ; 
 int /*<<< orphan*/  oce_multiq_start ; 
 int /*<<< orphan*/  oce_start ; 

__attribute__((used)) static int 
oce_attach_ifp(POCE_SOFTC sc)
{

	sc->ifp = if_alloc(IFT_ETHER);
	if (!sc->ifp)
		return ENOMEM;

	ifmedia_init(&sc->media, IFM_IMASK, oce_media_change, oce_media_status);
	ifmedia_add(&sc->media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->media, IFM_ETHER | IFM_AUTO);

	sc->ifp->if_flags = IFF_BROADCAST | IFF_MULTICAST;
	sc->ifp->if_ioctl = oce_ioctl;
	sc->ifp->if_start = oce_start;
	sc->ifp->if_init = oce_init;
	sc->ifp->if_mtu = ETHERMTU;
	sc->ifp->if_softc = sc;
#if __FreeBSD_version >= 800000
	sc->ifp->if_transmit = oce_multiq_start;
	sc->ifp->if_qflush = oce_multiq_flush;
#endif

	if_initname(sc->ifp,
		    device_get_name(sc->dev), device_get_unit(sc->dev));

	sc->ifp->if_snd.ifq_drv_maxlen = OCE_MAX_TX_DESC - 1;
	IFQ_SET_MAXLEN(&sc->ifp->if_snd, sc->ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&sc->ifp->if_snd);

	sc->ifp->if_hwassist = OCE_IF_HWASSIST;
	sc->ifp->if_hwassist |= CSUM_TSO;
	sc->ifp->if_hwassist |= (CSUM_IP | CSUM_TCP | CSUM_UDP);

	sc->ifp->if_capabilities = OCE_IF_CAPABILITIES;
	sc->ifp->if_capabilities |= IFCAP_HWCSUM;
	sc->ifp->if_capabilities |= IFCAP_VLAN_HWFILTER;

#if defined(INET6) || defined(INET)
	sc->ifp->if_capabilities |= IFCAP_TSO;
	sc->ifp->if_capabilities |= IFCAP_LRO;
	sc->ifp->if_capabilities |= IFCAP_VLAN_HWTSO;
#endif
	
	sc->ifp->if_capenable = sc->ifp->if_capabilities;
	sc->ifp->if_baudrate = IF_Gbps(10);

#if __FreeBSD_version >= 1000000
	sc->ifp->if_hw_tsomax = 65536 - (ETHER_HDR_LEN + ETHER_VLAN_ENCAP_LEN);
	sc->ifp->if_hw_tsomaxsegcount = OCE_MAX_TX_ELEMENTS;
	sc->ifp->if_hw_tsomaxsegsize = 4096;
#endif

	ether_ifattach(sc->ifp, sc->macaddr.mac_addr);
	
	return 0;
}