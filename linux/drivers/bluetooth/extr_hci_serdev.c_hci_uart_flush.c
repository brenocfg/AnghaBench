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
struct hci_uart {TYPE_1__* proto; int /*<<< orphan*/  flags; int /*<<< orphan*/  serdev; int /*<<< orphan*/ * tx_skb; } ;
struct hci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (struct hci_uart*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_write_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_uart_flush(struct hci_dev *hdev)
{
	struct hci_uart *hu  = hci_get_drvdata(hdev);

	BT_DBG("hdev %p serdev %p", hdev, hu->serdev);

	if (hu->tx_skb) {
		kfree_skb(hu->tx_skb); hu->tx_skb = NULL;
	}

	/* Flush any pending characters in the driver and discipline. */
	serdev_device_write_flush(hu->serdev);

	if (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hu->proto->flush(hu);

	return 0;
}