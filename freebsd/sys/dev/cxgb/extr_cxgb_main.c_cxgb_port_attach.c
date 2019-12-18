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
struct port_info {int port_id; int /*<<< orphan*/  media; int /*<<< orphan*/  hw_addr; struct ifnet* ifp; int /*<<< orphan*/  link_check_task; int /*<<< orphan*/  link_check_ch; int /*<<< orphan*/  lockbuf; struct adapter* adapter; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int if_hwassist; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_get_counter; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_ioctl; struct port_info* if_softc; int /*<<< orphan*/  if_init; } ;
struct TYPE_2__ {int nports; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int CXGB_CAP ; 
 int CXGB_CAP_ENABLE ; 
 int /*<<< orphan*/  DEBUGNET_SET (struct ifnet*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETHERMTU_JUMBO ; 
 int IFCAP_TOE4 ; 
 int IFCAP_TSO ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  PORT_LOCK_INIT (struct port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_NAME_LEN ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct port_info*) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_link_status ; 
 int /*<<< orphan*/  cxgb ; 
 int /*<<< orphan*/  cxgb_build_medialist (struct port_info*) ; 
 int /*<<< orphan*/  cxgb_get_counter ; 
 int /*<<< orphan*/  cxgb_init ; 
 int /*<<< orphan*/  cxgb_ioctl ; 
 int cxgb_makedev (struct port_info*) ; 
 int /*<<< orphan*/  cxgb_media_change ; 
 int /*<<< orphan*/  cxgb_media_status ; 
 int /*<<< orphan*/  cxgb_qflush ; 
 int /*<<< orphan*/  cxgb_transmit ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct port_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_offload (struct adapter*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  t3_sge_init_port (struct port_info*) ; 

__attribute__((used)) static int
cxgb_port_attach(device_t dev)
{
	struct port_info *p;
	struct ifnet *ifp;
	int err;
	struct adapter *sc;

	p = device_get_softc(dev);
	sc = p->adapter;
	snprintf(p->lockbuf, PORT_NAME_LEN, "cxgb port lock %d:%d",
	    device_get_unit(device_get_parent(dev)), p->port_id);
	PORT_LOCK_INIT(p, p->lockbuf);

	callout_init(&p->link_check_ch, 1);
	TASK_INIT(&p->link_check_task, 0, check_link_status, p);

	/* Allocate an ifnet object and set it up */
	ifp = p->ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "Cannot allocate ifnet\n");
		return (ENOMEM);
	}
	
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_init = cxgb_init;
	ifp->if_softc = p;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = cxgb_ioctl;
	ifp->if_transmit = cxgb_transmit;
	ifp->if_qflush = cxgb_qflush;
	ifp->if_get_counter = cxgb_get_counter;

	ifp->if_capabilities = CXGB_CAP;
#ifdef TCP_OFFLOAD
	if (is_offload(sc))
		ifp->if_capabilities |= IFCAP_TOE4;
#endif
	ifp->if_capenable = CXGB_CAP_ENABLE;
	ifp->if_hwassist = CSUM_TCP | CSUM_UDP | CSUM_IP | CSUM_TSO |
	    CSUM_UDP_IPV6 | CSUM_TCP_IPV6;

	/*
	 * Disable TSO on 4-port - it isn't supported by the firmware.
	 */	
	if (sc->params.nports > 2) {
		ifp->if_capabilities &= ~(IFCAP_TSO | IFCAP_VLAN_HWTSO);
		ifp->if_capenable &= ~(IFCAP_TSO | IFCAP_VLAN_HWTSO);
		ifp->if_hwassist &= ~CSUM_TSO;
	}

	ether_ifattach(ifp, p->hw_addr);

	/* Attach driver debugnet methods. */
	DEBUGNET_SET(ifp, cxgb);

#ifdef DEFAULT_JUMBO
	if (sc->params.nports <= 2)
		ifp->if_mtu = ETHERMTU_JUMBO;
#endif
	if ((err = cxgb_makedev(p)) != 0) {
		printf("makedev failed %d\n", err);
		return (err);
	}

	/* Create a list of media supported by this port */
	ifmedia_init(&p->media, IFM_IMASK, cxgb_media_change,
	    cxgb_media_status);
	cxgb_build_medialist(p);
      
	t3_sge_init_port(p);

	return (err);
}