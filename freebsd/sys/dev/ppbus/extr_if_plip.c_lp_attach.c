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
typedef  int /*<<< orphan*/  u_int32_t ;
struct lp_data {int /*<<< orphan*/ * res_irq; int /*<<< orphan*/  sc_intr_cookie; struct ifnet* sc_ifp; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifq_maxlen; } ;
struct ifnet {int if_flags; TYPE_1__ if_snd; scalar_t__ if_addrlen; scalar_t__ if_hdrlen; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_mtu; struct lp_data* if_softc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct lp_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DLT_NULL ; 
 int ENOSPC ; 
 int ENXIO ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFT_PARA ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  LPMTU ; 
 int /*<<< orphan*/  RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lp_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  lp_intr ; 
 int /*<<< orphan*/  lpioctl ; 
 int /*<<< orphan*/  lpoutput ; 

__attribute__((used)) static int
lp_attach(device_t dev)
{
	struct lp_data *lp = DEVTOSOFTC(dev);
	struct ifnet *ifp;
	int error, rid = 0;

	lp->sc_dev = dev;

	/*
	 * Reserve the interrupt resource.  If we don't have one, the
	 * attach fails.
	 */
	lp->res_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE);
	if (lp->res_irq == NULL) {
		device_printf(dev, "cannot reserve interrupt, failed.\n");
		return (ENXIO);
	}

	ifp = lp->sc_ifp = if_alloc(IFT_PARA);
	if (ifp == NULL) {
		return (ENOSPC);
	}

	ifp->if_softc = lp;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_mtu = LPMTU;
	ifp->if_flags = IFF_SIMPLEX | IFF_POINTOPOINT | IFF_MULTICAST;
	ifp->if_ioctl = lpioctl;
	ifp->if_output = lpoutput;
	ifp->if_hdrlen = 0;
	ifp->if_addrlen = 0;
	ifp->if_snd.ifq_maxlen = ifqmaxlen;
	if_attach(ifp);

	bpfattach(ifp, DLT_NULL, sizeof(u_int32_t));

	/*
	 * Attach our interrupt handler.  It is only called while we
	 * own the ppbus.
	 */
	error = bus_setup_intr(dev, lp->res_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, lp_intr, lp, &lp->sc_intr_cookie);
	if (error) {
		bpfdetach(ifp);
		if_detach(ifp);
		bus_release_resource(dev, SYS_RES_IRQ, 0, lp->res_irq);
		device_printf(dev, "Unable to register interrupt handler\n");
		return (error);
	}

	return (0);
}