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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct btusb_data {int /*<<< orphan*/  tx_anchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btusb_free_frags (struct btusb_data*) ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btusb_flush(struct hci_dev *hdev)
{
	struct btusb_data *data = hci_get_drvdata(hdev);

	BT_DBG("%s", hdev->name);

	usb_kill_anchored_urbs(&data->tx_anchor);
	btusb_free_frags(data);

	return 0;
}