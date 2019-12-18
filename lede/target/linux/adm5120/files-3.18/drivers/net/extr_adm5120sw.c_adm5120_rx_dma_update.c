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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct dma_desc {int buf1; int /*<<< orphan*/  buflen; scalar_t__ buf2; scalar_t__ misc; } ;

/* Variables and functions */
 int DESC_ADDR (int /*<<< orphan*/ ) ; 
 int DESC_EOR ; 
 int DESC_OWN ; 
 int /*<<< orphan*/  RX_MAX_PKTLEN ; 

__attribute__((used)) static inline void adm5120_rx_dma_update(struct dma_desc *desc,
	struct sk_buff *skb, int end)
{
	desc->misc = 0;
	desc->buf2 = 0;
	desc->buflen = RX_MAX_PKTLEN;
	desc->buf1 = DESC_ADDR(skb->data) |
		DESC_OWN | (end ? DESC_EOR : 0);
}