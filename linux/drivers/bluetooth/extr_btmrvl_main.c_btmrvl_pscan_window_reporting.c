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
typedef  int /*<<< orphan*/  u8 ;
struct btmrvl_sdio_card {int /*<<< orphan*/  support_pscan_win_report; } ;
struct TYPE_2__ {struct btmrvl_sdio_card* card; } ;
struct btmrvl_private {TYPE_1__ btmrvl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CMD_PSCAN_WIN_REPORT_ENABLE ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int btmrvl_send_sync_cmd (struct btmrvl_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int btmrvl_pscan_window_reporting(struct btmrvl_private *priv, u8 subcmd)
{
	struct btmrvl_sdio_card *card = priv->btmrvl_dev.card;
	int ret;

	if (!card->support_pscan_win_report)
		return 0;

	ret = btmrvl_send_sync_cmd(priv, BT_CMD_PSCAN_WIN_REPORT_ENABLE,
				   &subcmd, 1);
	if (ret)
		BT_ERR("PSCAN_WIN_REPORT_ENABLE command failed: %#x", ret);

	return ret;
}