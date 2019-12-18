#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct hci_uart {int init_speed; int oper_speed; int /*<<< orphan*/  hdev_flags; TYPE_1__* proto; int /*<<< orphan*/  serdev; } ;
struct hci_rp_read_local_version {int dummy; } ;
struct hci_dev {int dummy; } ;
struct TYPE_2__ {int init_speed; int oper_speed; int (* set_baudrate ) (struct hci_uart*,unsigned int) ;int (* setup ) (struct hci_uart*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_VERSION ; 
 int /*<<< orphan*/  HCI_UART_VND_DETECT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  serdev_device_set_baudrate (int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct hci_uart*,unsigned int) ; 
 int stub2 (struct hci_uart*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_uart_setup(struct hci_dev *hdev)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);
	struct hci_rp_read_local_version *ver;
	struct sk_buff *skb;
	unsigned int speed;
	int err;

	/* Init speed if any */
	if (hu->init_speed)
		speed = hu->init_speed;
	else if (hu->proto->init_speed)
		speed = hu->proto->init_speed;
	else
		speed = 0;

	if (speed)
		serdev_device_set_baudrate(hu->serdev, speed);

	/* Operational speed if any */
	if (hu->oper_speed)
		speed = hu->oper_speed;
	else if (hu->proto->oper_speed)
		speed = hu->proto->oper_speed;
	else
		speed = 0;

	if (hu->proto->set_baudrate && speed) {
		err = hu->proto->set_baudrate(hu, speed);
		if (err)
			bt_dev_err(hdev, "Failed to set baudrate");
		else
			serdev_device_set_baudrate(hu->serdev, speed);
	}

	if (hu->proto->setup)
		return hu->proto->setup(hu);

	if (!test_bit(HCI_UART_VND_DETECT, &hu->hdev_flags))
		return 0;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, NULL,
			     HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		bt_dev_err(hdev, "Reading local version info failed (%ld)",
			   PTR_ERR(skb));
		return 0;
	}

	if (skb->len != sizeof(*ver))
		bt_dev_err(hdev, "Event length mismatch for version info");

	kfree_skb(skb);
	return 0;
}