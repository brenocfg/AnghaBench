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
struct uniphier_mdmac_device {scalar_t__ reg_base; } ;
struct uniphier_mdmac_chan {scalar_t__ reg_ch_base; int /*<<< orphan*/  chan_id; struct uniphier_mdmac_device* mdev; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIPHIER_MDMAC_CH_IRQ_REQ ; 
 int UNIPHIER_MDMAC_CH_IRQ__ABORT ; 
 scalar_t__ UNIPHIER_MDMAC_CMD ; 
 int UNIPHIER_MDMAC_CMD_ABORT ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int uniphier_mdmac_abort(struct uniphier_mdmac_chan *mc)
{
	struct uniphier_mdmac_device *mdev = mc->mdev;
	u32 irq_flag = UNIPHIER_MDMAC_CH_IRQ__ABORT;
	u32 val;

	/* write 1 to clear */
	writel(irq_flag, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ);

	writel(UNIPHIER_MDMAC_CMD_ABORT | BIT(mc->chan_id),
	       mdev->reg_base + UNIPHIER_MDMAC_CMD);

	/*
	 * Abort should be accepted soon. We poll the bit here instead of
	 * waiting for the interrupt.
	 */
	return readl_poll_timeout(mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ,
				  val, val & irq_flag, 0, 20);
}