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
typedef  int /*<<< orphan*/  uint64_t ;
struct sfxge_txq {scalar_t__ tso_pdrop_no_rsrc; scalar_t__ tso_pdrop_too_many; scalar_t__ netdown_drops; scalar_t__ put_overflow; scalar_t__ get_non_tcp_overflow; scalar_t__ get_overflow; scalar_t__ drops; } ;
struct sfxge_softc {unsigned int txq_count; struct sfxge_txq** txq; } ;

/* Variables and functions */

uint64_t
sfxge_tx_get_drops(struct sfxge_softc *sc)
{
	unsigned int index;
	uint64_t drops = 0;
	struct sfxge_txq *txq;

	/* Sum across all TX queues */
	for (index = 0; index < sc->txq_count; index++) {
		txq = sc->txq[index];
		/*
		 * In theory, txq->put_overflow and txq->netdown_drops
		 * should use atomic operation and other should be
		 * obtained under txq lock, but it is just statistics.
		 */
		drops += txq->drops + txq->get_overflow +
			 txq->get_non_tcp_overflow +
			 txq->put_overflow + txq->netdown_drops +
			 txq->tso_pdrop_too_many + txq->tso_pdrop_no_rsrc;
	}
	return (drops);
}