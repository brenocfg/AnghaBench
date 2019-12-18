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
struct netfront_info {int xn_reset; int /*<<< orphan*/  xbdev; TYPE_1__* xn_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int XenbusState ;
struct TYPE_2__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*,int) ; 
#define  XenbusStateClosed 136 
#define  XenbusStateClosing 135 
#define  XenbusStateConnected 134 
#define  XenbusStateInitWait 133 
#define  XenbusStateInitialised 132 
#define  XenbusStateInitialising 131 
#define  XenbusStateReconfigured 130 
#define  XenbusStateReconfiguring 129 
#define  XenbusStateUnknown 128 
 struct netfront_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netfront_send_fake_arp (int /*<<< orphan*/ ,struct netfront_info*) ; 
 int /*<<< orphan*/  netif_disconnect_backend (struct netfront_info*) ; 
 int const xenbus_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  xn_connect (struct netfront_info*) ; 
 int /*<<< orphan*/  xn_kick_rings (struct netfront_info*) ; 

__attribute__((used)) static void
netfront_backend_changed(device_t dev, XenbusState newstate)
{
	struct netfront_info *sc = device_get_softc(dev);

	DPRINTK("newstate=%d\n", newstate);

	CURVNET_SET(sc->xn_ifp->if_vnet);

	switch (newstate) {
	case XenbusStateInitialising:
	case XenbusStateInitialised:
	case XenbusStateUnknown:
	case XenbusStateReconfigured:
	case XenbusStateReconfiguring:
		break;
	case XenbusStateInitWait:
		if (xenbus_get_state(dev) != XenbusStateInitialising)
			break;
		if (xn_connect(sc) != 0)
			break;
		/* Switch to connected state before kicking the rings. */
		xenbus_set_state(sc->xbdev, XenbusStateConnected);
		xn_kick_rings(sc);
		break;
	case XenbusStateClosing:
		xenbus_set_state(dev, XenbusStateClosed);
		break;
	case XenbusStateClosed:
		if (sc->xn_reset) {
			netif_disconnect_backend(sc);
			xenbus_set_state(dev, XenbusStateInitialising);
			sc->xn_reset = false;
		}
		break;
	case XenbusStateConnected:
#ifdef INET
		netfront_send_fake_arp(dev, sc);
#endif
		break;
	}

	CURVNET_RESTORE();
}