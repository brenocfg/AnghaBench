#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ntb_net_queue {int /*<<< orphan*/  tx_task; int /*<<< orphan*/  tx_tq; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  br; } ;
struct ntb_net_ctx {int num_queues; struct ntb_net_queue* queues; } ;
struct TYPE_2__ {int flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KTR_NTB ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 int curcpu ; 
 int drbr_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct ntb_net_ctx* if_getsoftc (int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_transmit_locked (struct ntb_net_queue*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ntb_transmit(if_t ifp, struct mbuf *m)
{
	struct ntb_net_ctx *sc = if_getsoftc(ifp);
	struct ntb_net_queue *q;
	int error, i;

	CTR0(KTR_NTB, "TX: ntb_transmit");
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE)
		i = m->m_pkthdr.flowid % sc->num_queues;
	else
		i = curcpu % sc->num_queues;
	q = &sc->queues[i];

	error = drbr_enqueue(ifp, q->br, m);
	if (error)
		return (error);

	if (mtx_trylock(&q->tx_lock)) {
		ntb_transmit_locked(q);
		mtx_unlock(&q->tx_lock);
	} else
		taskqueue_enqueue(q->tx_tq, &q->tx_task);
	return (0);
}