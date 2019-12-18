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
struct ntb_net_queue {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  br; } ;
struct ntb_net_ctx {int num_queues; struct ntb_net_queue* queues; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 struct mbuf* buf_ring_dequeue_sc (int /*<<< orphan*/ ) ; 
 struct ntb_net_ctx* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_qflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ntb_qflush(if_t ifp)
{
	struct ntb_net_ctx *sc = if_getsoftc(ifp);
	struct ntb_net_queue *q;
	struct mbuf *m;
	int i;

	for (i = 0; i < sc->num_queues; i++) {
		q = &sc->queues[i];
		mtx_lock(&q->tx_lock);
		while ((m = buf_ring_dequeue_sc(q->br)) != NULL)
			m_freem(m);
		mtx_unlock(&q->tx_lock);
	}
	if_qflush(ifp);
}