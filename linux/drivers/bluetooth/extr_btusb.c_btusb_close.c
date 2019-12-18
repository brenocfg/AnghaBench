#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hci_dev {int /*<<< orphan*/  name; } ;
struct btusb_data {int /*<<< orphan*/  deferred; TYPE_1__* intf; int /*<<< orphan*/  flags; int /*<<< orphan*/  waker; int /*<<< orphan*/  work; } ;
struct TYPE_3__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_BULK_RUNNING ; 
 int /*<<< orphan*/  BTUSB_DIAG_RUNNING ; 
 int /*<<< orphan*/  BTUSB_INTR_RUNNING ; 
 int /*<<< orphan*/  BTUSB_ISOC_RUNNING ; 
 int /*<<< orphan*/  BTUSB_WAKEUP_DISABLE ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btusb_free_frags (struct btusb_data*) ; 
 int /*<<< orphan*/  btusb_stop_traffic (struct btusb_data*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_scuttle_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btusb_close(struct hci_dev *hdev)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	int err;

	BT_DBG("%s", hdev->name);

	cancel_work_sync(&data->work);
	cancel_work_sync(&data->waker);

	clear_bit(BTUSB_ISOC_RUNNING, &data->flags);
	clear_bit(BTUSB_BULK_RUNNING, &data->flags);
	clear_bit(BTUSB_INTR_RUNNING, &data->flags);
	clear_bit(BTUSB_DIAG_RUNNING, &data->flags);

	btusb_stop_traffic(data);
	btusb_free_frags(data);

	err = usb_autopm_get_interface(data->intf);
	if (err < 0)
		goto failed;

	data->intf->needs_remote_wakeup = 0;

	/* Enable remote wake up for auto-suspend */
	if (test_bit(BTUSB_WAKEUP_DISABLE, &data->flags))
		data->intf->needs_remote_wakeup = 1;

	usb_autopm_put_interface(data->intf);

failed:
	usb_scuttle_anchored_urbs(&data->deferred);
	return 0;
}