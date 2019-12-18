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
typedef  int u8 ;
struct hci_dev {int dummy; } ;
struct btmtkuart_dev {int /*<<< orphan*/  desired_speed; int /*<<< orphan*/  curr_speed; int /*<<< orphan*/  serdev; } ;
struct btmtk_hci_wmt_params {int flag; int dlen; int /*<<< orphan*/ * status; int /*<<< orphan*/ * data; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  MTK_WMT_HIF ; 
 int /*<<< orphan*/  MTK_WMT_TEST ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct btmtkuart_dev* hci_get_drvdata (struct hci_dev*) ; 
 int mtk_hci_wmt_sync (struct hci_dev*,struct btmtk_hci_wmt_params*) ; 
 int serdev_device_set_baudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdev_device_set_flow_control (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serdev_device_wait_until_sent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int serdev_device_write (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int btmtkuart_change_baudrate(struct hci_dev *hdev)
{
	struct btmtkuart_dev *bdev = hci_get_drvdata(hdev);
	struct btmtk_hci_wmt_params wmt_params;
	__le32 baudrate;
	u8 param;
	int err;

	/* Indicate the device to enter the probe state the host is
	 * ready to change a new baudrate.
	 */
	baudrate = cpu_to_le32(bdev->desired_speed);
	wmt_params.op = MTK_WMT_HIF;
	wmt_params.flag = 1;
	wmt_params.dlen = 4;
	wmt_params.data = &baudrate;
	wmt_params.status = NULL;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to device baudrate (%d)", err);
		return err;
	}

	err = serdev_device_set_baudrate(bdev->serdev,
					 bdev->desired_speed);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to set up host baudrate (%d)",
			   err);
		return err;
	}

	serdev_device_set_flow_control(bdev->serdev, false);

	/* Send a dummy byte 0xff to activate the new baudrate */
	param = 0xff;
	err = serdev_device_write(bdev->serdev, &param, sizeof(param),
				  MAX_SCHEDULE_TIMEOUT);
	if (err < 0 || err < sizeof(param))
		return err;

	serdev_device_wait_until_sent(bdev->serdev, 0);

	/* Wait some time for the device changing baudrate done */
	usleep_range(20000, 22000);

	/* Test the new baudrate */
	wmt_params.op = MTK_WMT_TEST;
	wmt_params.flag = 7;
	wmt_params.dlen = 0;
	wmt_params.data = NULL;
	wmt_params.status = NULL;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to test new baudrate (%d)",
			   err);
		return err;
	}

	bdev->curr_speed = bdev->desired_speed;

	return 0;
}