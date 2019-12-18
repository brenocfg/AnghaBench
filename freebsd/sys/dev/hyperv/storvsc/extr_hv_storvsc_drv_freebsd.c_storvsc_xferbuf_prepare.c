#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ccb_scsiio {int /*<<< orphan*/  dxfer_len; } ;
union ccb {struct ccb_scsiio csio; } ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_4__ {int gpa_ofs; int /*<<< orphan*/  gpa_len; } ;
struct storvsc_gpa_range {int /*<<< orphan*/ * gpa_page; TYPE_1__ gpa_range; } ;
struct hv_storvsc_request {int prp_cnt; struct storvsc_gpa_range prp_list; union ccb* ccb; } ;
struct TYPE_5__ {int ds_addr; scalar_t__ ds_len; } ;
typedef  TYPE_2__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  atop (int) ; 

__attribute__((used)) static void
storvsc_xferbuf_prepare(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct hv_storvsc_request *reqp = arg;
	union ccb *ccb = reqp->ccb;
	struct ccb_scsiio *csio = &ccb->csio;
	struct storvsc_gpa_range *prplist;
	int i;

	prplist = &reqp->prp_list;
	prplist->gpa_range.gpa_len = csio->dxfer_len;
	prplist->gpa_range.gpa_ofs = segs[0].ds_addr & PAGE_MASK;

	for (i = 0; i < nsegs; i++) {
#ifdef INVARIANTS
		if (nsegs > 1) {
			if (i == 0) {
				KASSERT((segs[i].ds_addr & PAGE_MASK) +
				    segs[i].ds_len == PAGE_SIZE,
				    ("invalid 1st page, ofs 0x%jx, len %zu",
				     (uintmax_t)segs[i].ds_addr,
				     segs[i].ds_len));
			} else if (i == nsegs - 1) {
				KASSERT((segs[i].ds_addr & PAGE_MASK) == 0,
				    ("invalid last page, ofs 0x%jx",
				     (uintmax_t)segs[i].ds_addr));
			} else {
				KASSERT((segs[i].ds_addr & PAGE_MASK) == 0 &&
				    segs[i].ds_len == PAGE_SIZE,
				    ("not a full page, ofs 0x%jx, len %zu",
				     (uintmax_t)segs[i].ds_addr,
				     segs[i].ds_len));
			}
		}
#endif
		prplist->gpa_page[i] = atop(segs[i].ds_addr);
	}
	reqp->prp_cnt = nsegs;
}