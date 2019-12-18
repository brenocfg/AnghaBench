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
struct hci_uart {TYPE_3__* tty; scalar_t__ serdev; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ tiocmset; scalar_t__ tiocmget; } ;

/* Variables and functions */

bool hci_uart_has_flow_control(struct hci_uart *hu)
{
	/* serdev nodes check if the needed operations are present */
	if (hu->serdev)
		return true;

	if (hu->tty->driver->ops->tiocmget && hu->tty->driver->ops->tiocmset)
		return true;

	return false;
}