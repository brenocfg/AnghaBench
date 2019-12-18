#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
typedef  TYPE_3__* iflib_rxq_t ;
typedef  TYPE_4__* iflib_fl_t ;
typedef  TYPE_5__* if_rxsd_t ;
typedef  TYPE_6__* if_rxd_info_t ;
typedef  TYPE_7__* if_rxd_frag_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/ * bus_dmamap_t ;
struct TYPE_19__ {int irf_flid; int irf_idx; } ;
struct TYPE_18__ {int iri_pad; int iri_len; int /*<<< orphan*/  iri_ifp; } ;
struct TYPE_17__ {int ifsd_cidx; int /*<<< orphan*/ * ifsd_cl; TYPE_4__* ifsd_fl; } ;
struct TYPE_14__ {struct mbuf** ifsd_m; int /*<<< orphan*/ ** ifsd_map; int /*<<< orphan*/ * ifsd_cl; } ;
struct TYPE_16__ {int ifl_size; int ifl_cidx; int /*<<< orphan*/  ifl_rx_bitmap; scalar_t__ ifl_gen; int /*<<< orphan*/  ifl_buf_tag; TYPE_2__ ifl_sds; int /*<<< orphan*/  ifl_m_dequeued; int /*<<< orphan*/  ifl_credits; } ;
struct TYPE_15__ {int /*<<< orphan*/ * pfil; TYPE_1__* ifr_ctx; TYPE_4__* ifr_fl; } ;
struct TYPE_13__ {int ifc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int CACHE_LINE_SIZE ; 
 int CACHE_PTR_INCREMENT ; 
 int IFC_PREFETCH ; 
 int /*<<< orphan*/  MPASS (int) ; 
#define  PFIL_CONSUMED 131 
#define  PFIL_DROPPED 130 
 scalar_t__ PFIL_HOOKED_IN (int /*<<< orphan*/ *) ; 
 int PFIL_IN ; 
 int PFIL_MEMPTR ; 
#define  PFIL_PASS 129 
#define  PFIL_REALLOCED 128 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mbuf* pfil_mem2mbuf (int /*<<< orphan*/ ) ; 
 int pfil_run_hooks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  prefetch_pkts (TYPE_4__*,int) ; 

__attribute__((used)) static struct mbuf *
rxd_frag_to_sd(iflib_rxq_t rxq, if_rxd_frag_t irf, bool unload, if_rxsd_t sd,
    int *pf_rv, if_rxd_info_t ri)
{
	bus_dmamap_t map;
	iflib_fl_t fl;
	caddr_t payload;
	struct mbuf *m;
	int flid, cidx, len, next;

	map = NULL;
	flid = irf->irf_flid;
	cidx = irf->irf_idx;
	fl = &rxq->ifr_fl[flid];
	sd->ifsd_fl = fl;
	sd->ifsd_cidx = cidx;
	m = fl->ifl_sds.ifsd_m[cidx];
	sd->ifsd_cl = &fl->ifl_sds.ifsd_cl[cidx];
	fl->ifl_credits--;
#if MEMORY_LOGGING
	fl->ifl_m_dequeued++;
#endif
	if (rxq->ifr_ctx->ifc_flags & IFC_PREFETCH)
		prefetch_pkts(fl, cidx);
	next = (cidx + CACHE_PTR_INCREMENT) & (fl->ifl_size-1);
	prefetch(&fl->ifl_sds.ifsd_map[next]);
	map = fl->ifl_sds.ifsd_map[cidx];
	next = (cidx + CACHE_LINE_SIZE) & (fl->ifl_size-1);

	/* not valid assert if bxe really does SGE from non-contiguous elements */
	MPASS(fl->ifl_cidx == cidx);
	bus_dmamap_sync(fl->ifl_buf_tag, map, BUS_DMASYNC_POSTREAD);

	if (rxq->pfil != NULL && PFIL_HOOKED_IN(rxq->pfil) && pf_rv != NULL) {
		payload  = *sd->ifsd_cl;
		payload +=  ri->iri_pad;
		len = ri->iri_len - ri->iri_pad;
		*pf_rv = pfil_run_hooks(rxq->pfil, payload, ri->iri_ifp,
		    len | PFIL_MEMPTR | PFIL_IN, NULL);
		switch (*pf_rv) {
		case PFIL_DROPPED:
		case PFIL_CONSUMED:
			/*
			 * The filter ate it.  Everything is recycled.
			 */
			m = NULL;
			unload = 0;
			break;
		case PFIL_REALLOCED:
			/*
			 * The filter copied it.  Everything is recycled.
			 */
			m = pfil_mem2mbuf(payload);
			unload = 0;
			break;
		case PFIL_PASS:
			/*
			 * Filter said it was OK, so receive like
			 * normal
			 */
			fl->ifl_sds.ifsd_m[cidx] = NULL;
			break;
		default:
			MPASS(0);
		}
	} else {
		fl->ifl_sds.ifsd_m[cidx] = NULL;
		*pf_rv = PFIL_PASS;
	}

	if (unload)
		bus_dmamap_unload(fl->ifl_buf_tag, map);
	fl->ifl_cidx = (fl->ifl_cidx + 1) & (fl->ifl_size-1);
	if (__predict_false(fl->ifl_cidx == 0))
		fl->ifl_gen = 0;
	bit_clear(fl->ifl_rx_bitmap, cidx);
	return (m);
}