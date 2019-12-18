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
struct xbb_softc {scalar_t__ active_request_count; int /*<<< orphan*/  request_free_stailq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct xbb_xen_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
xbb_release_req(struct xbb_softc *xbb, struct xbb_xen_req *req)
{
	mtx_assert(&xbb->lock, MA_OWNED);

	STAILQ_INSERT_HEAD(&xbb->request_free_stailq, req, links);
	xbb->active_request_count--;

	KASSERT(xbb->active_request_count >= 0,
		("xbb_release_req: negative active count"));
}