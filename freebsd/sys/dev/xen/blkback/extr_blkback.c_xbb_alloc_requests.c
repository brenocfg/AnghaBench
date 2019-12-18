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
struct xbb_xen_req {int dummy; } ;
struct xbb_softc {int max_requests; int /*<<< orphan*/  request_free_stailq; struct xbb_xen_req* requests; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_XENBLOCKBACK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xbb_xen_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 struct xbb_xen_req* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
xbb_alloc_requests(struct xbb_softc *xbb)
{
	struct xbb_xen_req *req;
	struct xbb_xen_req *last_req;

	/*
	 * Allocate request book keeping datastructures.
	 */
	xbb->requests = malloc(xbb->max_requests * sizeof(*xbb->requests),
			       M_XENBLOCKBACK, M_NOWAIT|M_ZERO);
	if (xbb->requests == NULL) {
		xenbus_dev_fatal(xbb->dev, ENOMEM, 
				  "Unable to allocate request structures");
		return (ENOMEM);
	}

	req      = xbb->requests;
	last_req = &xbb->requests[xbb->max_requests - 1];
	STAILQ_INIT(&xbb->request_free_stailq);
	while (req <= last_req) {
		STAILQ_INSERT_TAIL(&xbb->request_free_stailq, req, links);
		req++;
	}
	return (0);
}