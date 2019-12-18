#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct btmrvl_sdio_card {TYPE_2__* reg; int /*<<< orphan*/  func; } ;
struct TYPE_3__ {struct btmrvl_sdio_card* card; } ;
struct btmrvl_private {TYPE_1__ btmrvl_dev; } ;
typedef  enum rdwr_status { ____Placeholder_rdwr_status } rdwr_status ;
struct TYPE_4__ {int /*<<< orphan*/  fw_dump_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BT_INFO (char*) ; 
 scalar_t__ FW_DUMP_DONE ; 
 scalar_t__ FW_DUMP_HOST_READY ; 
 int MAX_POLL_TRIES ; 
 int RDWR_STATUS_DONE ; 
 int RDWR_STATUS_FAILURE ; 
 int RDWR_STATUS_SUCCESS ; 
 scalar_t__ sdio_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static enum
rdwr_status btmrvl_sdio_rdwr_firmware(struct btmrvl_private *priv,
				      u8 doneflag)
{
	struct btmrvl_sdio_card *card = priv->btmrvl_dev.card;
	int ret, tries;
	u8 ctrl_data = 0;

	sdio_writeb(card->func, FW_DUMP_HOST_READY, card->reg->fw_dump_ctrl,
		    &ret);

	if (ret) {
		BT_ERR("SDIO write err");
		return RDWR_STATUS_FAILURE;
	}

	for (tries = 0; tries < MAX_POLL_TRIES; tries++) {
		ctrl_data = sdio_readb(card->func, card->reg->fw_dump_ctrl,
				       &ret);

		if (ret) {
			BT_ERR("SDIO read err");
			return RDWR_STATUS_FAILURE;
		}

		if (ctrl_data == FW_DUMP_DONE)
			break;
		if (doneflag && ctrl_data == doneflag)
			return RDWR_STATUS_DONE;
		if (ctrl_data != FW_DUMP_HOST_READY) {
			BT_INFO("The ctrl reg was changed, re-try again!");
			sdio_writeb(card->func, FW_DUMP_HOST_READY,
				    card->reg->fw_dump_ctrl, &ret);
			if (ret) {
				BT_ERR("SDIO write err");
				return RDWR_STATUS_FAILURE;
			}
		}
		usleep_range(100, 200);
	}

	if (ctrl_data == FW_DUMP_HOST_READY) {
		BT_ERR("Fail to pull ctrl_data");
		return RDWR_STATUS_FAILURE;
	}

	return RDWR_STATUS_SUCCESS;
}