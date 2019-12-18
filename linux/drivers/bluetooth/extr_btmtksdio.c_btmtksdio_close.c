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
typedef  int u32 ;
struct hci_dev {int dummy; } ;
struct btmtksdio_dev {int /*<<< orphan*/  func; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int C_COM_DRV_OWN ; 
 int /*<<< orphan*/  C_FW_OWN_REQ_SET ; 
 int /*<<< orphan*/  C_INT_EN_CLR ; 
 int /*<<< orphan*/  MTK_REG_CHLPCR ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btmtksdio_drv_own_query ; 
 struct btmtksdio_dev* hci_get_drvdata (struct hci_dev*) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct btmtksdio_dev*,int,int,int,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btmtksdio_close(struct hci_dev *hdev)
{
	struct btmtksdio_dev *bdev = hci_get_drvdata(hdev);
	u32 status;
	int err;

	sdio_claim_host(bdev->func);

	/* Disable interrupt */
	sdio_writel(bdev->func, C_INT_EN_CLR, MTK_REG_CHLPCR, NULL);

	sdio_release_irq(bdev->func);

	/* Return ownership to the device */
	sdio_writel(bdev->func, C_FW_OWN_REQ_SET, MTK_REG_CHLPCR, NULL);

	err = readx_poll_timeout(btmtksdio_drv_own_query, bdev, status,
				 !(status & C_COM_DRV_OWN), 2000, 1000000);
	if (err < 0)
		bt_dev_err(bdev->hdev, "Cannot return ownership to device");

	sdio_disable_func(bdev->func);

	sdio_release_host(bdev->func);

	return 0;
}