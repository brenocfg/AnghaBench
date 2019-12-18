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
struct serdev_device {int dummy; } ;
struct hci_uart {TYPE_3__* hdev; TYPE_2__* proto; int /*<<< orphan*/  flags; struct serdev_device* serdev; } ;
struct TYPE_4__ {size_t byte_rx; } ;
struct TYPE_6__ {TYPE_1__ stat; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* recv ) (struct hci_uart*,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct hci_uart* serdev_device_get_drvdata (struct serdev_device*) ; 
 int /*<<< orphan*/  stub1 (struct hci_uart*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hci_uart_receive_buf(struct serdev_device *serdev, const u8 *data,
				   size_t count)
{
	struct hci_uart *hu = serdev_device_get_drvdata(serdev);

	if (!hu || serdev != hu->serdev) {
		WARN_ON(1);
		return 0;
	}

	if (!test_bit(HCI_UART_PROTO_READY, &hu->flags))
		return 0;

	/* It does not need a lock here as it is already protected by a mutex in
	 * tty caller
	 */
	hu->proto->recv(hu, data, count);

	if (hu->hdev)
		hu->hdev->stat.byte_rx += count;

	return count;
}