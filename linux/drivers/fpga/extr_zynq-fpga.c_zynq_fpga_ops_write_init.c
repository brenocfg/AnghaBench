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
struct zynq_fpga_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  slcr; } ;
struct fpga_manager {int /*<<< orphan*/  dev; struct zynq_fpga_priv* priv; } ;
struct fpga_image_info {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_OFFSET ; 
 int CTRL_PCAP_MODE_MASK ; 
 int CTRL_PCAP_PR_MASK ; 
 int CTRL_PCAP_RATE_EN_MASK ; 
 int CTRL_PCFG_PROG_B_MASK ; 
 int CTRL_SEC_EN_MASK ; 
 int EBUSY ; 
 int EINVAL ; 
 int FPGA_MGR_ENCRYPTED_BITSTREAM ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  FPGA_RST_ALL_MASK ; 
 int /*<<< orphan*/  INIT_POLL_DELAY ; 
 int /*<<< orphan*/  INIT_POLL_TIMEOUT ; 
 int /*<<< orphan*/  LVL_SHFTR_DISABLE_ALL_MASK ; 
 int /*<<< orphan*/  LVL_SHFTR_ENABLE_PS_TO_PL ; 
 int /*<<< orphan*/  MCTRL_OFFSET ; 
 int MCTRL_PCAP_LPBK_MASK ; 
 int /*<<< orphan*/  SLCR_FPGA_RST_CTRL_OFFSET ; 
 int /*<<< orphan*/  SLCR_LVL_SHFTR_EN_OFFSET ; 
 int STATUS_DMA_Q_E ; 
 int STATUS_DMA_Q_F ; 
 int /*<<< orphan*/  STATUS_OFFSET ; 
 int STATUS_PCFG_INIT_MASK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_fpga_has_sync (char const*,size_t) ; 
 int zynq_fpga_poll_timeout (struct zynq_fpga_priv*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zynq_fpga_read (struct zynq_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_fpga_write (struct zynq_fpga_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zynq_fpga_ops_write_init(struct fpga_manager *mgr,
				    struct fpga_image_info *info,
				    const char *buf, size_t count)
{
	struct zynq_fpga_priv *priv;
	u32 ctrl, status;
	int err;

	priv = mgr->priv;

	err = clk_enable(priv->clk);
	if (err)
		return err;

	/* check if bitstream is encrypted & and system's still secure */
	if (info->flags & FPGA_MGR_ENCRYPTED_BITSTREAM) {
		ctrl = zynq_fpga_read(priv, CTRL_OFFSET);
		if (!(ctrl & CTRL_SEC_EN_MASK)) {
			dev_err(&mgr->dev,
				"System not secure, can't use crypted bitstreams\n");
			err = -EINVAL;
			goto out_err;
		}
	}

	/* don't globally reset PL if we're doing partial reconfig */
	if (!(info->flags & FPGA_MGR_PARTIAL_RECONFIG)) {
		if (!zynq_fpga_has_sync(buf, count)) {
			dev_err(&mgr->dev,
				"Invalid bitstream, could not find a sync word. Bitstream must be a byte swapped .bin file\n");
			err = -EINVAL;
			goto out_err;
		}

		/* assert AXI interface resets */
		regmap_write(priv->slcr, SLCR_FPGA_RST_CTRL_OFFSET,
			     FPGA_RST_ALL_MASK);

		/* disable all level shifters */
		regmap_write(priv->slcr, SLCR_LVL_SHFTR_EN_OFFSET,
			     LVL_SHFTR_DISABLE_ALL_MASK);
		/* enable level shifters from PS to PL */
		regmap_write(priv->slcr, SLCR_LVL_SHFTR_EN_OFFSET,
			     LVL_SHFTR_ENABLE_PS_TO_PL);

		/* create a rising edge on PCFG_INIT. PCFG_INIT follows
		 * PCFG_PROG_B, so we need to poll it after setting PCFG_PROG_B
		 * to make sure the rising edge actually happens.
		 * Note: PCFG_PROG_B is low active, sequence as described in
		 * UG585 v1.10 page 211
		 */
		ctrl = zynq_fpga_read(priv, CTRL_OFFSET);
		ctrl |= CTRL_PCFG_PROG_B_MASK;

		zynq_fpga_write(priv, CTRL_OFFSET, ctrl);

		err = zynq_fpga_poll_timeout(priv, STATUS_OFFSET, status,
					     status & STATUS_PCFG_INIT_MASK,
					     INIT_POLL_DELAY,
					     INIT_POLL_TIMEOUT);
		if (err) {
			dev_err(&mgr->dev, "Timeout waiting for PCFG_INIT\n");
			goto out_err;
		}

		ctrl = zynq_fpga_read(priv, CTRL_OFFSET);
		ctrl &= ~CTRL_PCFG_PROG_B_MASK;

		zynq_fpga_write(priv, CTRL_OFFSET, ctrl);

		err = zynq_fpga_poll_timeout(priv, STATUS_OFFSET, status,
					     !(status & STATUS_PCFG_INIT_MASK),
					     INIT_POLL_DELAY,
					     INIT_POLL_TIMEOUT);
		if (err) {
			dev_err(&mgr->dev, "Timeout waiting for !PCFG_INIT\n");
			goto out_err;
		}

		ctrl = zynq_fpga_read(priv, CTRL_OFFSET);
		ctrl |= CTRL_PCFG_PROG_B_MASK;

		zynq_fpga_write(priv, CTRL_OFFSET, ctrl);

		err = zynq_fpga_poll_timeout(priv, STATUS_OFFSET, status,
					     status & STATUS_PCFG_INIT_MASK,
					     INIT_POLL_DELAY,
					     INIT_POLL_TIMEOUT);
		if (err) {
			dev_err(&mgr->dev, "Timeout waiting for PCFG_INIT\n");
			goto out_err;
		}
	}

	/* set configuration register with following options:
	 * - enable PCAP interface
	 * - set throughput for maximum speed (if bistream not crypted)
	 * - set CPU in user mode
	 */
	ctrl = zynq_fpga_read(priv, CTRL_OFFSET);
	if (info->flags & FPGA_MGR_ENCRYPTED_BITSTREAM)
		zynq_fpga_write(priv, CTRL_OFFSET,
				(CTRL_PCAP_PR_MASK | CTRL_PCAP_MODE_MASK
				 | CTRL_PCAP_RATE_EN_MASK | ctrl));
	else
		zynq_fpga_write(priv, CTRL_OFFSET,
				(CTRL_PCAP_PR_MASK | CTRL_PCAP_MODE_MASK
				 | ctrl));


	/* We expect that the command queue is empty right now. */
	status = zynq_fpga_read(priv, STATUS_OFFSET);
	if ((status & STATUS_DMA_Q_F) ||
	    (status & STATUS_DMA_Q_E) != STATUS_DMA_Q_E) {
		dev_err(&mgr->dev, "DMA command queue not right\n");
		err = -EBUSY;
		goto out_err;
	}

	/* ensure internal PCAP loopback is disabled */
	ctrl = zynq_fpga_read(priv, MCTRL_OFFSET);
	zynq_fpga_write(priv, MCTRL_OFFSET, (~MCTRL_PCAP_LPBK_MASK & ctrl));

	clk_disable(priv->clk);

	return 0;

out_err:
	clk_disable(priv->clk);

	return err;
}