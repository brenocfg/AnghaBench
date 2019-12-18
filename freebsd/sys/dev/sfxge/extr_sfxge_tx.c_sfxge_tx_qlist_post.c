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
struct sfxge_txq {scalar_t__ n_pend_desc; scalar_t__ max_pkt_desc; int blocked; unsigned int added; unsigned int reaped; unsigned int entries; int /*<<< orphan*/  pend_desc; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 unsigned int EFX_TXQ_LIMIT (unsigned int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_ASSERT_OWNED (struct sfxge_txq*) ; 
 int efx_tx_qdesc_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  sfxge_tx_qreap (struct sfxge_txq*) ; 

__attribute__((used)) static void
sfxge_tx_qlist_post(struct sfxge_txq *txq)
{
	unsigned int old_added;
	unsigned int block_level;
	unsigned int level;
	int rc;

	SFXGE_TXQ_LOCK_ASSERT_OWNED(txq);

	KASSERT(txq->n_pend_desc != 0, ("txq->n_pend_desc == 0"));
	KASSERT(txq->n_pend_desc <= txq->max_pkt_desc,
		("txq->n_pend_desc too large"));
	KASSERT(!txq->blocked, ("txq->blocked"));

	old_added = txq->added;

	/* Post the fragment list. */
	rc = efx_tx_qdesc_post(txq->common, txq->pend_desc, txq->n_pend_desc,
			  txq->reaped, &txq->added);
	KASSERT(rc == 0, ("efx_tx_qdesc_post() failed"));

	/* If efx_tx_qdesc_post() had to refragment, our information about
	 * buffers to free may be associated with the wrong
	 * descriptors.
	 */
	KASSERT(txq->added - old_added == txq->n_pend_desc,
		("efx_tx_qdesc_post() refragmented descriptors"));

	level = txq->added - txq->reaped;
	KASSERT(level <= txq->entries, ("overfilled TX queue"));

	/* Clear the fragment list. */
	txq->n_pend_desc = 0;

	/*
	 * Set the block level to ensure there is space to generate a
	 * large number of descriptors for TSO.
	 */
	block_level = EFX_TXQ_LIMIT(txq->entries) - txq->max_pkt_desc;

	/* Have we reached the block level? */
	if (level < block_level)
		return;

	/* Reap, and check again */
	sfxge_tx_qreap(txq);
	level = txq->added - txq->reaped;
	if (level < block_level)
		return;

	txq->blocked = 1;

	/*
	 * Avoid a race with completion interrupt handling that could leave
	 * the queue blocked.
	 */
	mb();
	sfxge_tx_qreap(txq);
	level = txq->added - txq->reaped;
	if (level < block_level) {
		mb();
		txq->blocked = 0;
	}
}