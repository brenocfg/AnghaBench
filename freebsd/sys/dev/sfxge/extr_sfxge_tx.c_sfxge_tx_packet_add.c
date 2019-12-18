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
struct sfxge_txq {int /*<<< orphan*/  netdown_drops; int /*<<< orphan*/  sc; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int /*<<< orphan*/  SFXGE_LINK_UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_ASSERT_NOTOWNED (struct sfxge_txq*) ; 
 scalar_t__ SFXGE_TXQ_TRYLOCK (struct sfxge_txq*) ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int sfxge_tx_qdpl_put_locked (struct sfxge_txq*,struct mbuf*) ; 
 int sfxge_tx_qdpl_put_unlocked (struct sfxge_txq*,struct mbuf*) ; 
 int /*<<< orphan*/  sfxge_tx_qdpl_service (struct sfxge_txq*) ; 
 int /*<<< orphan*/  sfxge_tx_qdpl_swizzle (struct sfxge_txq*) ; 

__attribute__((used)) static int
sfxge_tx_packet_add(struct sfxge_txq *txq, struct mbuf *m)
{
	int rc;

	if (!SFXGE_LINK_UP(txq->sc)) {
		atomic_add_long(&txq->netdown_drops, 1);
		return (ENETDOWN);
	}

	/*
	 * Try to grab the txq lock.  If we are able to get the lock,
	 * the packet will be appended to the "get list" of the deferred
	 * packet list.  Otherwise, it will be pushed on the "put list".
	 */
	if (SFXGE_TXQ_TRYLOCK(txq)) {
		/* First swizzle put-list to get-list to keep order */
		sfxge_tx_qdpl_swizzle(txq);

		rc = sfxge_tx_qdpl_put_locked(txq, m);

		/* Try to service the list. */
		sfxge_tx_qdpl_service(txq);
		/* Lock has been dropped. */
	} else {
		rc = sfxge_tx_qdpl_put_unlocked(txq, m);

		/*
		 * Try to grab the lock again.
		 *
		 * If we are able to get the lock, we need to process
		 * the deferred packet list.  If we are not able to get
		 * the lock, another thread is processing the list.
		 */
		if ((rc == 0) && SFXGE_TXQ_TRYLOCK(txq)) {
			sfxge_tx_qdpl_service(txq);
			/* Lock has been dropped. */
		}
	}

	SFXGE_TXQ_LOCK_ASSERT_NOTOWNED(txq);

	return (rc);
}