#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct mbuf {int dummy; } ;
typedef  TYPE_2__* iflib_fl_t ;
typedef  TYPE_3__* iflib_dma_info_t ;
typedef  struct mbuf* caddr_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
struct TYPE_7__ {int /*<<< orphan*/  idi_size; int /*<<< orphan*/  idi_vaddr; } ;
struct TYPE_5__ {struct mbuf** ifsd_m; struct mbuf** ifsd_cl; int /*<<< orphan*/ * ifsd_map; } ;
struct TYPE_6__ {size_t ifl_size; scalar_t__ ifl_fragidx; scalar_t__ ifl_gen; scalar_t__ ifl_pidx; scalar_t__ ifl_cidx; scalar_t__ ifl_credits; TYPE_1__ ifl_sds; int /*<<< orphan*/  ifl_cl_dequeued; int /*<<< orphan*/  ifl_m_dequeued; int /*<<< orphan*/  ifl_zone; int /*<<< orphan*/  ifl_buf_tag; TYPE_3__* ifl_ifdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_init (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  zone_mbuf ; 

__attribute__((used)) static void
iflib_fl_bufs_free(iflib_fl_t fl)
{
	iflib_dma_info_t idi = fl->ifl_ifdi;
	bus_dmamap_t sd_map;
	uint32_t i;

	for (i = 0; i < fl->ifl_size; i++) {
		struct mbuf **sd_m = &fl->ifl_sds.ifsd_m[i];
		caddr_t *sd_cl = &fl->ifl_sds.ifsd_cl[i];

		if (*sd_cl != NULL) {
			sd_map = fl->ifl_sds.ifsd_map[i];
			bus_dmamap_sync(fl->ifl_buf_tag, sd_map,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(fl->ifl_buf_tag, sd_map);
			if (*sd_cl != NULL)
				uma_zfree(fl->ifl_zone, *sd_cl);
			if (*sd_m != NULL) {
				m_init(*sd_m, M_NOWAIT, MT_DATA, 0);
				uma_zfree(zone_mbuf, *sd_m);
			}
		} else {
			MPASS(*sd_cl == NULL);
			MPASS(*sd_m == NULL);
		}
#if MEMORY_LOGGING
		fl->ifl_m_dequeued++;
		fl->ifl_cl_dequeued++;
#endif
		*sd_cl = NULL;
		*sd_m = NULL;
	}
#ifdef INVARIANTS
	for (i = 0; i < fl->ifl_size; i++) {
		MPASS(fl->ifl_sds.ifsd_cl[i] == NULL);
		MPASS(fl->ifl_sds.ifsd_m[i] == NULL);
	}
#endif
	/*
	 * Reset free list values
	 */
	fl->ifl_credits = fl->ifl_cidx = fl->ifl_pidx = fl->ifl_gen = fl->ifl_fragidx = 0;
	bzero(idi->idi_vaddr, idi->idi_size);
}