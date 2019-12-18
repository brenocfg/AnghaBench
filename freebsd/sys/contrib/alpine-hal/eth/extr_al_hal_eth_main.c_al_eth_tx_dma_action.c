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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_udma_q {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_udma_desc_action_add (struct al_udma_q*,int /*<<< orphan*/ ) ; 

void al_eth_tx_dma_action(struct al_udma_q *tx_dma_q, uint32_t tx_descs)
{
	/* add tx descriptors */
	al_udma_desc_action_add(tx_dma_q, tx_descs);
}