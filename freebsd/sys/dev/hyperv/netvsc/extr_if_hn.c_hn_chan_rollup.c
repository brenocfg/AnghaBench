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
struct hn_tx_ring {scalar_t__ hn_txdone_cnt; int /*<<< orphan*/  hn_has_txeof; } ;
struct hn_rx_ring {int /*<<< orphan*/  hn_lro; } ;

/* Variables and functions */
 int /*<<< orphan*/  hn_txeof (struct hn_tx_ring*) ; 
 int /*<<< orphan*/  tcp_lro_flush_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_chan_rollup(struct hn_rx_ring *rxr, struct hn_tx_ring *txr)
{
#if defined(INET) || defined(INET6)
	tcp_lro_flush_all(&rxr->hn_lro);
#endif

	/*
	 * NOTE:
	 * 'txr' could be NULL, if multiple channels and
	 * ifnet.if_start method are enabled.
	 */
	if (txr == NULL || !txr->hn_has_txeof)
		return;

	txr->hn_txdone_cnt = 0;
	hn_txeof(txr);
}