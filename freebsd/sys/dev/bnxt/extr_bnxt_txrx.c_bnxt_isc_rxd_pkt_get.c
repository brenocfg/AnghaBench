#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint16_t ;
struct rx_tpa_start_cmpl_hi {int dummy; } ;
struct rx_tpa_start_cmpl {size_t agg_id; } ;
struct cmpl_base {int /*<<< orphan*/  type; } ;
struct bnxt_softc {int /*<<< orphan*/  dev; TYPE_2__* rx_rings; struct bnxt_cp_ring* rx_cp_rings; } ;
struct TYPE_12__ {scalar_t__ vaddr; } ;
struct bnxt_cp_ring {size_t cons; TYPE_7__ ring; int /*<<< orphan*/  v_bit; } ;
typedef  TYPE_3__* if_rxd_info_t ;
struct TYPE_11__ {size_t iri_qsidx; void* iri_cidx; } ;
struct TYPE_10__ {TYPE_1__* tpa_start; } ;
struct TYPE_9__ {struct rx_tpa_start_cmpl_hi high; struct rx_tpa_start_cmpl low; } ;

/* Variables and functions */
 int CMPL_BASE_TYPE_MASK ; 
#define  CMPL_BASE_TYPE_RX_L2 130 
#define  CMPL_BASE_TYPE_RX_TPA_END 129 
#define  CMPL_BASE_TYPE_RX_TPA_START 128 
 int /*<<< orphan*/  CMPL_PREFETCH_NEXT (struct bnxt_cp_ring*,size_t) ; 
 int /*<<< orphan*/  NEXT_CP_CONS_V (TYPE_7__*,size_t,int /*<<< orphan*/ ) ; 
 void* RING_NEXT (TYPE_7__*,void*) ; 
 size_t RX_TPA_START_CMPL_AGG_ID_MASK ; 
 size_t RX_TPA_START_CMPL_AGG_ID_SFT ; 
 int bnxt_pkt_get_l2 (struct bnxt_softc*,TYPE_3__*,struct bnxt_cp_ring*,int) ; 
 int bnxt_pkt_get_tpa (struct bnxt_softc*,TYPE_3__*,struct bnxt_cp_ring*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,size_t) ; 
 int le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_isc_rxd_pkt_get(void *sc, if_rxd_info_t ri)
{
	struct bnxt_softc *softc = (struct bnxt_softc *)sc;
	struct bnxt_cp_ring *cpr = &softc->rx_cp_rings[ri->iri_qsidx];
	struct cmpl_base *cmp_q = (struct cmpl_base *)cpr->ring.vaddr;
	struct cmpl_base *cmp;
	struct rx_tpa_start_cmpl *rtpa;
	uint16_t flags_type;
	uint16_t type;
	uint8_t agg_id;

	for (;;) {
		NEXT_CP_CONS_V(&cpr->ring, cpr->cons, cpr->v_bit);
		ri->iri_cidx = RING_NEXT(&cpr->ring, ri->iri_cidx);
		CMPL_PREFETCH_NEXT(cpr, cpr->cons);
		cmp = &((struct cmpl_base *)cpr->ring.vaddr)[cpr->cons];

		flags_type = le16toh(cmp->type);
		type = flags_type & CMPL_BASE_TYPE_MASK;

		switch (type) {
		case CMPL_BASE_TYPE_RX_L2:
			return bnxt_pkt_get_l2(softc, ri, cpr, flags_type);
		case CMPL_BASE_TYPE_RX_TPA_END:
			return bnxt_pkt_get_tpa(softc, ri, cpr, flags_type);
		case CMPL_BASE_TYPE_RX_TPA_START:
			rtpa = (void *)&cmp_q[cpr->cons];
			agg_id = (rtpa->agg_id &
			    RX_TPA_START_CMPL_AGG_ID_MASK) >>
			    RX_TPA_START_CMPL_AGG_ID_SFT;
			softc->rx_rings[ri->iri_qsidx].tpa_start[agg_id].low = *rtpa;

			NEXT_CP_CONS_V(&cpr->ring, cpr->cons, cpr->v_bit);
			ri->iri_cidx = RING_NEXT(&cpr->ring, ri->iri_cidx);
			CMPL_PREFETCH_NEXT(cpr, cpr->cons);

			softc->rx_rings[ri->iri_qsidx].tpa_start[agg_id].high =
			    ((struct rx_tpa_start_cmpl_hi *)cmp_q)[cpr->cons];
			break;
		default:
			device_printf(softc->dev,
			    "Unhandled completion type %d on RXQ %d get\n",
			    type, ri->iri_qsidx);
			if (type & 1) {
				NEXT_CP_CONS_V(&cpr->ring, cpr->cons,
				    cpr->v_bit);
				ri->iri_cidx = RING_NEXT(&cpr->ring,
				    ri->iri_cidx);
				CMPL_PREFETCH_NEXT(cpr, cpr->cons);
			}
			break;
		}
	}

	return 0;
}