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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {uintptr_t callback_data; int /*<<< orphan*/ * node; int /*<<< orphan*/  callback; } ;
struct xbb_softc {TYPE_1__ hotplug_watch; scalar_t__ dev; int /*<<< orphan*/  hotplug_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_task; int /*<<< orphan*/  otherend_id; } ;
struct sbuf {int dummy; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_XENBLOCKBACK ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xbb_softc*) ; 
 int /*<<< orphan*/  XBB_MAX_RING_PAGES ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  XenbusStateInitWait ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 struct xbb_softc* device_get_softc (scalar_t__) ; 
 scalar_t__ flsl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbb_attach_disk ; 
 int /*<<< orphan*/  xbb_attach_failed (struct xbb_softc*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbb_run_queue ; 
 int /*<<< orphan*/ * xenbus_get_node (scalar_t__) ; 
 int /*<<< orphan*/  xenbus_get_otherend_id (scalar_t__) ; 
 int /*<<< orphan*/  xenbus_set_state (scalar_t__,int /*<<< orphan*/ ) ; 
 struct sbuf* xs_join (int /*<<< orphan*/ *,char*) ; 
 int xs_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,...) ; 
 int xs_register_watch (TYPE_1__*) ; 

__attribute__((used)) static int
xbb_attach(device_t dev)
{
	struct xbb_softc	*xbb;
	int			 error;
	u_int			 max_ring_page_order;
	struct sbuf		*watch_path;

	DPRINTF("Attaching to %s\n", xenbus_get_node(dev));

	/*
	 * Basic initialization.
	 * After this block it is safe to call xbb_detach()
	 * to clean up any allocated data for this instance.
	 */
	xbb = device_get_softc(dev);
	xbb->dev = dev;
	xbb->otherend_id = xenbus_get_otherend_id(dev);
	TASK_INIT(&xbb->io_task, /*priority*/0, xbb_run_queue, xbb);
	mtx_init(&xbb->lock, device_get_nameunit(dev), NULL, MTX_DEF);

	/*
	 * Publish protocol capabilities for consumption by the
	 * front-end.
	 */
	error = xs_printf(XST_NIL, xenbus_get_node(xbb->dev),
			  "feature-barrier", "1");
	if (error) {
		xbb_attach_failed(xbb, error, "writing %s/feature-barrier",
				  xenbus_get_node(xbb->dev));
		return (error);
	}

	error = xs_printf(XST_NIL, xenbus_get_node(xbb->dev),
			  "feature-flush-cache", "1");
	if (error) {
		xbb_attach_failed(xbb, error, "writing %s/feature-flush-cache",
				  xenbus_get_node(xbb->dev));
		return (error);
	}

	max_ring_page_order = flsl(XBB_MAX_RING_PAGES) - 1;
	error = xs_printf(XST_NIL, xenbus_get_node(xbb->dev),
			  "max-ring-page-order", "%u", max_ring_page_order);
	if (error) {
		xbb_attach_failed(xbb, error, "writing %s/max-ring-page-order",
				  xenbus_get_node(xbb->dev));
		return (error);
	}

	/*
	 * We need to wait for hotplug script execution before
	 * moving forward.
	 */
	KASSERT(!xbb->hotplug_done, ("Hotplug scripts already executed"));
	watch_path = xs_join(xenbus_get_node(xbb->dev), "physical-device-path");
	xbb->hotplug_watch.callback_data = (uintptr_t)dev;
	xbb->hotplug_watch.callback = xbb_attach_disk;
	KASSERT(xbb->hotplug_watch.node == NULL, ("watch node already setup"));
	xbb->hotplug_watch.node = strdup(sbuf_data(watch_path), M_XENBLOCKBACK);
	sbuf_delete(watch_path);
	error = xs_register_watch(&xbb->hotplug_watch);
	if (error != 0) {
		xbb_attach_failed(xbb, error, "failed to create watch on %s",
		    xbb->hotplug_watch.node);
		free(xbb->hotplug_watch.node, M_XENBLOCKBACK);
		return (error);
	}

	/* Tell the toolstack blkback has attached. */
	xenbus_set_state(dev, XenbusStateInitWait);

	return (0);
}