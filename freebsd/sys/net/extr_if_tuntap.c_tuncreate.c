#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct tuntap_softc {int tun_flags; struct ifnet* tun_ifp; struct tuntap_driver* tun_drv; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_name; } ;
struct tuntap_driver {TYPE_1__ cdevsw; } ;
struct TYPE_5__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_xname; TYPE_2__ if_snd; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_capenable; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_ioctl; struct tuntap_softc* if_softc; } ;
struct ether_addr {int /*<<< orphan*/  octet; } ;
struct cdev {struct tuntap_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_NULL ; 
 int /*<<< orphan*/  ETHERMTU ; 
 int /*<<< orphan*/  IFCAP_LINKSTATE ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_2__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IFT_PPP ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNMTU ; 
 int TUN_INITED ; 
 int TUN_L2 ; 
 int /*<<< orphan*/  TUN_LOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  TUN_UNLOCK (struct tuntap_softc*) ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 int /*<<< orphan*/  ether_gen_addr (struct ifnet*,struct ether_addr*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tunifinit ; 
 int /*<<< orphan*/  tunifioctl ; 
 int /*<<< orphan*/  tunoutput ; 
 int /*<<< orphan*/  tunstart ; 
 int /*<<< orphan*/  tunstart_l2 ; 

__attribute__((used)) static void
tuncreate(struct cdev *dev)
{
	struct tuntap_driver *drv;
	struct tuntap_softc *tp;
	struct ifnet *ifp;
	struct ether_addr eaddr;
	int iflags;
	u_char type;

	tp = dev->si_drv1;
	KASSERT(tp != NULL,
	    ("si_drv1 should have been initialized at creation"));

	drv = tp->tun_drv;
	iflags = IFF_MULTICAST;
	if ((tp->tun_flags & TUN_L2) != 0) {
		type = IFT_ETHER;
		iflags |= IFF_BROADCAST | IFF_SIMPLEX;
	} else {
		type = IFT_PPP;
		iflags |= IFF_POINTOPOINT;
	}
	ifp = tp->tun_ifp = if_alloc(type);
	if (ifp == NULL)
		panic("%s%d: failed to if_alloc() interface.\n",
		    drv->cdevsw.d_name, dev2unit(dev));
	ifp->if_softc = tp;
	if_initname(ifp, drv->cdevsw.d_name, dev2unit(dev));
	ifp->if_ioctl = tunifioctl;
	ifp->if_flags = iflags;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_capabilities |= IFCAP_LINKSTATE;
	ifp->if_capenable |= IFCAP_LINKSTATE;

	if ((tp->tun_flags & TUN_L2) != 0) {
		ifp->if_mtu = ETHERMTU;
		ifp->if_init = tunifinit;
		ifp->if_start = tunstart_l2;

		ether_gen_addr(ifp, &eaddr);
		ether_ifattach(ifp, eaddr.octet);
	} else {
		ifp->if_mtu = TUNMTU;
		ifp->if_start = tunstart;
		ifp->if_output = tunoutput;

		ifp->if_snd.ifq_drv_maxlen = 0;
		IFQ_SET_READY(&ifp->if_snd);

		if_attach(ifp);
		bpfattach(ifp, DLT_NULL, sizeof(u_int32_t));
	}

	TUN_LOCK(tp);
	tp->tun_flags |= TUN_INITED;
	TUN_UNLOCK(tp);

	TUNDEBUG(ifp, "interface %s is created, minor = %#x\n",
	    ifp->if_xname, dev2unit(dev));
}