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
struct xenbusb_softc {int dummy; } ;
struct xenbus_device_ivars {int xd_state; int xd_flags; int /*<<< orphan*/  xd_lock; int /*<<< orphan*/  xd_node; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int XDF_CONNECTING ; 
#define  XENBUS_IVAR_NODE 132 
#define  XENBUS_IVAR_OTHEREND_ID 131 
#define  XENBUS_IVAR_OTHEREND_PATH 130 
#define  XENBUS_IVAR_STATE 129 
#define  XENBUS_IVAR_TYPE 128 
 int /*<<< orphan*/  XST_NIL ; 
 int XenbusStateClosed ; 
 int XenbusStateClosing ; 
 int XenbusStateConnected ; 
 struct xenbus_device_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct xenbusb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  xenbusb_release_confighook (struct xenbusb_softc*) ; 
 int xs_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int xs_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int*) ; 

int
xenbusb_write_ivar(device_t dev, device_t child, int index, uintptr_t value)
{
	struct xenbus_device_ivars *ivars = device_get_ivars(child);
	enum xenbus_state newstate;
	int currstate;

	switch (index) {
	case XENBUS_IVAR_STATE:
	{
		int error;

		newstate = (enum xenbus_state)value;
		sx_xlock(&ivars->xd_lock);
		if (ivars->xd_state == newstate) {
			error = 0;
			goto out;
		}

		error = xs_scanf(XST_NIL, ivars->xd_node, "state",
		    NULL, "%d", &currstate);
		if (error)
			goto out;

		do {
			error = xs_printf(XST_NIL, ivars->xd_node, "state",
			    "%d", newstate);
		} while (error == EAGAIN);
		if (error) {
			/*
			 * Avoid looping through xenbus_dev_fatal()
			 * which calls xenbus_write_ivar to set the
			 * state to closing.
			 */
			if (newstate != XenbusStateClosing)
				xenbus_dev_fatal(dev, error,
						 "writing new state");
			goto out;
		}
		ivars->xd_state = newstate;

		if ((ivars->xd_flags & XDF_CONNECTING) != 0
		 && (newstate == XenbusStateClosed
		  || newstate == XenbusStateConnected)) {
			struct xenbusb_softc *xbs;

			ivars->xd_flags &= ~XDF_CONNECTING;
			xbs = device_get_softc(dev);
			xenbusb_release_confighook(xbs);
		}

		wakeup(&ivars->xd_state);
	out:
		sx_xunlock(&ivars->xd_lock);
		return (error);
	}

	case XENBUS_IVAR_NODE:
	case XENBUS_IVAR_TYPE:
	case XENBUS_IVAR_OTHEREND_ID:
	case XENBUS_IVAR_OTHEREND_PATH:
		/*
		 * These variables are read-only.
		 */
		return (EINVAL);
	}

	return (ENOENT);
}