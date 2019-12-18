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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct octm_softc {int /*<<< orphan*/  sc_port; struct ifnet* sc_ifp; } ;
struct ifnet {int if_drv_flags; int if_flags; } ;
typedef  int /*<<< orphan*/  cvmx_mgmt_port_netdevice_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IFF_ALLMULTI ; 
 int /*<<< orphan*/  CVMX_IFF_PROMISC ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_set_mac (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_set_multicast_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
octm_init(void *arg)
{
	struct ifnet *ifp;
	struct octm_softc *sc;
	cvmx_mgmt_port_netdevice_flags_t flags;
	uint64_t mac;

	sc = arg;
	ifp = sc->sc_ifp;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0) {
		cvmx_mgmt_port_disable(sc->sc_port);

		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	}

	/*
	 * NB:
	 * MAC must be set before allmulti and promisc below, as
	 * cvmx_mgmt_port_set_mac will always enable the CAM, and turning on
	 * promiscuous mode only works with the CAM disabled.
	 */
	mac = 0;
	memcpy((u_int8_t *)&mac + 2, IF_LLADDR(ifp), 6);
	cvmx_mgmt_port_set_mac(sc->sc_port, mac);

	/*
	 * This is done unconditionally, rather than only if sc_flags have
	 * changed because of set_mac's effect on the CAM noted above.
	 */
	flags = 0;
	if ((ifp->if_flags & IFF_ALLMULTI) != 0)
		flags |= CVMX_IFF_ALLMULTI;
	if ((ifp->if_flags & IFF_PROMISC) != 0)
		flags |= CVMX_IFF_PROMISC;
	cvmx_mgmt_port_set_multicast_list(sc->sc_port, flags);

	/* XXX link state?  */

	if ((ifp->if_flags & IFF_UP) != 0)
		cvmx_mgmt_port_enable(sc->sc_port);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
}