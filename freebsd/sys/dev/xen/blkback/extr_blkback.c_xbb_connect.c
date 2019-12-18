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
struct xbb_softc {int max_reqlist_segments; int max_request_segments; int max_requests; int max_reqlist_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  hotplug_done; } ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  XBBF_SHUTDOWN ; 
 int /*<<< orphan*/  XBB_MAX_SEGMENTS_PER_REQLIST ; 
 int /*<<< orphan*/  XenbusStateConnected ; 
 scalar_t__ XenbusStateInitWait ; 
 int xbb_alloc_communication_mem (struct xbb_softc*) ; 
 int xbb_alloc_request_lists (struct xbb_softc*) ; 
 int xbb_alloc_requests (struct xbb_softc*) ; 
 scalar_t__ xbb_collect_frontend_info (struct xbb_softc*) ; 
 int xbb_connect_ring (struct xbb_softc*) ; 
 int /*<<< orphan*/  xbb_disconnect (struct xbb_softc*) ; 
 scalar_t__ xbb_publish_backend_info (struct xbb_softc*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ xenbus_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbb_connect(struct xbb_softc *xbb)
{
	int error;

	if (!xbb->hotplug_done ||
	    (xenbus_get_state(xbb->dev) != XenbusStateInitWait) ||
	    (xbb_collect_frontend_info(xbb) != 0))
		return;

	xbb->flags &= ~XBBF_SHUTDOWN;

	/*
	 * We limit the maximum number of reqlist segments to the maximum
	 * number of segments in the ring, or our absolute maximum,
	 * whichever is smaller.
	 */
	xbb->max_reqlist_segments = MIN(xbb->max_request_segments *
		xbb->max_requests, XBB_MAX_SEGMENTS_PER_REQLIST);

	/*
	 * The maximum size is simply a function of the number of segments
	 * we can handle.
	 */
	xbb->max_reqlist_size = xbb->max_reqlist_segments * PAGE_SIZE;

	/* Allocate resources whose size depends on front-end configuration. */
	error = xbb_alloc_communication_mem(xbb);
	if (error != 0) {
		xenbus_dev_fatal(xbb->dev, error,
				 "Unable to allocate communication memory");
		return;
	}

	error = xbb_alloc_requests(xbb);
	if (error != 0) {
		/* Specific errors are reported by xbb_alloc_requests(). */
		return;
	}

	error = xbb_alloc_request_lists(xbb);
	if (error != 0) {
		/* Specific errors are reported by xbb_alloc_request_lists(). */
		return;
	}

	/*
	 * Connect communication channel.
	 */
	error = xbb_connect_ring(xbb);
	if (error != 0) {
		/* Specific errors are reported by xbb_connect_ring(). */
		return;
	}
	
	if (xbb_publish_backend_info(xbb) != 0) {
		/*
		 * If we can't publish our data, we cannot participate
		 * in this connection, and waiting for a front-end state
		 * change will not help the situation.
		 */
		(void)xbb_disconnect(xbb);
		return;
	}

	/* Ready for I/O. */
	xenbus_set_state(xbb->dev, XenbusStateConnected);
}