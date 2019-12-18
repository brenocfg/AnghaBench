#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct mtkbtsdio_hdr {int /*<<< orphan*/  bt_type; void* reserved; void* len; } ;
struct btmtksdio_dev {TYPE_2__* hdev; int /*<<< orphan*/  func; } ;
struct TYPE_3__ {int /*<<< orphan*/  byte_tx; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MTK_REG_CTDR ; 
 int /*<<< orphan*/  MTK_SDIO_BLOCK_SIZE ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int pskb_expand_head (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (scalar_t__,int /*<<< orphan*/ ) ; 
 int sdio_writesb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int btmtksdio_tx_packet(struct btmtksdio_dev *bdev,
			       struct sk_buff *skb)
{
	struct mtkbtsdio_hdr *sdio_hdr;
	int err;

	/* Make sure that there are enough rooms for SDIO header */
	if (unlikely(skb_headroom(skb) < sizeof(*sdio_hdr))) {
		err = pskb_expand_head(skb, sizeof(*sdio_hdr), 0,
				       GFP_ATOMIC);
		if (err < 0)
			return err;
	}

	/* Prepend MediaTek SDIO Specific Header */
	skb_push(skb, sizeof(*sdio_hdr));

	sdio_hdr = (void *)skb->data;
	sdio_hdr->len = cpu_to_le16(skb->len);
	sdio_hdr->reserved = cpu_to_le16(0);
	sdio_hdr->bt_type = hci_skb_pkt_type(skb);

	err = sdio_writesb(bdev->func, MTK_REG_CTDR, skb->data,
			   round_up(skb->len, MTK_SDIO_BLOCK_SIZE));
	if (err < 0)
		goto err_skb_pull;

	bdev->hdev->stat.byte_tx += skb->len;

	kfree_skb(skb);

	return 0;

err_skb_pull:
	skb_pull(skb, sizeof(*sdio_hdr));

	return err;
}