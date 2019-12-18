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
struct TYPE_2__ {int /*<<< orphan*/  ifq_maxlen; } ;
struct ifnet {int if_flags; TYPE_1__ if_snd; scalar_t__ if_addrlen; scalar_t__ if_hdrlen; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_ioctl; struct ic_softc* if_softc; } ;
struct ic_softc {int /*<<< orphan*/  ic_dev; int /*<<< orphan*/  ic_addr; int /*<<< orphan*/  ic_lock; struct ifnet* ic_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_NULL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  ICHDRLEN ; 
 int /*<<< orphan*/  ICMTU ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFT_PARA ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  PCF_MASTER_ADDRESS ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ic_alloc_buffers (struct ic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icioctl ; 
 int /*<<< orphan*/  icoutput ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icattach(device_t dev)
{
	struct ic_softc *sc = (struct ic_softc *)device_get_softc(dev);
	struct ifnet *ifp;

	ifp = sc->ic_ifp = if_alloc(IFT_PARA);
	if (ifp == NULL)
		return (ENOSPC);

	mtx_init(&sc->ic_lock, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	sc->ic_addr = PCF_MASTER_ADDRESS;	/* XXX only PCF masters */
	sc->ic_dev = dev;

	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_SIMPLEX | IFF_POINTOPOINT | IFF_MULTICAST;
	ifp->if_ioctl = icioctl;
	ifp->if_output = icoutput;
	ifp->if_hdrlen = 0;
	ifp->if_addrlen = 0;
	ifp->if_snd.ifq_maxlen = ifqmaxlen;

	ic_alloc_buffers(sc, ICMTU);

	if_attach(ifp);

	bpfattach(ifp, DLT_NULL, ICHDRLEN);

	return (0);
}