#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* node; } ;
struct xenbus_device_ivars {char* xd_otherend_path; scalar_t__ xd_state; int /*<<< orphan*/  xd_lock; TYPE_1__ xd_otherend_watch; scalar_t__ xd_otherend_path_len; } ;
typedef  char device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_RESUME (char) ; 
 scalar_t__ DS_NOTPRESENT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  M_XENBUS ; 
 int XENBUSB_GET_OTHEREND_NODE (char,struct xenbus_device_ivars*) ; 
 scalar_t__ XenbusStateClosed ; 
 scalar_t__ XenbusStateConnected ; 
 int /*<<< orphan*/  XenbusStateInitialising ; 
 scalar_t__ device_get_children (char,char**,int*) ; 
 struct xenbus_device_ivars* device_get_ivars (char) ; 
 scalar_t__ device_get_state (char) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  sx_sleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xen_suspend_cancelled ; 
 int /*<<< orphan*/  xenbus_set_state (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_register_watch (TYPE_1__*) ; 
 int /*<<< orphan*/  xs_unregister_watch (TYPE_1__*) ; 

int
xenbusb_resume(device_t dev)
{
	device_t *kids;
	struct xenbus_device_ivars *ivars;
	int i, count, error;
	char *statepath;

	/*
	 * We must re-examine each device and find the new path for
	 * its backend.
	 */
	if (device_get_children(dev, &kids, &count) == 0) {
		for (i = 0; i < count; i++) {
			if (device_get_state(kids[i]) == DS_NOTPRESENT)
				continue;

			if (xen_suspend_cancelled) {
				DEVICE_RESUME(kids[i]);
				continue;
			}

			ivars = device_get_ivars(kids[i]);

			xs_unregister_watch(&ivars->xd_otherend_watch);
			xenbus_set_state(kids[i], XenbusStateInitialising);

			/*
			 * Find the new backend details and
			 * re-register our watch.
			 */
			error = XENBUSB_GET_OTHEREND_NODE(dev, ivars);
			if (error)
				return (error);

			statepath = malloc(ivars->xd_otherend_path_len
			    + strlen("/state") + 1, M_XENBUS, M_WAITOK);
			sprintf(statepath, "%s/state", ivars->xd_otherend_path);

			free(ivars->xd_otherend_watch.node, M_XENBUS);
			ivars->xd_otherend_watch.node = statepath;

			DEVICE_RESUME(kids[i]);

			xs_register_watch(&ivars->xd_otherend_watch);
#if 0
			/*
			 * Can't do this yet since we are running in
			 * the xenwatch thread and if we sleep here,
			 * we will stop delivering watch notifications
			 * and the device will never come back online.
			 */
			sx_xlock(&ivars->xd_lock);
			while (ivars->xd_state != XenbusStateClosed
			    && ivars->xd_state != XenbusStateConnected)
				sx_sleep(&ivars->xd_state, &ivars->xd_lock,
				    0, "xdresume", 0);
			sx_xunlock(&ivars->xd_lock);
#endif
		}
		free(kids, M_TEMP);
	}

	return (0);
}