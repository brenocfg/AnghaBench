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
struct al_udma_q {int /*<<< orphan*/  qid; TYPE_1__* udma; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_udma_cdesc_ack (struct al_udma_q*,int) ; 
 int al_udma_cdesc_get_all (struct al_udma_q*,int /*<<< orphan*/ *) ; 

int al_eth_comp_tx_get(struct al_udma_q *tx_dma_q)
{
	int rc;

	rc = al_udma_cdesc_get_all(tx_dma_q, NULL);
	if (rc != 0) {
		al_udma_cdesc_ack(tx_dma_q, rc);
		al_dbg("[%s %d]: tx completion: descs (%d)\n",
			 tx_dma_q->udma->name, tx_dma_q->qid, rc);
	}

	return rc;
}