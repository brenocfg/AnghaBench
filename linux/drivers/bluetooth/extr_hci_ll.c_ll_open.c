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
struct ll_struct {int /*<<< orphan*/  hcill_state; int /*<<< orphan*/  hcill_lock; int /*<<< orphan*/  tx_wait_q; int /*<<< orphan*/  txq; } ;
struct ll_device {int /*<<< orphan*/  ext_clk; } ;
struct hci_uart {scalar_t__ serdev; struct ll_struct* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCILL_AWAKE ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct ll_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ll_device* serdev_device_get_drvdata (scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ll_open(struct hci_uart *hu)
{
	struct ll_struct *ll;

	BT_DBG("hu %p", hu);

	ll = kzalloc(sizeof(*ll), GFP_KERNEL);
	if (!ll)
		return -ENOMEM;

	skb_queue_head_init(&ll->txq);
	skb_queue_head_init(&ll->tx_wait_q);
	spin_lock_init(&ll->hcill_lock);

	ll->hcill_state = HCILL_AWAKE;

	hu->priv = ll;

	if (hu->serdev) {
		struct ll_device *lldev = serdev_device_get_drvdata(hu->serdev);

		if (!IS_ERR(lldev->ext_clk))
			clk_prepare_enable(lldev->ext_clk);
	}

	return 0;
}