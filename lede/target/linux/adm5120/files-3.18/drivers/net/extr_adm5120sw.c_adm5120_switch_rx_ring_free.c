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

/* Variables and functions */
 int /*<<< orphan*/  RX_DESCS_SIZE ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  kfree_skb (scalar_t__) ; 
 scalar_t__ rxl_descs ; 
 int /*<<< orphan*/  rxl_descs_dma ; 
 scalar_t__* rxl_skbuff ; 

__attribute__((used)) static void adm5120_switch_rx_ring_free(void)
{
	int i;

	if (rxl_skbuff) {
		for (i = 0; i < RX_RING_SIZE; i++)
			if (rxl_skbuff[i])
				kfree_skb(rxl_skbuff[i]);
		kfree(rxl_skbuff);
	}

	if (rxl_descs)
		dma_free_coherent(NULL, RX_DESCS_SIZE, rxl_descs,
			rxl_descs_dma);
}