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
struct mrvl_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  rawq; int /*<<< orphan*/  txq; } ;
struct hci_uart {scalar_t__ serdev; struct mrvl_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_uart*) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STATE_CHIP_VER_PENDING ; 
 int /*<<< orphan*/  hci_uart_has_flow_control (struct hci_uart*) ; 
 int /*<<< orphan*/  kfree (struct mrvl_data*) ; 
 struct mrvl_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int serdev_device_open (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mrvl_open(struct hci_uart *hu)
{
	struct mrvl_data *mrvl;
	int ret;

	BT_DBG("hu %p", hu);

	if (!hci_uart_has_flow_control(hu))
		return -EOPNOTSUPP;

	mrvl = kzalloc(sizeof(*mrvl), GFP_KERNEL);
	if (!mrvl)
		return -ENOMEM;

	skb_queue_head_init(&mrvl->txq);
	skb_queue_head_init(&mrvl->rawq);

	set_bit(STATE_CHIP_VER_PENDING, &mrvl->flags);

	hu->priv = mrvl;

	if (hu->serdev) {
		ret = serdev_device_open(hu->serdev);
		if (ret)
			goto err;
	}

	return 0;
err:
	kfree(mrvl);

	return ret;
}