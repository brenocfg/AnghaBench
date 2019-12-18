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
struct sw_zone_info {int size; } ;
struct TYPE_6__ {int hwidx; int zidx; int region1; int region3; } ;
struct sge_fl {int flags; TYPE_3__ cll_alt; } ;
struct sge {size_t safe_hwidx2; size_t safe_hwidx1; struct sw_zone_info* sw_zone_info; struct hw_buf_info* hw_buf_info; } ;
struct hw_buf_info {size_t zidx; int size; } ;
struct TYPE_4__ {int pad_boundary; } ;
struct TYPE_5__ {TYPE_1__ sge; } ;
struct adapter {TYPE_2__ params; struct sge sge; } ;
typedef  size_t int8_t ;

/* Variables and functions */
 int CL_METADATA_SIZE ; 
 int FL_BUF_PACKING ; 
 int MSIZE ; 
 scalar_t__ allow_mbufs_in_cluster ; 
 scalar_t__ fl_pad ; 

__attribute__((used)) static void
find_safe_refill_source(struct adapter *sc, struct sge_fl *fl)
{
	struct sge *s = &sc->sge;
	struct hw_buf_info *hwb;
	struct sw_zone_info *swz;
	int spare;
	int8_t hwidx;

	if (fl->flags & FL_BUF_PACKING)
		hwidx = s->safe_hwidx2;	/* with room for metadata */
	else if (allow_mbufs_in_cluster && s->safe_hwidx2 != -1) {
		hwidx = s->safe_hwidx2;
		hwb = &s->hw_buf_info[hwidx];
		swz = &s->sw_zone_info[hwb->zidx];
		spare = swz->size - hwb->size;

		/* no good if there isn't room for an mbuf as well */
		if (spare < CL_METADATA_SIZE + MSIZE)
			hwidx = s->safe_hwidx1;
	} else
		hwidx = s->safe_hwidx1;

	if (hwidx == -1) {
		/* No fallback source */
		fl->cll_alt.hwidx = -1;
		fl->cll_alt.zidx = -1;

		return;
	}

	hwb = &s->hw_buf_info[hwidx];
	swz = &s->sw_zone_info[hwb->zidx];
	spare = swz->size - hwb->size;
	fl->cll_alt.hwidx = hwidx;
	fl->cll_alt.zidx = hwb->zidx;
	if (allow_mbufs_in_cluster &&
	    (fl_pad == 0 || (MSIZE % sc->params.sge.pad_boundary) == 0))
		fl->cll_alt.region1 = ((spare - CL_METADATA_SIZE) / MSIZE) * MSIZE;
	else
		fl->cll_alt.region1 = 0;
	fl->cll_alt.region3 = spare - fl->cll_alt.region1;
}