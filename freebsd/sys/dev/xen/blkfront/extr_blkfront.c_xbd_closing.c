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
struct xbd_softc {int /*<<< orphan*/ * xbd_disk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XenbusStateClosed ; 
 int /*<<< orphan*/  XenbusStateClosing ; 
 struct xbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbd_closing(device_t dev)
{
	struct xbd_softc *sc = device_get_softc(dev);

	xenbus_set_state(dev, XenbusStateClosing);

	DPRINTK("xbd_closing: %s removed\n", xenbus_get_node(dev));

	if (sc->xbd_disk != NULL) {
		disk_destroy(sc->xbd_disk);
		sc->xbd_disk = NULL;
	}

	xenbus_set_state(dev, XenbusStateClosed); 
}