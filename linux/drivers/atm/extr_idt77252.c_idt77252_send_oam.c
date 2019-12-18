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
struct sk_buff {int /*<<< orphan*/  truesize; } ;
struct idt77252_dev {int /*<<< orphan*/  name; } ;
struct atm_vcc {TYPE_1__* stats; struct atm_dev* dev; } ;
struct atm_dev {struct idt77252_dev* dev_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_err; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int idt77252_send_skb (struct atm_vcc*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,int) ; 

__attribute__((used)) static int
idt77252_send_oam(struct atm_vcc *vcc, void *cell, int flags)
{
	struct atm_dev *dev = vcc->dev;
	struct idt77252_dev *card = dev->dev_data;
	struct sk_buff *skb;

	skb = dev_alloc_skb(64);
	if (!skb) {
		printk("%s: Out of memory in send_oam().\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		return -ENOMEM;
	}
	refcount_add(skb->truesize, &sk_atm(vcc)->sk_wmem_alloc);

	skb_put_data(skb, cell, 52);

	return idt77252_send_skb(vcc, skb, 1);
}