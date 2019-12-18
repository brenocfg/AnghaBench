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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct xbb_xen_reqlist {int residual_512b_sectors; int /*<<< orphan*/  pendcnt; scalar_t__ kva; scalar_t__ bounce; int /*<<< orphan*/  status; struct xbb_softc* xbb; } ;
struct xbb_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_name; } ;
struct bio {int bio_resid; scalar_t__ bio_error; scalar_t__ bio_cmd; int /*<<< orphan*/  bio_bcount; scalar_t__ bio_data; struct xbb_xen_reqlist* bio_caller1; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 int /*<<< orphan*/  BLKIF_RSP_ERROR ; 
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  XenbusStateClosing ; 
 scalar_t__ XenbusStateConnected ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbb_complete_reqlist (struct xbb_softc*,struct xbb_xen_reqlist*) ; 
 scalar_t__ xenbus_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbb_bio_done(struct bio *bio)
{
	struct xbb_softc       *xbb;
	struct xbb_xen_reqlist *reqlist;

	reqlist = bio->bio_caller1;
	xbb     = reqlist->xbb;

	reqlist->residual_512b_sectors += bio->bio_resid >> 9;

	/*
	 * This is a bit imprecise.  With aggregated I/O a single
	 * request list can contain multiple front-end requests and
	 * a multiple bios may point to a single request.  By carefully
	 * walking the request list, we could map residuals and errors
	 * back to the original front-end request, but the interface
	 * isn't sufficiently rich for us to properly report the error.
	 * So, we just treat the entire request list as having failed if an
	 * error occurs on any part.  And, if an error occurs, we treat
	 * the amount of data transferred as 0.
	 *
	 * For residuals, we report it on the overall aggregated device,
	 * but not on the individual requests, since we don't currently
	 * do the work to determine which front-end request to which the
	 * residual applies.
	 */
	if (bio->bio_error) {
		DPRINTF("BIO returned error %d for operation on device %s\n",
			bio->bio_error, xbb->dev_name);
		reqlist->status = BLKIF_RSP_ERROR;

		if (bio->bio_error == ENXIO
		 && xenbus_get_state(xbb->dev) == XenbusStateConnected) {

			/*
			 * Backend device has disappeared.  Signal the
			 * front-end that we (the device proxy) want to
			 * go away.
			 */
			xenbus_set_state(xbb->dev, XenbusStateClosing);
		}
	}

#ifdef XBB_USE_BOUNCE_BUFFERS
	if (bio->bio_cmd == BIO_READ) {
		vm_offset_t kva_offset;

		kva_offset = (vm_offset_t)bio->bio_data
			   - (vm_offset_t)reqlist->bounce;
		memcpy((uint8_t *)reqlist->kva + kva_offset,
		       bio->bio_data, bio->bio_bcount);
	}
#endif /* XBB_USE_BOUNCE_BUFFERS */

	/*
	 * Decrement the pending count for the request list.  When we're
	 * done with the requests, send status back for all of them.
	 */
	if (atomic_fetchadd_int(&reqlist->pendcnt, -1) == 1)
		xbb_complete_reqlist(xbb, reqlist);

	g_destroy_bio(bio);
}