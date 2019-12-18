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
struct xbb_softc {int /*<<< orphan*/  active_request_count; int /*<<< orphan*/  request_free_stailq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct xbb_xen_req* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct xbb_xen_req *
xbb_get_req(struct xbb_softc *xbb)
{
	struct xbb_xen_req *req;

	req = NULL;

	mtx_assert(&xbb->lock, MA_OWNED);

	if ((req = STAILQ_FIRST(&xbb->request_free_stailq)) != NULL) {
		STAILQ_REMOVE_HEAD(&xbb->request_free_stailq, links);
		xbb->active_request_count++;
	}

	return (req);
}