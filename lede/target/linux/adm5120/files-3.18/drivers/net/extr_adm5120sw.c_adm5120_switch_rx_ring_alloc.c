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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RX_DESCS_SIZE ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  RX_SKBS_SIZE ; 
 int /*<<< orphan*/  SKB_ALLOC_LEN ; 
 int /*<<< orphan*/  SKB_RESERVE_LEN ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sk_buff** kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxl_descs ; 
 int /*<<< orphan*/  rxl_descs_dma ; 
 struct sk_buff** rxl_skbuff ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm5120_switch_rx_ring_alloc(void)
{
	int err;
	int i;

	/* init RX ring */
	rxl_descs = dma_alloc_coherent(NULL, RX_DESCS_SIZE, &rxl_descs_dma,
					GFP_ATOMIC);
	if (!rxl_descs) {
		err = -ENOMEM;
		goto err;
	}

	rxl_skbuff = kzalloc(RX_SKBS_SIZE, GFP_KERNEL);
	if (!rxl_skbuff) {
		err = -ENOMEM;
		goto err;
	}

	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb;
		skb = alloc_skb(SKB_ALLOC_LEN, GFP_ATOMIC);
		if (!skb) {
			err = -ENOMEM;
			goto err;
		}
		rxl_skbuff[i] = skb;
		skb_reserve(skb, SKB_RESERVE_LEN);
	}

	return 0;

err:
	return err;
}