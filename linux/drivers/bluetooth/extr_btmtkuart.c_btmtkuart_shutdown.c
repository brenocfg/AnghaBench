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
struct btmtk_hci_wmt_params {int dlen; int* data; int /*<<< orphan*/ * status; scalar_t__ flag; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_WMT_FUNC_CTRL ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int mtk_hci_wmt_sync (struct hci_dev*,struct btmtk_hci_wmt_params*) ; 

__attribute__((used)) static int btmtkuart_shutdown(struct hci_dev *hdev)
{
	struct btmtk_hci_wmt_params wmt_params;
	u8 param = 0x0;
	int err;

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

	return 0;
}