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
struct hci_uart_proto {size_t id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_INFO (char*,int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int EINVAL ; 
 size_t HCI_UART_MAX_PROTO ; 
 struct hci_uart_proto const** hup ; 

int hci_uart_register_proto(const struct hci_uart_proto *p)
{
	if (p->id >= HCI_UART_MAX_PROTO)
		return -EINVAL;

	if (hup[p->id])
		return -EEXIST;

	hup[p->id] = p;

	BT_INFO("HCI UART protocol %s registered", p->name);

	return 0;
}