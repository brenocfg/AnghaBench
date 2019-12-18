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
struct al_eth_ring {int enqueue_is_running; int /*<<< orphan*/  br_mtx; int /*<<< orphan*/  br; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_data_memory_barrier () ; 
 int /*<<< orphan*/  al_eth_xmit_mbuf (struct al_eth_ring*,struct mbuf*) ; 
 struct mbuf* drbr_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ napi ; 

__attribute__((used)) static void
al_eth_start_xmit(void *arg, int pending)
{
	struct al_eth_ring *tx_ring = arg;
	struct mbuf *mbuf;

	if (napi != 0) {
		tx_ring->enqueue_is_running = 1;
		al_data_memory_barrier();
	}

	while (1) {
		mtx_lock(&tx_ring->br_mtx);
		mbuf = drbr_dequeue(NULL, tx_ring->br);
		mtx_unlock(&tx_ring->br_mtx);

		if (mbuf == NULL)
			break;

		al_eth_xmit_mbuf(tx_ring, mbuf);
	}

	if (napi != 0) {
		tx_ring->enqueue_is_running = 0;
		al_data_memory_barrier();
		while (1) {
			mtx_lock(&tx_ring->br_mtx);
			mbuf = drbr_dequeue(NULL, tx_ring->br);
			mtx_unlock(&tx_ring->br_mtx);
			if (mbuf == NULL)
				break;
			al_eth_xmit_mbuf(tx_ring, mbuf);
		}
	}
}