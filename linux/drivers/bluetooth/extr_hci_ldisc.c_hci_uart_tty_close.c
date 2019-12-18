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
struct tty_struct {struct hci_uart* disc_data; } ;
struct hci_uart {int /*<<< orphan*/  proto_lock; int /*<<< orphan*/  flags; TYPE_1__* proto; int /*<<< orphan*/  write_work; struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct hci_uart*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*) ; 
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 int /*<<< orphan*/  HCI_UART_PROTO_SET ; 
 int /*<<< orphan*/  HCI_UART_REGISTERED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_uart_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree (struct hci_uart*) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_free_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_uart_tty_close(struct tty_struct *tty)
{
	struct hci_uart *hu = tty->disc_data;
	struct hci_dev *hdev;

	BT_DBG("tty %p", tty);

	/* Detach from the tty */
	tty->disc_data = NULL;

	if (!hu)
		return;

	hdev = hu->hdev;
	if (hdev)
		hci_uart_close(hdev);

	if (test_bit(HCI_UART_PROTO_READY, &hu->flags)) {
		percpu_down_write(&hu->proto_lock);
		clear_bit(HCI_UART_PROTO_READY, &hu->flags);
		percpu_up_write(&hu->proto_lock);

		cancel_work_sync(&hu->write_work);

		if (hdev) {
			if (test_bit(HCI_UART_REGISTERED, &hu->flags))
				hci_unregister_dev(hdev);
			hci_free_dev(hdev);
		}
		hu->proto->close(hu);
	}
	clear_bit(HCI_UART_PROTO_SET, &hu->flags);

	percpu_free_rwsem(&hu->proto_lock);

	kfree(hu);
}