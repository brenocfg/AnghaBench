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
struct sfxge_tx_dpl {scalar_t__ std_get_count; scalar_t__ std_get_max; scalar_t__ std_get_non_tcp_count; scalar_t__ std_get_non_tcp_max; struct mbuf** std_getp; } ;
struct sfxge_txq {int /*<<< orphan*/  get_non_tcp_overflow; int /*<<< orphan*/  get_overflow; struct sfxge_tx_dpl dpl; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_ASSERT_OWNED (struct sfxge_txq*) ; 
 scalar_t__ sfxge_is_mbuf_non_tcp (struct mbuf*) ; 

__attribute__((used)) static int
sfxge_tx_qdpl_put_locked(struct sfxge_txq *txq, struct mbuf *mbuf)
{
	struct sfxge_tx_dpl *stdp;

	stdp = &txq->dpl;

	KASSERT(mbuf->m_nextpkt == NULL, ("mbuf->m_nextpkt != NULL"));

	SFXGE_TXQ_LOCK_ASSERT_OWNED(txq);

	if (stdp->std_get_count >= stdp->std_get_max) {
		txq->get_overflow++;
		return (ENOBUFS);
	}
	if (sfxge_is_mbuf_non_tcp(mbuf)) {
		if (stdp->std_get_non_tcp_count >=
		    stdp->std_get_non_tcp_max) {
			txq->get_non_tcp_overflow++;
			return (ENOBUFS);
		}
		stdp->std_get_non_tcp_count++;
	}

	*(stdp->std_getp) = mbuf;
	stdp->std_getp = &mbuf->m_nextpkt;
	stdp->std_get_count++;

	return (0);
}