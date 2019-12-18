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
struct xbb_xen_reqlist {int /*<<< orphan*/  contig_req_list; scalar_t__ nr_segments; scalar_t__ num_children; scalar_t__ residual_512b_sectors; int /*<<< orphan*/  status; int /*<<< orphan*/ * kva; int /*<<< orphan*/  flags; } ;
struct xbb_softc {int /*<<< orphan*/  reqlist_free_stailq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_RSP_OKAY ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct xbb_xen_reqlist* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XBB_REQLIST_NONE ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct xbb_xen_reqlist *
xbb_get_reqlist(struct xbb_softc *xbb)
{
	struct xbb_xen_reqlist *reqlist;

	reqlist = NULL;

	mtx_assert(&xbb->lock, MA_OWNED);

	if ((reqlist = STAILQ_FIRST(&xbb->reqlist_free_stailq)) != NULL) {

		STAILQ_REMOVE_HEAD(&xbb->reqlist_free_stailq, links);
		reqlist->flags = XBB_REQLIST_NONE;
		reqlist->kva = NULL;
		reqlist->status = BLKIF_RSP_OKAY;
		reqlist->residual_512b_sectors = 0;
		reqlist->num_children = 0;
		reqlist->nr_segments = 0;
		STAILQ_INIT(&reqlist->contig_req_list);
	}

	return (reqlist);
}