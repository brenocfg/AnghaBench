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
typedef  size_t u_int ;
struct TYPE_4__ {size_t va; size_t ring_pages; size_t gnt_addr; int /*<<< orphan*/  evtchn; int /*<<< orphan*/ * bus_addr; int /*<<< orphan*/ * handle; int /*<<< orphan*/ * ring_ref; } ;
struct TYPE_3__ {int /*<<< orphan*/  x86_64; int /*<<< orphan*/  x86_32; int /*<<< orphan*/  native; } ;
struct xbb_softc {int flags; size_t kva; size_t kva_size; size_t gnt_base_addr; int abi; int /*<<< orphan*/  dev; int /*<<< orphan*/  xen_intr_handle; TYPE_2__ ring_config; int /*<<< orphan*/  otherend_id; TYPE_1__ rings; } ;
struct gnttab_map_grant_ref {size_t host_addr; scalar_t__ status; int /*<<< orphan*/  dev_bus_addr; int /*<<< orphan*/  handle; int /*<<< orphan*/  dom; int /*<<< orphan*/  ref; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  blkif_x86_64_sring_t ;
typedef  int /*<<< orphan*/  blkif_x86_32_sring_t ;
typedef  int /*<<< orphan*/  blkif_sring_t ;

/* Variables and functions */
 int /*<<< orphan*/  BACK_RING_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
#define  BLKIF_PROTOCOL_NATIVE 130 
#define  BLKIF_PROTOCOL_X86_32 129 
#define  BLKIF_PROTOCOL_X86_64 128 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EACCES ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 int /*<<< orphan*/  GNTTABOP_map_grant_ref ; 
 int HYPERVISOR_grant_table_op (int /*<<< orphan*/ ,struct gnttab_map_grant_ref*,size_t) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 size_t PAGE_SIZE ; 
 int XBBF_RING_CONNECTED ; 
 int XBB_MAX_RING_PAGES ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  xbb_disconnect (struct xbb_softc*) ; 
 int /*<<< orphan*/  xbb_filter ; 
 int xen_intr_bind_remote_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct xbb_softc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static int
xbb_connect_ring(struct xbb_softc *xbb)
{
	struct gnttab_map_grant_ref  gnts[XBB_MAX_RING_PAGES];
	struct gnttab_map_grant_ref *gnt;
	u_int			     ring_idx;
	int			     error;

	if ((xbb->flags & XBBF_RING_CONNECTED) != 0)
		return (0);

	/*
	 * Kva for our ring is at the tail of the region of kva allocated
	 * by xbb_alloc_communication_mem().
	 */
	xbb->ring_config.va = xbb->kva
			    + (xbb->kva_size
			     - (xbb->ring_config.ring_pages * PAGE_SIZE));
	xbb->ring_config.gnt_addr = xbb->gnt_base_addr
				  + (xbb->kva_size
				   - (xbb->ring_config.ring_pages * PAGE_SIZE));

	for (ring_idx = 0, gnt = gnts;
	     ring_idx < xbb->ring_config.ring_pages;
	     ring_idx++, gnt++) {

		gnt->host_addr = xbb->ring_config.gnt_addr
			       + (ring_idx * PAGE_SIZE);
		gnt->flags     = GNTMAP_host_map;
		gnt->ref       = xbb->ring_config.ring_ref[ring_idx];
		gnt->dom       = xbb->otherend_id;
	}

	error = HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref, gnts,
					  xbb->ring_config.ring_pages);
	if (error)
		panic("blkback: Ring page grant table op failed (%d)", error);

	for (ring_idx = 0, gnt = gnts;
	     ring_idx < xbb->ring_config.ring_pages;
	     ring_idx++, gnt++) {
		if (gnt->status != 0) {
			xbb->ring_config.va = 0;
			xenbus_dev_fatal(xbb->dev, EACCES,
					 "Ring shared page mapping failed. "
					 "Status %d.", gnt->status);
			return (EACCES);
		}
		xbb->ring_config.handle[ring_idx]   = gnt->handle;
		xbb->ring_config.bus_addr[ring_idx] = gnt->dev_bus_addr;
	}

	/* Initialize the ring based on ABI. */
	switch (xbb->abi) {
	case BLKIF_PROTOCOL_NATIVE:
	{
		blkif_sring_t *sring;
		sring = (blkif_sring_t *)xbb->ring_config.va;
		BACK_RING_INIT(&xbb->rings.native, sring,
			       xbb->ring_config.ring_pages * PAGE_SIZE);
		break;
	}
	case BLKIF_PROTOCOL_X86_32:
	{
		blkif_x86_32_sring_t *sring_x86_32;
		sring_x86_32 = (blkif_x86_32_sring_t *)xbb->ring_config.va;
		BACK_RING_INIT(&xbb->rings.x86_32, sring_x86_32,
			       xbb->ring_config.ring_pages * PAGE_SIZE);
		break;
	}
	case BLKIF_PROTOCOL_X86_64:
	{
		blkif_x86_64_sring_t *sring_x86_64;
		sring_x86_64 = (blkif_x86_64_sring_t *)xbb->ring_config.va;
		BACK_RING_INIT(&xbb->rings.x86_64, sring_x86_64,
			       xbb->ring_config.ring_pages * PAGE_SIZE);
		break;
	}
	default:
		panic("Unexpected blkif protocol ABI.");
	}

	xbb->flags |= XBBF_RING_CONNECTED;

	error = xen_intr_bind_remote_port(xbb->dev,
					  xbb->otherend_id,
					  xbb->ring_config.evtchn,
					  xbb_filter,
					  /*ithread_handler*/NULL,
					  /*arg*/xbb,
					  INTR_TYPE_BIO | INTR_MPSAFE,
					  &xbb->xen_intr_handle);
	if (error) {
		(void)xbb_disconnect(xbb);
		xenbus_dev_fatal(xbb->dev, error, "binding event channel");
		return (error);
	}

	DPRINTF("rings connected!\n");

	return 0;
}