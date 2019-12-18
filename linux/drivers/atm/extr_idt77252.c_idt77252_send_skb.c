#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vc_map {int /*<<< orphan*/  flags; } ;
struct sk_buff {int dummy; } ;
struct idt77252_dev {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int aal; } ;
struct atm_vcc {TYPE_2__* stats; TYPE_1__ qos; struct vc_map* dev_data; struct atm_dev* dev; } ;
struct atm_dev {struct idt77252_dev* dev_data; } ;
struct TYPE_8__ {struct atm_vcc* vcc; } ;
struct TYPE_7__ {scalar_t__ nr_frags; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_err; } ;

/* Variables and functions */
#define  ATM_AAL0 130 
#define  ATM_AAL1 129 
#define  ATM_AAL5 128 
 TYPE_4__* ATM_SKB (struct sk_buff*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  VCF_TX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int queue_skb (struct idt77252_dev*,struct vc_map*,struct sk_buff*,int) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
idt77252_send_skb(struct atm_vcc *vcc, struct sk_buff *skb, int oam)
{
	struct atm_dev *dev = vcc->dev;
	struct idt77252_dev *card = dev->dev_data;
	struct vc_map *vc = vcc->dev_data;
	int err;

	if (vc == NULL) {
		printk("%s: NULL connection in send().\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		dev_kfree_skb(skb);
		return -EINVAL;
	}
	if (!test_bit(VCF_TX, &vc->flags)) {
		printk("%s: Trying to transmit on a non-tx VC.\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		dev_kfree_skb(skb);
		return -EINVAL;
	}

	switch (vcc->qos.aal) {
	case ATM_AAL0:
	case ATM_AAL1:
	case ATM_AAL5:
		break;
	default:
		printk("%s: Unsupported AAL: %d\n", card->name, vcc->qos.aal);
		atomic_inc(&vcc->stats->tx_err);
		dev_kfree_skb(skb);
		return -EINVAL;
	}

	if (skb_shinfo(skb)->nr_frags != 0) {
		printk("%s: No scatter-gather yet.\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		dev_kfree_skb(skb);
		return -EINVAL;
	}
	ATM_SKB(skb)->vcc = vcc;

	err = queue_skb(card, vc, skb, oam);
	if (err) {
		atomic_inc(&vcc->stats->tx_err);
		dev_kfree_skb(skb);
		return err;
	}

	return 0;
}