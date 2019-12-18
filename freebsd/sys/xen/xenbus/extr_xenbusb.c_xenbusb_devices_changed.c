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
typedef  int u_int ;
struct xs_watch {scalar_t__ callback_data; } ;
struct xenbusb_softc {int xbs_id_components; int /*<<< orphan*/  xbs_probe_children; int /*<<< orphan*/  xbs_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENBUS ; 
 unsigned int XS_WATCH_PATH ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/  xenbusb_add_device (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
xenbusb_devices_changed(struct xs_watch *watch, const char **vec,
			unsigned int len)
{
	struct xenbusb_softc *xbs;
	device_t dev;
	char *node;
	char *type;
	char *id;
	char *p;
	u_int component;

	xbs = (struct xenbusb_softc *)watch->callback_data;
	dev = xbs->xbs_dev;

	if (len <= XS_WATCH_PATH) {
		device_printf(dev, "xenbusb_devices_changed: "
			      "Short Event Data.\n");
		return;
	}

	node = strdup(vec[XS_WATCH_PATH], M_XENBUS);
	p = strchr(node, '/');
	if (p == NULL)
		goto out;
	*p = 0;
	type = p + 1;

	p = strchr(type, '/');
	if (p == NULL)
		goto out;
	*p++ = 0;

	/*
	 * Extract the device ID.  A device ID has one or more path
	 * components separated by the '/' character.
	 *
	 * e.g. "<frontend vm id>/<frontend dev id>" for backend devices.
	 */
	id = p;
	for (component = 0; component < xbs->xbs_id_components; component++) {
		p = strchr(p, '/');
		if (p == NULL)
			break;
		p++;
	}
	if (p != NULL)
		*p = 0;

	if (*id != 0 && component >= xbs->xbs_id_components - 1) {
		xenbusb_add_device(xbs->xbs_dev, type, id);
		taskqueue_enqueue(taskqueue_thread, &xbs->xbs_probe_children);
	}
out:
	free(node, M_XENBUS);
}