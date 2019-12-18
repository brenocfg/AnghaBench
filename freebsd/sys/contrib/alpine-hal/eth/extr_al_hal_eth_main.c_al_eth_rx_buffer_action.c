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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_udma_q {int /*<<< orphan*/  qid; TYPE_1__* udma; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_udma_desc_action_add (struct al_udma_q*,int /*<<< orphan*/ ) ; 

void al_eth_rx_buffer_action(struct al_udma_q *rx_dma_q, uint32_t descs_num)
{
	al_dbg("[%s]: update the rx engine tail pointer: queue %d. descs %d\n",
		 rx_dma_q->udma->name, rx_dma_q->qid, descs_num);

	/* add rx descriptor */
	al_udma_desc_action_add(rx_dma_q, descs_num);
}