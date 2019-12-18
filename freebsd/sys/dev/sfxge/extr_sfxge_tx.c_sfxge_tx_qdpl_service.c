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
struct sfxge_txq {int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_ASSERT_OWNED (struct sfxge_txq*) ; 
 scalar_t__ SFXGE_TXQ_TRYLOCK (struct sfxge_txq*) ; 
 int /*<<< orphan*/  SFXGE_TXQ_UNLOCK (struct sfxge_txq*) ; 
 scalar_t__ SFXGE_TX_QDPL_PENDING (struct sfxge_txq*) ; 
 int /*<<< orphan*/  sfxge_tx_qdpl_drain (struct sfxge_txq*) ; 
 int /*<<< orphan*/  sfxge_tx_qdpl_swizzle (struct sfxge_txq*) ; 

__attribute__((used)) static void
sfxge_tx_qdpl_service(struct sfxge_txq *txq)
{
	SFXGE_TXQ_LOCK_ASSERT_OWNED(txq);

	do {
		if (SFXGE_TX_QDPL_PENDING(txq))
			sfxge_tx_qdpl_swizzle(txq);

		if (!txq->blocked)
			sfxge_tx_qdpl_drain(txq);

		SFXGE_TXQ_UNLOCK(txq);
	} while (SFXGE_TX_QDPL_PENDING(txq) &&
		 SFXGE_TXQ_TRYLOCK(txq));
}