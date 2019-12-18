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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tci_sleep ;
struct sk_buff {int dummy; } ;
struct hci_dev {int dummy; } ;
struct btmtkuart_dev {TYPE_1__* data; int /*<<< orphan*/  tx_state; } ;
struct btmtk_tci_sleep {int mode; scalar_t__ time_compensation; scalar_t__ host_wakeup_pin; void* host_duration; void* duration; } ;
struct btmtk_hci_wmt_params {int flag; int dlen; int* data; int* status; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwname; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTMTKUART_REQUIRED_WAKEUP ; 
 int BTMTK_WMT_ON_DONE ; 
 int BTMTK_WMT_ON_PROGRESS ; 
 int BTMTK_WMT_PATCH_DONE ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  MTK_WMT_FUNC_CTRL ; 
 int /*<<< orphan*/  MTK_WMT_SEMAPHORE ; 
 int /*<<< orphan*/  MTK_WMT_WAKEUP ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int,struct btmtk_tci_sleep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  btmtkuart_change_baudrate (struct hci_dev*) ; 
 int /*<<< orphan*/  btmtkuart_func_query ; 
 scalar_t__ btmtkuart_is_standalone (struct btmtkuart_dev*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 struct btmtkuart_dev* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int mtk_hci_wmt_sync (struct hci_dev*,struct btmtk_hci_wmt_params*) ; 
 int mtk_setup_firmware (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct hci_dev*,int,int,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmtkuart_setup(struct hci_dev *hdev)
{
	struct btmtkuart_dev *bdev = hci_get_drvdata(hdev);
	struct btmtk_hci_wmt_params wmt_params;
	ktime_t calltime, delta, rettime;
	struct btmtk_tci_sleep tci_sleep;
	unsigned long long duration;
	struct sk_buff *skb;
	int err, status;
	u8 param = 0x1;

	calltime = ktime_get();

	/* Wakeup MCUSYS is required for certain devices before we start to
	 * do any setups.
	 */
	if (test_bit(BTMTKUART_REQUIRED_WAKEUP, &bdev->tx_state)) {
		wmt_params.op = MTK_WMT_WAKEUP;
		wmt_params.flag = 3;
		wmt_params.dlen = 0;
		wmt_params.data = NULL;
		wmt_params.status = NULL;

		err = mtk_hci_wmt_sync(hdev, &wmt_params);
		if (err < 0) {
			bt_dev_err(hdev, "Failed to wakeup the chip (%d)", err);
			return err;
		}

		clear_bit(BTMTKUART_REQUIRED_WAKEUP, &bdev->tx_state);
	}

	if (btmtkuart_is_standalone(bdev))
		btmtkuart_change_baudrate(hdev);

	/* Query whether the firmware is already download */
	wmt_params.op = MTK_WMT_SEMAPHORE;
	wmt_params.flag = 1;
	wmt_params.dlen = 0;
	wmt_params.data = NULL;
	wmt_params.status = &status;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to query firmware status (%d)", err);
		return err;
	}

	if (status == BTMTK_WMT_PATCH_DONE) {
		bt_dev_info(hdev, "Firmware already downloaded");
		goto ignore_setup_fw;
	}

	/* Setup a firmware which the device definitely requires */
	err = mtk_setup_firmware(hdev, bdev->data->fwname);
	if (err < 0)
		return err;

ignore_setup_fw:
	/* Query whether the device is already enabled */
	err = readx_poll_timeout(btmtkuart_func_query, hdev, status,
				 status < 0 || status != BTMTK_WMT_ON_PROGRESS,
				 2000, 5000000);
	/* -ETIMEDOUT happens */
	if (err < 0)
		return err;

	/* The other errors happen in btusb_mtk_func_query */
	if (status < 0)
		return status;

	if (status == BTMTK_WMT_ON_DONE) {
		bt_dev_info(hdev, "function already on");
		goto ignore_func_on;
	}

	/* Enable Bluetooth protocol */
	wmt_params.op = MTK_WMT_FUNC_CTRL;
	wmt_params.flag = 0;
	wmt_params.dlen = sizeof(param);
	wmt_params.data = &param;
	wmt_params.status = NULL;

	err = mtk_hci_wmt_sync(hdev, &wmt_params);
	if (err < 0) {
		bt_dev_err(hdev, "Failed to send wmt func ctrl (%d)", err);
		return err;
	}

ignore_func_on:
	/* Apply the low power environment setup */
	tci_sleep.mode = 0x5;
	tci_sleep.duration = cpu_to_le16(0x640);
	tci_sleep.host_duration = cpu_to_le16(0x640);
	tci_sleep.host_wakeup_pin = 0;
	tci_sleep.time_compensation = 0;

	skb = __hci_cmd_sync(hdev, 0xfc7a, sizeof(tci_sleep), &tci_sleep,
			     HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "Failed to apply low power setting (%d)", err);
		return err;
	}
	kfree_skb(skb);

	rettime = ktime_get();
	delta = ktime_sub(rettime, calltime);
	duration = (unsigned long long)ktime_to_ns(delta) >> 10;

	bt_dev_info(hdev, "Device setup in %llu usecs", duration);

	return 0;
}