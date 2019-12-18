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
struct fpga_manager {int /*<<< orphan*/  dev; struct a10_fpga_priv* priv; } ;
struct fpga_image_info {int dummy; } ;
struct a10_fpga_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_01_OFST ; 
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_01_S2F_NCE ; 
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG ; 
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_01_S2F_PR_REQUEST ; 
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_02_EN_CFG_CTRL ; 
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_02_OFST ; 
 int A10_FPGAMGR_IMGCFG_STAT_F2S_CONDONE_PIN ; 
 int A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN ; 
 int A10_FPGAMGR_IMGCFG_STAT_F2S_USERMODE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socfpga_a10_fpga_generate_dclks (struct a10_fpga_priv*,int) ; 
 int socfpga_a10_fpga_read_stat (struct a10_fpga_priv*) ; 
 int socfpga_a10_fpga_wait_for_pr_done (struct a10_fpga_priv*) ; 

__attribute__((used)) static int socfpga_a10_fpga_write_complete(struct fpga_manager *mgr,
					   struct fpga_image_info *info)
{
	struct a10_fpga_priv *priv = mgr->priv;
	u32 reg;
	int ret;

	/* Wait for pr_done */
	ret = socfpga_a10_fpga_wait_for_pr_done(priv);

	/* Clear pr_request */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_PR_REQUEST, 0);

	/* Send some clocks to clear out any errors */
	socfpga_a10_fpga_generate_dclks(priv, 256);

	/* Disable s2f dclk and data */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_02_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_02_EN_CFG_CTRL, 0);

	/* Deassert chip select */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NCE,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NCE);

	/* Disable data, dclk, nce, and pr_request override to CSS */
	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_01_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG,
			   A10_FPGAMGR_IMGCFG_CTL_01_S2F_NENABLE_CONFIG);

	/* Return any errors regarding pr_done or pr_error */
	if (ret)
		return ret;

	/* Final check */
	reg = socfpga_a10_fpga_read_stat(priv);

	if (((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_USERMODE) == 0) ||
	    ((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_CONDONE_PIN) == 0) ||
	    ((reg & A10_FPGAMGR_IMGCFG_STAT_F2S_NSTATUS_PIN) == 0)) {
		dev_dbg(&mgr->dev,
			"Timeout in final check. Status=%08xf\n", reg);
		return -ETIMEDOUT;
	}

	return 0;
}