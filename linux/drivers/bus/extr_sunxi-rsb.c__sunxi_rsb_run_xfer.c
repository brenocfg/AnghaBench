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
struct sunxi_rsb {int status; int /*<<< orphan*/  dev; scalar_t__ regs; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ RSB_CTRL ; 
 int RSB_CTRL_ABORT_TRANS ; 
 int RSB_CTRL_GLOBAL_INT_ENB ; 
 int RSB_CTRL_START_TRANS ; 
 scalar_t__ RSB_INTE ; 
 scalar_t__ RSB_INTS ; 
 int RSB_INTS_LOAD_BSY ; 
 int RSB_INTS_TRANS_ERR ; 
 int RSB_INTS_TRANS_ERR_ACK ; 
 int RSB_INTS_TRANS_ERR_DATA ; 
 int RSB_INTS_TRANS_OVER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_io_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int _sunxi_rsb_run_xfer(struct sunxi_rsb *rsb)
{
	if (readl(rsb->regs + RSB_CTRL) & RSB_CTRL_START_TRANS) {
		dev_dbg(rsb->dev, "RSB transfer still in progress\n");
		return -EBUSY;
	}

	reinit_completion(&rsb->complete);

	writel(RSB_INTS_LOAD_BSY | RSB_INTS_TRANS_ERR | RSB_INTS_TRANS_OVER,
	       rsb->regs + RSB_INTE);
	writel(RSB_CTRL_START_TRANS | RSB_CTRL_GLOBAL_INT_ENB,
	       rsb->regs + RSB_CTRL);

	if (!wait_for_completion_io_timeout(&rsb->complete,
					    msecs_to_jiffies(100))) {
		dev_dbg(rsb->dev, "RSB timeout\n");

		/* abort the transfer */
		writel(RSB_CTRL_ABORT_TRANS, rsb->regs + RSB_CTRL);

		/* clear any interrupt flags */
		writel(readl(rsb->regs + RSB_INTS), rsb->regs + RSB_INTS);

		return -ETIMEDOUT;
	}

	if (rsb->status & RSB_INTS_LOAD_BSY) {
		dev_dbg(rsb->dev, "RSB busy\n");
		return -EBUSY;
	}

	if (rsb->status & RSB_INTS_TRANS_ERR) {
		if (rsb->status & RSB_INTS_TRANS_ERR_ACK) {
			dev_dbg(rsb->dev, "RSB slave nack\n");
			return -EINVAL;
		}

		if (rsb->status & RSB_INTS_TRANS_ERR_DATA) {
			dev_dbg(rsb->dev, "RSB transfer data error\n");
			return -EIO;
		}
	}

	return 0;
}