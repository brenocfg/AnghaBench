#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  idi_size; int /*<<< orphan*/  idi_vaddr; } ;
struct TYPE_15__ {int filter_id; TYPE_11__ rss_grp_tbl; void* rss_id; void* id; } ;
struct TYPE_16__ {void* phys_id; } ;
struct TYPE_17__ {TYPE_1__ ring; void* stats_ctx_id; } ;
struct bnxt_softc {int ntxqsets; int nrxqsets; TYPE_12__ vnic_info; TYPE_10__* grp_info; TYPE_9__* ag_rings; TYPE_8__* rx_rings; TYPE_7__* rx_cp_rings; TYPE_5__* tx_rings; TYPE_4__* tx_cp_rings; TYPE_2__ def_cp_ring; } ;
struct TYPE_24__ {void* phys_id; } ;
struct TYPE_23__ {void* phys_id; } ;
struct TYPE_21__ {void* phys_id; } ;
struct TYPE_22__ {TYPE_6__ ring; void* stats_ctx_id; } ;
struct TYPE_20__ {void* phys_id; } ;
struct TYPE_18__ {void* phys_id; } ;
struct TYPE_19__ {TYPE_3__ ring; void* stats_ctx_id; } ;
struct TYPE_13__ {void* grp_id; } ;

/* Variables and functions */
 void* HWRM_NA_SIGNATURE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_clear_ids(struct bnxt_softc *softc)
{
	int i;

	softc->def_cp_ring.stats_ctx_id = HWRM_NA_SIGNATURE;
	softc->def_cp_ring.ring.phys_id = (uint16_t)HWRM_NA_SIGNATURE;
	for (i = 0; i < softc->ntxqsets; i++) {
		softc->tx_cp_rings[i].stats_ctx_id = HWRM_NA_SIGNATURE;
		softc->tx_cp_rings[i].ring.phys_id =
		    (uint16_t)HWRM_NA_SIGNATURE;
		softc->tx_rings[i].phys_id = (uint16_t)HWRM_NA_SIGNATURE;
	}
	for (i = 0; i < softc->nrxqsets; i++) {
		softc->rx_cp_rings[i].stats_ctx_id = HWRM_NA_SIGNATURE;
		softc->rx_cp_rings[i].ring.phys_id =
		    (uint16_t)HWRM_NA_SIGNATURE;
		softc->rx_rings[i].phys_id = (uint16_t)HWRM_NA_SIGNATURE;
		softc->ag_rings[i].phys_id = (uint16_t)HWRM_NA_SIGNATURE;
		softc->grp_info[i].grp_id = (uint16_t)HWRM_NA_SIGNATURE;
	}
	softc->vnic_info.filter_id = -1;
	softc->vnic_info.id = (uint16_t)HWRM_NA_SIGNATURE;
	softc->vnic_info.rss_id = (uint16_t)HWRM_NA_SIGNATURE;
	memset(softc->vnic_info.rss_grp_tbl.idi_vaddr, 0xff,
	    softc->vnic_info.rss_grp_tbl.idi_size);
}