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
struct hci_dev {int /*<<< orphan*/ * flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_uart_flush (struct hci_dev*) ; 

__attribute__((used)) static int hci_uart_close(struct hci_dev *hdev)
{
	BT_DBG("hdev %p", hdev);

	hci_uart_flush(hdev);
	hdev->flush = NULL;

	return 0;
}