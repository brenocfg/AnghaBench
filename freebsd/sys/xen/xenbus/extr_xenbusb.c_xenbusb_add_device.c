#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xenbusb_softc {int /*<<< orphan*/  xbs_lock; int /*<<< orphan*/  xbs_connecting_children; int /*<<< orphan*/  xbs_node; } ;
struct TYPE_4__ {uintptr_t callback_data; int /*<<< orphan*/  callback; void* node; } ;
struct TYPE_3__ {char* node; uintptr_t callback_data; int /*<<< orphan*/  callback; } ;
struct xenbus_device_ivars {int xd_state; char* xd_otherend_path; int /*<<< orphan*/ * xd_dev; TYPE_2__ xd_local_watch; void* xd_node; TYPE_1__ xd_otherend_watch; int /*<<< orphan*/  xd_otherend_path_len; void* xd_type; int /*<<< orphan*/  xd_node_len; int /*<<< orphan*/  xd_flags; int /*<<< orphan*/  xd_lock; } ;
struct sbuf {int dummy; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  M_XENBUS ; 
 int M_ZERO ; 
 int /*<<< orphan*/  XDF_CONNECTING ; 
 int XENBUSB_GET_OTHEREND_NODE (int /*<<< orphan*/ *,struct xenbus_device_ivars*) ; 
 int /*<<< orphan*/  XST_NIL ; 
 int XenbusStateInitialising ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct xenbusb_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct xenbus_device_ivars*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 void* strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int xenbus_read_driver_state (char*) ; 
 int /*<<< orphan*/ * xenbusb_device_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xenbusb_free_child_ivars (struct xenbus_device_ivars*) ; 
 int /*<<< orphan*/  xenbusb_local_watch_cb ; 
 int /*<<< orphan*/  xenbusb_otherend_watch_cb ; 
 scalar_t__ xs_exists (int /*<<< orphan*/ ,char*,char*) ; 

int
xenbusb_add_device(device_t dev, const char *type, const char *id)
{
	struct xenbusb_softc *xbs;
	struct sbuf *devpath_sbuf;
	char *devpath;
	struct xenbus_device_ivars *ivars;
	int error;

	xbs = device_get_softc(dev);
	devpath_sbuf = sbuf_new_auto();
	sbuf_printf(devpath_sbuf, "%s/%s/%s", xbs->xbs_node, type, id);
	sbuf_finish(devpath_sbuf);
	devpath = sbuf_data(devpath_sbuf);

	ivars = malloc(sizeof(*ivars), M_XENBUS, M_ZERO|M_WAITOK);
	error = ENXIO;

	if (xs_exists(XST_NIL, devpath, "") != 0) {
		device_t child;
		enum xenbus_state state;
		char *statepath;

		child = xenbusb_device_exists(dev, devpath);
		if (child != NULL) {
			/*
			 * We are already tracking this node
			 */
			error = 0;
			goto out;
		}
			
		state = xenbus_read_driver_state(devpath);
		if (state != XenbusStateInitialising) {
			/*
			 * Device is not new, so ignore it. This can
			 * happen if a device is going away after
			 * switching to Closed.
			 */
			printf("xenbusb_add_device: Device %s ignored. "
			       "State %d\n", devpath, state);
			error = 0;
			goto out;
		}

		sx_init(&ivars->xd_lock, "xdlock");
		ivars->xd_flags = XDF_CONNECTING;
		ivars->xd_node = strdup(devpath, M_XENBUS);
		ivars->xd_node_len = strlen(devpath);
		ivars->xd_type  = strdup(type, M_XENBUS);
		ivars->xd_state = XenbusStateInitialising;

		error = XENBUSB_GET_OTHEREND_NODE(dev, ivars);
		if (error) {
			printf("xenbus_update_device: %s no otherend id\n",
			    devpath); 
			goto out;
		}

		statepath = malloc(ivars->xd_otherend_path_len
		    + strlen("/state") + 1, M_XENBUS, M_WAITOK);
		sprintf(statepath, "%s/state", ivars->xd_otherend_path);
		ivars->xd_otherend_watch.node = statepath;
		ivars->xd_otherend_watch.callback = xenbusb_otherend_watch_cb;
		ivars->xd_otherend_watch.callback_data = (uintptr_t)ivars;

		ivars->xd_local_watch.node = ivars->xd_node;
		ivars->xd_local_watch.callback = xenbusb_local_watch_cb;
		ivars->xd_local_watch.callback_data = (uintptr_t)ivars;

		mtx_lock(&xbs->xbs_lock);
		xbs->xbs_connecting_children++;
		mtx_unlock(&xbs->xbs_lock);

		child = device_add_child(dev, NULL, -1);
		ivars->xd_dev = child;
		device_set_ivars(child, ivars);
	}

out:
	sbuf_delete(devpath_sbuf);
	if (error != 0)
		xenbusb_free_child_ivars(ivars);

	return (error);
}