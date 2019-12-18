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
struct hci_uart {int /*<<< orphan*/  serdev; TYPE_1__* proto; int /*<<< orphan*/  write_work; int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hci_uart*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  serdev_device_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*) ; 

void hci_uart_unregister_device(struct hci_uart *hu)
{
	struct hci_dev *hdev = hu->hdev;

	clear_bit(HCI_UART_PROTO_READY, &hu->flags);
	hci_unregister_dev(hdev);
	hci_free_dev(hdev);

	cancel_work_sync(&hu->write_work);

	hu->proto->close(hu);
	serdev_device_close(hu->serdev);
}