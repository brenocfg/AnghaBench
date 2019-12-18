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
typedef  size_t u_int ;
struct xbb_xen_reqlist {struct xbb_xen_reqlist* gnt_handles; struct xbb_xen_reqlist* bounce; } ;
struct TYPE_2__ {size_t ring_pages; int /*<<< orphan*/ * handle; int /*<<< orphan*/ * bus_addr; scalar_t__ gnt_addr; } ;
struct xbb_softc {int flags; scalar_t__ active_request_count; int max_requests; struct xbb_xen_reqlist* request_lists; struct xbb_xen_reqlist* requests; TYPE_1__ ring_config; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_task; int /*<<< orphan*/  io_taskqueue; int /*<<< orphan*/  xen_intr_handle; } ;
struct gnttab_unmap_grant_ref {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_bus_addr; scalar_t__ host_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GNTTABOP_unmap_grant_ref ; 
 int HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,struct gnttab_unmap_grant_ref*,size_t) ; 
 int /*<<< orphan*/  M_XENBLOCKBACK ; 
 size_t PAGE_SIZE ; 
 int XBBF_RING_CONNECTED ; 
 int XBB_MAX_RING_PAGES ; 
 int /*<<< orphan*/  free (struct xbb_xen_reqlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbb_free_communication_mem (struct xbb_softc*) ; 
 int /*<<< orphan*/  xen_intr_unbind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xbb_disconnect(struct xbb_softc *xbb)
{
	struct gnttab_unmap_grant_ref  ops[XBB_MAX_RING_PAGES];
	struct gnttab_unmap_grant_ref *op;
	u_int			       ring_idx;
	int			       error;

	DPRINTF("\n");

	if ((xbb->flags & XBBF_RING_CONNECTED) == 0)
		return (0);

	mtx_unlock(&xbb->lock);
	xen_intr_unbind(&xbb->xen_intr_handle);
	taskqueue_drain(xbb->io_taskqueue, &xbb->io_task); 
	mtx_lock(&xbb->lock);

	/*
	 * No new interrupts can generate work, but we must wait
	 * for all currently active requests to drain.
	 */
	if (xbb->active_request_count != 0)
		return (EAGAIN);
	
	for (ring_idx = 0, op = ops;
	     ring_idx < xbb->ring_config.ring_pages;
	     ring_idx++, op++) {

		op->host_addr    = xbb->ring_config.gnt_addr
			         + (ring_idx * PAGE_SIZE);
		op->dev_bus_addr = xbb->ring_config.bus_addr[ring_idx];
		op->handle	 = xbb->ring_config.handle[ring_idx];
	}

	error = HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref, ops,
					  xbb->ring_config.ring_pages);
	if (error != 0)
		panic("Grant table op failed (%d)", error);

	xbb_free_communication_mem(xbb);

	if (xbb->requests != NULL) {
		free(xbb->requests, M_XENBLOCKBACK);
		xbb->requests = NULL;
	}

	if (xbb->request_lists != NULL) {
		struct xbb_xen_reqlist *reqlist;
		int i;

		/* There is one request list for ever allocated request. */
		for (i = 0, reqlist = xbb->request_lists;
		     i < xbb->max_requests; i++, reqlist++){
#ifdef XBB_USE_BOUNCE_BUFFERS
			if (reqlist->bounce != NULL) {
				free(reqlist->bounce, M_XENBLOCKBACK);
				reqlist->bounce = NULL;
			}
#endif
			if (reqlist->gnt_handles != NULL) {
				free(reqlist->gnt_handles, M_XENBLOCKBACK);
				reqlist->gnt_handles = NULL;
			}
		}
		free(xbb->request_lists, M_XENBLOCKBACK);
		xbb->request_lists = NULL;
	}

	xbb->flags &= ~XBBF_RING_CONNECTED;
	return (0);
}