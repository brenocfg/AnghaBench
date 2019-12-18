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
struct hn_tx_ring {int hn_txdesc_cnt; int /*<<< orphan*/  hn_tx_lock; int /*<<< orphan*/  hn_txlist_spin; int /*<<< orphan*/ * hn_mbuf_br; int /*<<< orphan*/ * hn_txdesc; int /*<<< orphan*/ * hn_txdesc_br; int /*<<< orphan*/ * hn_tx_rndis_dtag; int /*<<< orphan*/ * hn_tx_data_dtag; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_txdesc_dmamap_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hn_txdesc_gc (struct hn_tx_ring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_tx_ring_destroy(struct hn_tx_ring *txr)
{
	int i;

	if (txr->hn_txdesc == NULL)
		return;

	/*
	 * NOTE:
	 * Because the freeing of aggregated txds will be deferred
	 * to the aggregating txd, two passes are used here:
	 * - The first pass GCes any pending txds.  This GC is necessary,
	 *   since if the channels are revoked, hypervisor will not
	 *   deliver send-done for all pending txds.
	 * - The second pass frees the busdma stuffs, i.e. after all txds
	 *   were freed.
	 */
	for (i = 0; i < txr->hn_txdesc_cnt; ++i)
		hn_txdesc_gc(txr, &txr->hn_txdesc[i]);
	for (i = 0; i < txr->hn_txdesc_cnt; ++i)
		hn_txdesc_dmamap_destroy(&txr->hn_txdesc[i]);

	if (txr->hn_tx_data_dtag != NULL)
		bus_dma_tag_destroy(txr->hn_tx_data_dtag);
	if (txr->hn_tx_rndis_dtag != NULL)
		bus_dma_tag_destroy(txr->hn_tx_rndis_dtag);

#ifdef HN_USE_TXDESC_BUFRING
	buf_ring_free(txr->hn_txdesc_br, M_DEVBUF);
#endif

	free(txr->hn_txdesc, M_DEVBUF);
	txr->hn_txdesc = NULL;

	if (txr->hn_mbuf_br != NULL)
		buf_ring_free(txr->hn_mbuf_br, M_DEVBUF);

#ifndef HN_USE_TXDESC_BUFRING
	mtx_destroy(&txr->hn_txlist_spin);
#endif
	mtx_destroy(&txr->hn_tx_lock);
}