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
struct sfxge_tx_dpl {struct mbuf* std_get; struct mbuf** std_getp; scalar_t__ std_get_non_tcp_count; scalar_t__ std_get_count; } ;
struct sfxge_txq {struct sfxge_tx_dpl dpl; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_TXQ_LOCK (struct sfxge_txq*) ; 
 int /*<<< orphan*/  SFXGE_TXQ_UNLOCK (struct sfxge_txq*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  sfxge_tx_qdpl_swizzle (struct sfxge_txq*) ; 

__attribute__((used)) static void
sfxge_tx_qdpl_flush(struct sfxge_txq *txq)
{
	struct sfxge_tx_dpl *stdp = &txq->dpl;
	struct mbuf *mbuf, *next;

	SFXGE_TXQ_LOCK(txq);

	sfxge_tx_qdpl_swizzle(txq);
	for (mbuf = stdp->std_get; mbuf != NULL; mbuf = next) {
		next = mbuf->m_nextpkt;
		m_freem(mbuf);
	}
	stdp->std_get = NULL;
	stdp->std_get_count = 0;
	stdp->std_get_non_tcp_count = 0;
	stdp->std_getp = &stdp->std_get;

	SFXGE_TXQ_UNLOCK(txq);
}