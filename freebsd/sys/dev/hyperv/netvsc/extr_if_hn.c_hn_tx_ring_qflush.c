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
struct mbuf {int dummy; } ;
struct hn_tx_ring {int /*<<< orphan*/  hn_tx_lock; int /*<<< orphan*/  hn_mbuf_br; } ;

/* Variables and functions */
 struct mbuf* buf_ring_dequeue_sc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_tx_ring_qflush(struct hn_tx_ring *txr)
{
	struct mbuf *m;

	mtx_lock(&txr->hn_tx_lock);
	while ((m = buf_ring_dequeue_sc(txr->hn_mbuf_br)) != NULL)
		m_freem(m);
	mtx_unlock(&txr->hn_tx_lock);
}