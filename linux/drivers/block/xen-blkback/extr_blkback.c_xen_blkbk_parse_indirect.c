#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct xen_blkif_ring {int dummy; } ;
struct seg_buf {int nsec; int offset; } ;
struct phys_req {int /*<<< orphan*/  nr_sects; } ;
struct pending_req {int nr_segs; TYPE_3__** segments; struct xen_blkif_ring* ring; struct grant_page** indirect_pages; } ;
struct grant_page {int /*<<< orphan*/  page; int /*<<< orphan*/  gref; } ;
struct blkif_request_segment {int /*<<< orphan*/  last_sect; int /*<<< orphan*/  first_sect; int /*<<< orphan*/  gref; } ;
struct TYPE_4__ {int /*<<< orphan*/ * indirect_grefs; } ;
struct TYPE_5__ {TYPE_1__ indirect; } ;
struct blkif_request {TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  gref; } ;

/* Variables and functions */
 int BLKIF_MAX_INDIRECT_PAGES_PER_REQUEST ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int INDIRECT_PAGES (int) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int SEGS_PER_INDIRECT_FRAME ; 
 int XEN_PAGE_SIZE ; 
 struct blkif_request_segment* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct blkif_request_segment*) ; 
 int xen_blkbk_map (struct xen_blkif_ring*,struct grant_page**,int,int) ; 
 int /*<<< orphan*/  xen_blkbk_unmap (struct xen_blkif_ring*,struct grant_page**,int) ; 

__attribute__((used)) static int xen_blkbk_parse_indirect(struct blkif_request *req,
				    struct pending_req *pending_req,
				    struct seg_buf seg[],
				    struct phys_req *preq)
{
	struct grant_page **pages = pending_req->indirect_pages;
	struct xen_blkif_ring *ring = pending_req->ring;
	int indirect_grefs, rc, n, nseg, i;
	struct blkif_request_segment *segments = NULL;

	nseg = pending_req->nr_segs;
	indirect_grefs = INDIRECT_PAGES(nseg);
	BUG_ON(indirect_grefs > BLKIF_MAX_INDIRECT_PAGES_PER_REQUEST);

	for (i = 0; i < indirect_grefs; i++)
		pages[i]->gref = req->u.indirect.indirect_grefs[i];

	rc = xen_blkbk_map(ring, pages, indirect_grefs, true);
	if (rc)
		goto unmap;

	for (n = 0, i = 0; n < nseg; n++) {
		uint8_t first_sect, last_sect;

		if ((n % SEGS_PER_INDIRECT_FRAME) == 0) {
			/* Map indirect segments */
			if (segments)
				kunmap_atomic(segments);
			segments = kmap_atomic(pages[n/SEGS_PER_INDIRECT_FRAME]->page);
		}
		i = n % SEGS_PER_INDIRECT_FRAME;

		pending_req->segments[n]->gref = segments[i].gref;

		first_sect = READ_ONCE(segments[i].first_sect);
		last_sect = READ_ONCE(segments[i].last_sect);
		if (last_sect >= (XEN_PAGE_SIZE >> 9) || last_sect < first_sect) {
			rc = -EINVAL;
			goto unmap;
		}

		seg[n].nsec = last_sect - first_sect + 1;
		seg[n].offset = first_sect << 9;
		preq->nr_sects += seg[n].nsec;
	}

unmap:
	if (segments)
		kunmap_atomic(segments);
	xen_blkbk_unmap(ring, pages, indirect_grefs);
	return rc;
}