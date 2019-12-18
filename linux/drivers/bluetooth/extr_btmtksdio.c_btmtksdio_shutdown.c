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
struct btmtksdio_dev {int /*<<< orphan*/  dev; } ;
struct btmtk_hci_wmt_params {int dlen; int* data; int /*<<< orphan*/ * status; scalar_t__ flag; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_WMT_FUNC_CTRL ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 struct btmtksdio_dev* hci_get_drvdata (struct hci_dev*) ; 
 int mtk_hci_wmt_sync (struct hci_dev*,struct btmtk_hci_wmt_params*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmtksdio_shutdown(struct hci_dev *hdev)
{
	struct btmtksdio_dev *bdev = hci_get_drvdata(hdev);
	struct btmtk_hci_wmt_params wmt_params;
	u8 param = 0x0;
	int err;

	/* Get back the state to be consistent with the state
	 * in btmtksdio_setup.
	 */
	pm_runtime_get_sync(bdev->dev);

	/* Disable the device */
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

	pm_runtime_put_noidle(bdev->dev);
	pm_runtime_disable(bdev->dev);

	return 0;
}