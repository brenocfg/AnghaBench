#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tty_struct {struct hci_uart* disc_data; } ;
struct hci_uart {TYPE_3__* hdev; int /*<<< orphan*/  proto_lock; TYPE_1__* proto; int /*<<< orphan*/  flags; struct tty_struct* tty; } ;
struct TYPE_5__ {int byte_rx; } ;
struct TYPE_6__ {TYPE_2__ stat; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* recv ) (struct hci_uart*,int /*<<< orphan*/  const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 int /*<<< orphan*/  percpu_down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unthrottle (struct tty_struct*) ; 

__attribute__((used)) static void hci_uart_tty_receive(struct tty_struct *tty, const u8 *data,
				 char *flags, int count)
{
	struct hci_uart *hu = tty->disc_data;

	if (!hu || tty != hu->tty)
		return;

	percpu_down_read(&hu->proto_lock);

	if (!test_bit(HCI_UART_PROTO_READY, &hu->flags)) {
		percpu_up_read(&hu->proto_lock);
		return;
	}

	/* It does not need a lock here as it is already protected by a mutex in
	 * tty caller
	 */
	hu->proto->recv(hu, data, count);
	percpu_up_read(&hu->proto_lock);

	if (hu->hdev)
		hu->hdev->stat.byte_rx += count;

	tty_unthrottle(tty);
}