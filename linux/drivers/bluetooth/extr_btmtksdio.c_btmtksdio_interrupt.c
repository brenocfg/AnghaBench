#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct sdio_func {int dummy; } ;
struct btmtksdio_dev {int /*<<< orphan*/  dev; TYPE_2__* hdev; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {int /*<<< orphan*/  err_rx; } ;
struct TYPE_6__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int C_INT_EN_CLR ; 
 int C_INT_EN_SET ; 
 int FW_OWN_BACK_INT ; 
 int /*<<< orphan*/  MTK_REG_CHISR ; 
 int /*<<< orphan*/  MTK_REG_CHLPCR ; 
 int RX_DONE_INT ; 
 int RX_PKT_LEN ; 
 int TX_EMPTY ; 
 int TX_FIFO_OVERFLOW ; 
 int /*<<< orphan*/  bt_dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  bt_dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  bt_dev_warn (TYPE_2__*,char*) ; 
 scalar_t__ btmtksdio_rx_packet (struct btmtksdio_dev*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 struct btmtksdio_dev* sdio_get_drvdata (struct sdio_func*) ; 
 int sdio_readl (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writel (struct sdio_func*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void btmtksdio_interrupt(struct sdio_func *func)
{
	struct btmtksdio_dev *bdev = sdio_get_drvdata(func);
	u32 int_status;
	u16 rx_size;

	/* It is required that the host gets ownership from the device before
	 * accessing any register, however, if SDIO host is not being released,
	 * a potential deadlock probably happens in a circular wait between SDIO
	 * IRQ work and PM runtime work. So, we have to explicitly release SDIO
	 * host here and claim again after the PM runtime work is all done.
	 */
	sdio_release_host(bdev->func);

	pm_runtime_get_sync(bdev->dev);

	sdio_claim_host(bdev->func);

	/* Disable interrupt */
	sdio_writel(func, C_INT_EN_CLR, MTK_REG_CHLPCR, 0);

	int_status = sdio_readl(func, MTK_REG_CHISR, NULL);

	/* Ack an interrupt as soon as possible before any operation on
	 * hardware.
	 *
	 * Note that we don't ack any status during operations to avoid race
	 * condition between the host and the device such as it's possible to
	 * mistakenly ack RX_DONE for the next packet and then cause interrupts
	 * not be raised again but there is still pending data in the hardware
	 * FIFO.
	 */
	sdio_writel(func, int_status, MTK_REG_CHISR, NULL);

	if (unlikely(!int_status))
		bt_dev_err(bdev->hdev, "CHISR is 0");

	if (int_status & FW_OWN_BACK_INT)
		bt_dev_dbg(bdev->hdev, "Get fw own back");

	if (int_status & TX_EMPTY)
		schedule_work(&bdev->tx_work);
	else if (unlikely(int_status & TX_FIFO_OVERFLOW))
		bt_dev_warn(bdev->hdev, "Tx fifo overflow");

	if (int_status & RX_DONE_INT) {
		rx_size = (int_status & RX_PKT_LEN) >> 16;

		if (btmtksdio_rx_packet(bdev, rx_size) < 0)
			bdev->hdev->stat.err_rx++;
	}

	/* Enable interrupt */
	sdio_writel(func, C_INT_EN_SET, MTK_REG_CHLPCR, 0);

	pm_runtime_mark_last_busy(bdev->dev);
	pm_runtime_put_autosuspend(bdev->dev);
}