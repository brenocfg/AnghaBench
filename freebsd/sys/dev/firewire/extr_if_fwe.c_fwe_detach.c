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
struct ifnet {int if_capenable; } ;
struct TYPE_2__ {struct ifnet* ifp; } ;
struct fwe_softc {int /*<<< orphan*/  mtx; TYPE_1__ eth_softc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 struct fwe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  fwe_stop (struct fwe_softc*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int splimp () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
fwe_detach(device_t dev)
{
	struct fwe_softc *fwe;
	struct ifnet *ifp;
	int s;

	fwe = device_get_softc(dev);
	ifp = fwe->eth_softc.ifp;

#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif
	s = splimp();

	fwe_stop(fwe);
	ether_ifdetach(ifp);
	if_free(ifp);

	splx(s);
	mtx_destroy(&fwe->mtx);
	return 0;
}