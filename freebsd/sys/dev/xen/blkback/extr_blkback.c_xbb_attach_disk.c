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
struct xs_watch {int /*<<< orphan*/ * node; scalar_t__ callback_data; } ;
struct xbb_softc {int hotplug_done; scalar_t__ dev; int /*<<< orphan*/ * io_taskqueue; int /*<<< orphan*/  sector_size; void* xbb_stats_in; void* xbb_stats; int /*<<< orphan*/ * dev_name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * dev_mode; int /*<<< orphan*/ * dev_type; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVSTAT_ALL_SUPPORTED ; 
 int /*<<< orphan*/  DEVSTAT_PRIORITY_OTHER ; 
 int DEVSTAT_TYPE_DIRECT ; 
 int DEVSTAT_TYPE_IF_OTHER ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_XENBLOCKBACK ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  XBBF_READ_ONLY ; 
 int /*<<< orphan*/  XST_NIL ; 
 scalar_t__ XenbusStateInitialised ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 struct xbb_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_get_unit (scalar_t__) ; 
 void* devstat_new_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * taskqueue_create_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  xbb_attach_failed (struct xbb_softc*,int,char*,...) ; 
 int /*<<< orphan*/  xbb_connect (struct xbb_softc*) ; 
 int xbb_open_backend (struct xbb_softc*) ; 
 int /*<<< orphan*/  xbb_setup_sysctl (struct xbb_softc*) ; 
 int /*<<< orphan*/ * xenbus_get_node (scalar_t__) ; 
 int /*<<< orphan*/ * xenbus_get_otherend_path (scalar_t__) ; 
 scalar_t__ xenbus_get_otherend_state (scalar_t__) ; 
 int xs_gather (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int xs_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  xs_unregister_watch (struct xs_watch*) ; 

__attribute__((used)) static void
xbb_attach_disk(struct xs_watch *watch, const char **vec, unsigned int len)
{
	device_t		 dev;
	struct xbb_softc	*xbb;
	int			 error;

	dev = (device_t) watch->callback_data;
	xbb = device_get_softc(dev);

	error = xs_gather(XST_NIL, xenbus_get_node(dev), "physical-device-path",
	    NULL, &xbb->dev_name, NULL);
	if (error != 0)
		return;

	xs_unregister_watch(watch);
	free(watch->node, M_XENBLOCKBACK);
	watch->node = NULL;

	/* Collect physical device information. */
	error = xs_gather(XST_NIL, xenbus_get_otherend_path(xbb->dev),
			  "device-type", NULL, &xbb->dev_type,
			  NULL);
	if (error != 0)
		xbb->dev_type = NULL;

	error = xs_gather(XST_NIL, xenbus_get_node(dev),
                          "mode", NULL, &xbb->dev_mode,
                          NULL);
	if (error != 0) {
		xbb_attach_failed(xbb, error, "reading backend fields at %s",
				  xenbus_get_node(dev));
                return;
        }

	/* Parse fopen style mode flags. */
	if (strchr(xbb->dev_mode, 'w') == NULL)
		xbb->flags |= XBBF_READ_ONLY;

	/*
	 * Verify the physical device is present and can support
	 * the desired I/O mode.
	 */
	error = xbb_open_backend(xbb);
	if (error != 0) {
		xbb_attach_failed(xbb, error, "Unable to open %s",
				  xbb->dev_name);
		return;
	}

	/* Use devstat(9) for recording statistics. */
	xbb->xbb_stats = devstat_new_entry("xbb", device_get_unit(xbb->dev),
					   xbb->sector_size,
					   DEVSTAT_ALL_SUPPORTED,
					   DEVSTAT_TYPE_DIRECT
					 | DEVSTAT_TYPE_IF_OTHER,
					   DEVSTAT_PRIORITY_OTHER);

	xbb->xbb_stats_in = devstat_new_entry("xbbi", device_get_unit(xbb->dev),
					      xbb->sector_size,
					      DEVSTAT_ALL_SUPPORTED,
					      DEVSTAT_TYPE_DIRECT
					    | DEVSTAT_TYPE_IF_OTHER,
					      DEVSTAT_PRIORITY_OTHER);
	/*
	 * Setup sysctl variables.
	 */
	xbb_setup_sysctl(xbb);

	/*
	 * Create a taskqueue for doing work that must occur from a
	 * thread context.
	 */
	xbb->io_taskqueue = taskqueue_create_fast(device_get_nameunit(dev),
						  M_NOWAIT,
						  taskqueue_thread_enqueue,
						  /*contxt*/&xbb->io_taskqueue);
	if (xbb->io_taskqueue == NULL) {
		xbb_attach_failed(xbb, error, "Unable to create taskqueue");
		return;
	}

	taskqueue_start_threads(&xbb->io_taskqueue,
				/*num threads*/1,
				/*priority*/PWAIT,
				/*thread name*/
				"%s taskq", device_get_nameunit(dev));

	/* Update hot-plug status to satisfy xend. */
	error = xs_printf(XST_NIL, xenbus_get_node(xbb->dev),
			  "hotplug-status", "connected");
	if (error) {
		xbb_attach_failed(xbb, error, "writing %s/hotplug-status",
				  xenbus_get_node(xbb->dev));
		return;
	}

	xbb->hotplug_done = true;

	/* The front end might be waiting for the backend, attach if so. */
	if (xenbus_get_otherend_state(xbb->dev) == XenbusStateInitialised)
		xbb_connect(xbb);
}