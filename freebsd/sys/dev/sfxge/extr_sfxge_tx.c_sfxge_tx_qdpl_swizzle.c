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
struct sfxge_tx_dpl {uintptr_t std_put; unsigned int std_put_hiwat; unsigned int std_get_count; unsigned int std_get_non_tcp_count; struct mbuf** std_getp; } ;
struct sfxge_txq {struct sfxge_tx_dpl dpl; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_ASSERT_OWNED (struct sfxge_txq*) ; 
 uintptr_t atomic_readandclear_ptr (uintptr_t volatile*) ; 
 scalar_t__ sfxge_is_mbuf_non_tcp (struct mbuf*) ; 

__attribute__((used)) static void
sfxge_tx_qdpl_swizzle(struct sfxge_txq *txq)
{
	struct sfxge_tx_dpl *stdp;
	struct mbuf *mbuf, *get_next, **get_tailp;
	volatile uintptr_t *putp;
	uintptr_t put;
	unsigned int count;
	unsigned int non_tcp_count;

	SFXGE_TXQ_LOCK_ASSERT_OWNED(txq);

	stdp = &txq->dpl;

	/* Acquire the put list. */
	putp = &stdp->std_put;
	put = atomic_readandclear_ptr(putp);
	mbuf = (void *)put;

	if (mbuf == NULL)
		return;

	/* Reverse the put list. */
	get_tailp = &mbuf->m_nextpkt;
	get_next = NULL;

	count = 0;
	non_tcp_count = 0;
	do {
		struct mbuf *put_next;

		non_tcp_count += sfxge_is_mbuf_non_tcp(mbuf);
		put_next = mbuf->m_nextpkt;
		mbuf->m_nextpkt = get_next;
		get_next = mbuf;
		mbuf = put_next;

		count++;
	} while (mbuf != NULL);

	if (count > stdp->std_put_hiwat)
		stdp->std_put_hiwat = count;

	/* Append the reversed put list to the get list. */
	KASSERT(*get_tailp == NULL, ("*get_tailp != NULL"));
	*stdp->std_getp = get_next;
	stdp->std_getp = get_tailp;
	stdp->std_get_count += count;
	stdp->std_get_non_tcp_count += non_tcp_count;
}