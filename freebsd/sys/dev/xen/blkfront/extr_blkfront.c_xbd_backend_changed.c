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
struct xbd_softc {int /*<<< orphan*/ * xbd_disk; int /*<<< orphan*/  xbd_users; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int XenbusState ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
#define  XenbusStateClosed 136 
#define  XenbusStateClosing 135 
#define  XenbusStateConnected 134 
#define  XenbusStateInitWait 133 
#define  XenbusStateInitialised 132 
#define  XenbusStateInitialising 131 
#define  XenbusStateReconfigured 130 
#define  XenbusStateReconfiguring 129 
#define  XenbusStateUnknown 128 
 struct xbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_gone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbd_closing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_connect (struct xbd_softc*) ; 
 int /*<<< orphan*/  xbd_initialize (struct xbd_softc*) ; 

__attribute__((used)) static void
xbd_backend_changed(device_t dev, XenbusState backend_state)
{
	struct xbd_softc *sc = device_get_softc(dev);

	DPRINTK("backend_state=%d\n", backend_state);

	switch (backend_state) {
	case XenbusStateUnknown:
	case XenbusStateInitialising:
	case XenbusStateReconfigured:
	case XenbusStateReconfiguring:
	case XenbusStateClosed:
		break;

	case XenbusStateInitWait:
	case XenbusStateInitialised:
		xbd_initialize(sc);
		break;

	case XenbusStateConnected:
		xbd_initialize(sc);
		xbd_connect(sc);
		break;

	case XenbusStateClosing:
		if (sc->xbd_users > 0) {
			device_printf(dev, "detaching with pending users\n");
			KASSERT(sc->xbd_disk != NULL,
			    ("NULL disk with pending users\n"));
			disk_gone(sc->xbd_disk);
		} else {
			xbd_closing(dev);
		}
		break;	
	}
}