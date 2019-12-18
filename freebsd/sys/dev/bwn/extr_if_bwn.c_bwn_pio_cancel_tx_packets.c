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
struct bwn_pio_txqueue {struct bwn_pio_txpkt* tq_pkts; } ;
struct bwn_pio_txpkt {int /*<<< orphan*/ * tp_m; } ;

/* Variables and functions */
 unsigned int N (struct bwn_pio_txpkt*) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwn_pio_cancel_tx_packets(struct bwn_pio_txqueue *tq)
{
	struct bwn_pio_txpkt *tp;
	unsigned int i;

	for (i = 0; i < N(tq->tq_pkts); i++) {
		tp = &(tq->tq_pkts[i]);
		if (tp->tp_m) {
			m_freem(tp->tp_m);
			tp->tp_m = NULL;
		}
	}
}