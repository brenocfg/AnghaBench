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
struct xbb_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int XenbusState ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
#define  XenbusStateClosed 132 
#define  XenbusStateClosing 131 
#define  XenbusStateConnected 130 
#define  XenbusStateInitialised 129 
#define  XenbusStateInitialising 128 
 struct xbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbb_connect (struct xbb_softc*) ; 
 int /*<<< orphan*/  xbb_shutdown (struct xbb_softc*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int xenbus_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  xenbus_strstate (int) ; 

__attribute__((used)) static void
xbb_frontend_changed(device_t dev, XenbusState frontend_state)
{
	struct xbb_softc *xbb = device_get_softc(dev);

	DPRINTF("frontend_state=%s, xbb_state=%s\n",
	        xenbus_strstate(frontend_state),
		xenbus_strstate(xenbus_get_state(xbb->dev)));

	switch (frontend_state) {
	case XenbusStateInitialising:
		break;
	case XenbusStateInitialised:
	case XenbusStateConnected:
		xbb_connect(xbb);
		break;
	case XenbusStateClosing:
	case XenbusStateClosed:
		mtx_lock(&xbb->lock);
		xbb_shutdown(xbb);
		mtx_unlock(&xbb->lock);
		if (frontend_state == XenbusStateClosed)
			xenbus_set_state(xbb->dev, XenbusStateClosed);
		break;
	default:
		xenbus_dev_fatal(xbb->dev, EINVAL, "saw state %d at frontend",
				 frontend_state);
		break;
	}
}