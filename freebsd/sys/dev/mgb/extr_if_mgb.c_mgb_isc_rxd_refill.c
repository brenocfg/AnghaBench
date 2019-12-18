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
typedef  int /*<<< orphan*/  uint64_t ;
struct mgb_ring_data {struct mgb_ring_desc* ring; } ;
struct mgb_softc {struct mgb_ring_data rx_ring_data; int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {void* high; void* low; } ;
struct mgb_ring_desc {void* ctl; TYPE_1__ addr; scalar_t__ sts; } ;
typedef  size_t qidx_t ;
typedef  int /*<<< orphan*/  if_softc_ctx_t ;
typedef  TYPE_2__* if_rxd_update_t ;
struct TYPE_5__ {int iru_count; int iru_buf_size; size_t* iru_idxs; scalar_t__ iru_qsidx; int /*<<< orphan*/ * iru_paddrs; } ;

/* Variables and functions */
 int CSR_TRANSLATE_ADDR_HIGH32 (int /*<<< orphan*/ ) ; 
 int CSR_TRANSLATE_ADDR_LOW32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MGB_DESC_CTL_BUFLEN_MASK ; 
 int MGB_DESC_CTL_OWN ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mgb_isc_rxd_refill(void *xsc, if_rxd_update_t iru)
{
	if_softc_ctx_t scctx;
	struct mgb_softc *sc;
	struct mgb_ring_data *rdata;
	struct mgb_ring_desc *rxd;
	uint64_t *paddrs;
	qidx_t *idxs;
	qidx_t idx;
	int count, len;

	count = iru->iru_count;
	len = iru->iru_buf_size;
	idxs = iru->iru_idxs;
	paddrs = iru->iru_paddrs;
	KASSERT(iru->iru_qsidx == 0,
	    ("tried to refill RX Channel %d.\n", iru->iru_qsidx));

	sc = xsc;
	scctx = iflib_get_softc_ctx(sc->ctx);
	rdata = &sc->rx_ring_data;

	while (count > 0) {
		idx = idxs[--count];
		rxd = &rdata->ring[idx];

		rxd->sts = 0;
		rxd->addr.low =
		    htole32(CSR_TRANSLATE_ADDR_LOW32(paddrs[count]));
		rxd->addr.high =
		    htole32(CSR_TRANSLATE_ADDR_HIGH32(paddrs[count]));
		rxd->ctl = htole32(MGB_DESC_CTL_OWN |
		    (len & MGB_DESC_CTL_BUFLEN_MASK));
	}
	return;
}