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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; int /*<<< orphan*/ * head; } ;
struct idt77252_dev {int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/ * fbq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT77252_PRV_PADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  IDT77252_PRV_POOL (struct sk_buff*) ; 
 int /*<<< orphan*/  SAR_FB_SIZE_0 ; 
 int /*<<< orphan*/  SAR_FB_SIZE_1 ; 
 int /*<<< orphan*/  SAR_FB_SIZE_2 ; 
 int /*<<< orphan*/  SAR_FB_SIZE_3 ; 
 scalar_t__ idt77252_fbq_full (struct idt77252_dev*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
push_rx_skb(struct idt77252_dev *card, struct sk_buff *skb, int queue)
{
	unsigned long flags;
	u32 handle;
	u32 addr;

	skb->data = skb->head;
	skb_reset_tail_pointer(skb);
	skb->len = 0;

	skb_reserve(skb, 16);

	switch (queue) {
	case 0:
		skb_put(skb, SAR_FB_SIZE_0);
		break;
	case 1:
		skb_put(skb, SAR_FB_SIZE_1);
		break;
	case 2:
		skb_put(skb, SAR_FB_SIZE_2);
		break;
	case 3:
		skb_put(skb, SAR_FB_SIZE_3);
		break;
	default:
		return -1;
	}

	if (idt77252_fbq_full(card, queue))
		return -1;

	memset(&skb->data[(skb->len & ~(0x3f)) - 64], 0, 2 * sizeof(u32));

	handle = IDT77252_PRV_POOL(skb);
	addr = IDT77252_PRV_PADDR(skb);

	spin_lock_irqsave(&card->cmd_lock, flags);
	writel(handle, card->fbq[queue]);
	writel(addr, card->fbq[queue]);
	spin_unlock_irqrestore(&card->cmd_lock, flags);

	return 0;
}