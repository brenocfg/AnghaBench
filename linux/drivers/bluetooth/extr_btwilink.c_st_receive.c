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
struct ti_st {TYPE_2__* hdev; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  byte_rx; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 long EFAULT ; 
 int hci_recv_frame (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static long st_receive(void *priv_data, struct sk_buff *skb)
{
	struct ti_st *lhst = priv_data;
	int err;

	if (!skb)
		return -EFAULT;

	if (!lhst) {
		kfree_skb(skb);
		return -EFAULT;
	}

	/* Forward skb to HCI core layer */
	err = hci_recv_frame(lhst->hdev, skb);
	if (err < 0) {
		BT_ERR("Unable to push skb to HCI core(%d)", err);
		return err;
	}

	lhst->hdev->stat.byte_rx += skb->len;

	return 0;
}