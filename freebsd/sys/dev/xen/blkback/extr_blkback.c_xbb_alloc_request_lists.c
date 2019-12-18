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
struct xbb_xen_reqlist {int /*<<< orphan*/ * gnt_handles; int /*<<< orphan*/ * bounce; struct xbb_softc* xbb; } ;
struct xbb_softc {int max_requests; int max_reqlist_size; int max_reqlist_segments; int /*<<< orphan*/  reqlist_free_stailq; int /*<<< orphan*/  dev; struct xbb_xen_reqlist* request_lists; int /*<<< orphan*/  reqlist_pending_stailq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GRANT_REF_INVALID ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_XENBLOCKBACK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xbb_xen_reqlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
xbb_alloc_request_lists(struct xbb_softc *xbb)
{
	struct xbb_xen_reqlist *reqlist;
	int			i;

	/*
	 * If no requests can be merged, we need 1 request list per
	 * in flight request.
	 */
	xbb->request_lists = malloc(xbb->max_requests *
		sizeof(*xbb->request_lists), M_XENBLOCKBACK, M_NOWAIT|M_ZERO);
	if (xbb->request_lists == NULL) {
		xenbus_dev_fatal(xbb->dev, ENOMEM, 
				  "Unable to allocate request list structures");
		return (ENOMEM);
	}

	STAILQ_INIT(&xbb->reqlist_free_stailq);
	STAILQ_INIT(&xbb->reqlist_pending_stailq);
	for (i = 0; i < xbb->max_requests; i++) {
		int seg;

		reqlist      = &xbb->request_lists[i];

		reqlist->xbb = xbb;

#ifdef XBB_USE_BOUNCE_BUFFERS
		reqlist->bounce = malloc(xbb->max_reqlist_size,
					 M_XENBLOCKBACK, M_NOWAIT);
		if (reqlist->bounce == NULL) {
			xenbus_dev_fatal(xbb->dev, ENOMEM, 
					 "Unable to allocate request "
					 "bounce buffers");
			return (ENOMEM);
		}
#endif /* XBB_USE_BOUNCE_BUFFERS */

		reqlist->gnt_handles = malloc(xbb->max_reqlist_segments *
					      sizeof(*reqlist->gnt_handles),
					      M_XENBLOCKBACK, M_NOWAIT|M_ZERO);
		if (reqlist->gnt_handles == NULL) {
			xenbus_dev_fatal(xbb->dev, ENOMEM,
					  "Unable to allocate request "
					  "grant references");
			return (ENOMEM);
		}

		for (seg = 0; seg < xbb->max_reqlist_segments; seg++)
			reqlist->gnt_handles[seg] = GRANT_REF_INVALID;

		STAILQ_INSERT_TAIL(&xbb->reqlist_free_stailq, reqlist, links);
	}
	return (0);
}