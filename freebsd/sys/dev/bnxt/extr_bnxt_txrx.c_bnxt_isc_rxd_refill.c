#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct rx_prod_pkt_bd {size_t opaque; int /*<<< orphan*/  addr; void* len; void* flags_type; } ;
struct bnxt_softc {struct bnxt_ring* ag_rings; struct bnxt_ring* rx_rings; } ;
struct bnxt_ring {size_t ring_size; scalar_t__ vaddr; } ;
typedef  size_t qidx_t ;
typedef  TYPE_1__* if_rxd_update_t ;
struct TYPE_3__ {size_t iru_qsidx; size_t iru_count; size_t iru_buf_size; size_t iru_pidx; int iru_flidx; size_t* iru_idxs; int /*<<< orphan*/ * iru_paddrs; } ;

/* Variables and functions */
 size_t RX_PROD_AGG_BD_TYPE_RX_PROD_AGG ; 
 size_t RX_PROD_PKT_BD_TYPE_RX_PROD_PKT ; 
 void* htole16 (size_t) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_isc_rxd_refill(void *sc, if_rxd_update_t iru)
{
	struct bnxt_softc *softc = (struct bnxt_softc *)sc;
	struct bnxt_ring *rx_ring;
	struct rx_prod_pkt_bd *rxbd;
	uint16_t type;
	uint16_t i;
	uint16_t rxqid;
	uint16_t count, len;
	uint32_t pidx;
	uint8_t flid;
	uint64_t *paddrs;
	qidx_t	*frag_idxs;

	rxqid = iru->iru_qsidx;
	count = iru->iru_count;
	len = iru->iru_buf_size;
	pidx = iru->iru_pidx;
	flid = iru->iru_flidx;
	paddrs = iru->iru_paddrs;
	frag_idxs = iru->iru_idxs;

	if (flid == 0) {
		rx_ring = &softc->rx_rings[rxqid];
		type = RX_PROD_PKT_BD_TYPE_RX_PROD_PKT;
	}
	else {
		rx_ring = &softc->ag_rings[rxqid];
		type = RX_PROD_AGG_BD_TYPE_RX_PROD_AGG;
	}
	rxbd = (void *)rx_ring->vaddr;

	for (i=0; i<count; i++) {
		rxbd[pidx].flags_type = htole16(type);
		rxbd[pidx].len = htole16(len);
		/* No need to byte-swap the opaque value */
		rxbd[pidx].opaque = (((rxqid & 0xff) << 24) | (flid << 16)
		    | (frag_idxs[i]));
		rxbd[pidx].addr = htole64(paddrs[i]);
		if (++pidx == rx_ring->ring_size)
			pidx = 0;
	}
	return;
}