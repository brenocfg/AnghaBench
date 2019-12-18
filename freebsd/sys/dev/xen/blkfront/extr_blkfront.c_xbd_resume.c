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
struct xbd_softc {int /*<<< orphan*/  xbd_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XBD_STATE_CONNECTED ; 
 struct xbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_free (struct xbd_softc*) ; 
 int /*<<< orphan*/  xbd_initialize (struct xbd_softc*) ; 
 scalar_t__ xen_suspend_cancelled ; 
 int /*<<< orphan*/  xenbus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xbd_resume(device_t dev)
{
	struct xbd_softc *sc = device_get_softc(dev);

	if (xen_suspend_cancelled) {
		sc->xbd_state = XBD_STATE_CONNECTED;
		return (0);
	}

	DPRINTK("xbd_resume: %s\n", xenbus_get_node(dev));

	xbd_free(sc);
	xbd_initialize(sc);
	return (0);
}