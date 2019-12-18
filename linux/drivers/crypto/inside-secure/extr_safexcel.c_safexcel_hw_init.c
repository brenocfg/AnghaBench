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
typedef  int u32 ;
struct TYPE_2__ {int pes; int rings; int cd_offset; int rd_offset; } ;
struct safexcel_crypto_priv {int flags; TYPE_1__ config; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIP197_DEFAULT_RING_SIZE ; 
 int EIP197_DxE_THR_CTRL_EN ; 
 int EIP197_DxE_THR_CTRL_RESET_PE ; 
 int EIP197_FUNCTION_ALL ; 
 scalar_t__ EIP197_HIA_AIC (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_AIC_G (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_AIC_G_ACK ; 
 scalar_t__ EIP197_HIA_AIC_G_ENABLE_CTRL ; 
 scalar_t__ EIP197_HIA_AIC_R (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_AIC_R_ENABLE_CLR (int) ; 
 scalar_t__ EIP197_HIA_CDR (struct safexcel_crypto_priv*,int) ; 
 scalar_t__ EIP197_HIA_DFE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_DFE_CFG (int) ; 
 int EIP197_HIA_DFE_CFG_DIS_DEBUG ; 
 scalar_t__ EIP197_HIA_DFE_THR (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_DFE_THR_CTRL (int) ; 
 scalar_t__ EIP197_HIA_DSE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_DSE_CFG (int) ; 
 int EIP197_HIA_DSE_CFG_ALWAYS_BUFFERABLE ; 
 int EIP197_HIA_DSE_CFG_DIS_DEBUG ; 
 int EIP197_HIA_DSE_CFG_EN_SINGLE_WR ; 
 scalar_t__ EIP197_HIA_DSE_THR (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_DSE_THR_CTRL (int) ; 
 scalar_t__ EIP197_HIA_DSE_THR_STAT (int) ; 
 int EIP197_HIA_DxE_CFG_CTRL_CACHE_CTRL (int /*<<< orphan*/ ) ; 
 int EIP197_HIA_DxE_CFG_DATA_CACHE_CTRL (int /*<<< orphan*/ ) ; 
 int EIP197_HIA_DxE_CFG_MAX_CTRL_SIZE (int) ; 
 int EIP197_HIA_DxE_CFG_MAX_DATA_SIZE (int) ; 
 int EIP197_HIA_DxE_CFG_MIN_CTRL_SIZE (int) ; 
 int EIP197_HIA_DxE_CFG_MIN_DATA_SIZE (int) ; 
 scalar_t__ EIP197_HIA_GEN_CFG (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_HIA_MST_CTRL ; 
 scalar_t__ EIP197_HIA_RA_PE_CTRL (int) ; 
 int EIP197_HIA_RA_PE_CTRL_EN ; 
 int EIP197_HIA_RA_PE_CTRL_RESET ; 
 scalar_t__ EIP197_HIA_RDR (struct safexcel_crypto_priv*,int) ; 
 scalar_t__ EIP197_HIA_xDR_CFG ; 
 scalar_t__ EIP197_HIA_xDR_PREP_COUNT ; 
 scalar_t__ EIP197_HIA_xDR_PREP_PNTR ; 
 scalar_t__ EIP197_HIA_xDR_PROC_COUNT ; 
 scalar_t__ EIP197_HIA_xDR_PROC_PNTR ; 
 scalar_t__ EIP197_HIA_xDR_RING_SIZE ; 
 scalar_t__ EIP197_MST_CTRL ; 
 int EIP197_MST_CTRL_RD_CACHE (int /*<<< orphan*/ ) ; 
 int EIP197_MST_CTRL_TX_MAX_CMD (int) ; 
 int EIP197_MST_CTRL_WD_CACHE (int /*<<< orphan*/ ) ; 
 scalar_t__ EIP197_PE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_PE_EIP96_FUNCTION2_EN (int) ; 
 scalar_t__ EIP197_PE_EIP96_FUNCTION_EN (int) ; 
 scalar_t__ EIP197_PE_EIP96_TOKEN_CTRL (int) ; 
 int EIP197_PE_EIP96_TOKEN_CTRL_CTX_UPDATES ; 
 int EIP197_PE_EIP96_TOKEN_CTRL_ENABLE_TIMEOUT ; 
 int EIP197_PE_EIP96_TOKEN_CTRL_NO_TOKEN_WAIT ; 
 scalar_t__ EIP197_PE_IN_DBUF_THRES (int) ; 
 scalar_t__ EIP197_PE_IN_TBUF_THRES (int) ; 
 int EIP197_PE_IN_xBUF_THRES_MAX (int) ; 
 int EIP197_PE_IN_xBUF_THRES_MIN (int) ; 
 scalar_t__ EIP197_PE_OUT_DBUF_THRES (int) ; 
 int EIP197_PE_OUT_DBUF_THRES_MAX (int) ; 
 int EIP197_PE_OUT_DBUF_THRES_MIN (int) ; 
 int EIP197_TRC_CACHE ; 
 int EIP197_xDR_PREP_CLR_COUNT ; 
 int EIP197_xDR_PROC_CLR_COUNT ; 
 int GENMASK (int,int) ; 
 int /*<<< orphan*/  RD_CACHE_3BITS ; 
 int /*<<< orphan*/  RD_CACHE_4BITS ; 
 int SAFEXCEL_HW_EIP197 ; 
 int /*<<< orphan*/  WR_CACHE_3BITS ; 
 int /*<<< orphan*/  WR_CACHE_4BITS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int eip197_load_firmwares (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  eip197_trc_cache_init (struct safexcel_crypto_priv*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  safexcel_hw_setup_cdesc_rings (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  safexcel_hw_setup_rdesc_rings (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int safexcel_hw_init(struct safexcel_crypto_priv *priv)
{
	u32 val;
	int i, ret, pe;

	dev_dbg(priv->dev, "HW init: using %d pipe(s) and %d ring(s)\n",
		priv->config.pes, priv->config.rings);

	/*
	 * For EIP197's only set maximum number of TX commands to 2^5 = 32
	 * Skip for the EIP97 as it does not have this field.
	 */
	if (priv->flags & SAFEXCEL_HW_EIP197) {
		val = readl(EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
		val |= EIP197_MST_CTRL_TX_MAX_CMD(5);
		writel(val, EIP197_HIA_AIC(priv) + EIP197_HIA_MST_CTRL);
	}

	/* Configure wr/rd cache values */
	writel(EIP197_MST_CTRL_RD_CACHE(RD_CACHE_4BITS) |
	       EIP197_MST_CTRL_WD_CACHE(WR_CACHE_4BITS),
	       EIP197_HIA_GEN_CFG(priv) + EIP197_MST_CTRL);

	/* Interrupts reset */

	/* Disable all global interrupts */
	writel(0, EIP197_HIA_AIC_G(priv) + EIP197_HIA_AIC_G_ENABLE_CTRL);

	/* Clear any pending interrupt */
	writel(GENMASK(31, 0), EIP197_HIA_AIC_G(priv) + EIP197_HIA_AIC_G_ACK);

	/* Processing Engine configuration */
	for (pe = 0; pe < priv->config.pes; pe++) {
		/* Data Fetch Engine configuration */

		/* Reset all DFE threads */
		writel(EIP197_DxE_THR_CTRL_RESET_PE,
		       EIP197_HIA_DFE_THR(priv) + EIP197_HIA_DFE_THR_CTRL(pe));

		if (priv->flags & SAFEXCEL_HW_EIP197)
			/* Reset HIA input interface arbiter (EIP197 only) */
			writel(EIP197_HIA_RA_PE_CTRL_RESET,
			       EIP197_HIA_AIC(priv) + EIP197_HIA_RA_PE_CTRL(pe));

		/* DMA transfer size to use */
		val = EIP197_HIA_DFE_CFG_DIS_DEBUG;
		val |= EIP197_HIA_DxE_CFG_MIN_DATA_SIZE(6) |
		       EIP197_HIA_DxE_CFG_MAX_DATA_SIZE(9);
		val |= EIP197_HIA_DxE_CFG_MIN_CTRL_SIZE(6) |
		       EIP197_HIA_DxE_CFG_MAX_CTRL_SIZE(7);
		val |= EIP197_HIA_DxE_CFG_DATA_CACHE_CTRL(RD_CACHE_3BITS);
		val |= EIP197_HIA_DxE_CFG_CTRL_CACHE_CTRL(RD_CACHE_3BITS);
		writel(val, EIP197_HIA_DFE(priv) + EIP197_HIA_DFE_CFG(pe));

		/* Leave the DFE threads reset state */
		writel(0, EIP197_HIA_DFE_THR(priv) + EIP197_HIA_DFE_THR_CTRL(pe));

		/* Configure the processing engine thresholds */
		writel(EIP197_PE_IN_xBUF_THRES_MIN(6) |
		       EIP197_PE_IN_xBUF_THRES_MAX(9),
		       EIP197_PE(priv) + EIP197_PE_IN_DBUF_THRES(pe));
		writel(EIP197_PE_IN_xBUF_THRES_MIN(6) |
		       EIP197_PE_IN_xBUF_THRES_MAX(7),
		       EIP197_PE(priv) + EIP197_PE_IN_TBUF_THRES(pe));

		if (priv->flags & SAFEXCEL_HW_EIP197)
			/* enable HIA input interface arbiter and rings */
			writel(EIP197_HIA_RA_PE_CTRL_EN |
			       GENMASK(priv->config.rings - 1, 0),
			       EIP197_HIA_AIC(priv) + EIP197_HIA_RA_PE_CTRL(pe));

		/* Data Store Engine configuration */

		/* Reset all DSE threads */
		writel(EIP197_DxE_THR_CTRL_RESET_PE,
		       EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_CTRL(pe));

		/* Wait for all DSE threads to complete */
		while ((readl(EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_STAT(pe)) &
			GENMASK(15, 12)) != GENMASK(15, 12))
			;

		/* DMA transfer size to use */
		val = EIP197_HIA_DSE_CFG_DIS_DEBUG;
		val |= EIP197_HIA_DxE_CFG_MIN_DATA_SIZE(7) |
		       EIP197_HIA_DxE_CFG_MAX_DATA_SIZE(8);
		val |= EIP197_HIA_DxE_CFG_DATA_CACHE_CTRL(WR_CACHE_3BITS);
		val |= EIP197_HIA_DSE_CFG_ALWAYS_BUFFERABLE;
		/* FIXME: instability issues can occur for EIP97 but disabling
		 * it impacts performance.
		 */
		if (priv->flags & SAFEXCEL_HW_EIP197)
			val |= EIP197_HIA_DSE_CFG_EN_SINGLE_WR;
		writel(val, EIP197_HIA_DSE(priv) + EIP197_HIA_DSE_CFG(pe));

		/* Leave the DSE threads reset state */
		writel(0, EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_CTRL(pe));

		/* Configure the procesing engine thresholds */
		writel(EIP197_PE_OUT_DBUF_THRES_MIN(7) |
		       EIP197_PE_OUT_DBUF_THRES_MAX(8),
		       EIP197_PE(priv) + EIP197_PE_OUT_DBUF_THRES(pe));

		/* Processing Engine configuration */

		/* Token & context configuration */
		val = EIP197_PE_EIP96_TOKEN_CTRL_CTX_UPDATES |
		      EIP197_PE_EIP96_TOKEN_CTRL_NO_TOKEN_WAIT |
		      EIP197_PE_EIP96_TOKEN_CTRL_ENABLE_TIMEOUT;
		writel(val, EIP197_PE(priv) + EIP197_PE_EIP96_TOKEN_CTRL(pe));

		/* H/W capabilities selection: just enable everything */
		writel(EIP197_FUNCTION_ALL,
		       EIP197_PE(priv) + EIP197_PE_EIP96_FUNCTION_EN(pe));
		writel(EIP197_FUNCTION_ALL,
		       EIP197_PE(priv) + EIP197_PE_EIP96_FUNCTION2_EN(pe));
	}

	/* Command Descriptor Rings prepare */
	for (i = 0; i < priv->config.rings; i++) {
		/* Clear interrupts for this ring */
		writel(GENMASK(31, 0),
		       EIP197_HIA_AIC_R(priv) + EIP197_HIA_AIC_R_ENABLE_CLR(i));

		/* Disable external triggering */
		writel(0, EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_CFG);

		/* Clear the pending prepared counter */
		writel(EIP197_xDR_PREP_CLR_COUNT,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PREP_COUNT);

		/* Clear the pending processed counter */
		writel(EIP197_xDR_PROC_CLR_COUNT,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PROC_COUNT);

		writel(0,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PREP_PNTR);
		writel(0,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_PROC_PNTR);

		writel((EIP197_DEFAULT_RING_SIZE * priv->config.cd_offset) << 2,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_SIZE);
	}

	/* Result Descriptor Ring prepare */
	for (i = 0; i < priv->config.rings; i++) {
		/* Disable external triggering*/
		writel(0, EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_CFG);

		/* Clear the pending prepared counter */
		writel(EIP197_xDR_PREP_CLR_COUNT,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PREP_COUNT);

		/* Clear the pending processed counter */
		writel(EIP197_xDR_PROC_CLR_COUNT,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PROC_COUNT);

		writel(0,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PREP_PNTR);
		writel(0,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_PROC_PNTR);

		/* Ring size */
		writel((EIP197_DEFAULT_RING_SIZE * priv->config.rd_offset) << 2,
		       EIP197_HIA_RDR(priv, i) + EIP197_HIA_xDR_RING_SIZE);
	}

	for (pe = 0; pe < priv->config.pes; pe++) {
		/* Enable command descriptor rings */
		writel(EIP197_DxE_THR_CTRL_EN | GENMASK(priv->config.rings - 1, 0),
		       EIP197_HIA_DFE_THR(priv) + EIP197_HIA_DFE_THR_CTRL(pe));

		/* Enable result descriptor rings */
		writel(EIP197_DxE_THR_CTRL_EN | GENMASK(priv->config.rings - 1, 0),
		       EIP197_HIA_DSE_THR(priv) + EIP197_HIA_DSE_THR_CTRL(pe));
	}

	/* Clear any HIA interrupt */
	writel(GENMASK(30, 20), EIP197_HIA_AIC_G(priv) + EIP197_HIA_AIC_G_ACK);

	if (priv->flags & SAFEXCEL_HW_EIP197) {
		eip197_trc_cache_init(priv);
		priv->flags |= EIP197_TRC_CACHE;

		ret = eip197_load_firmwares(priv);
		if (ret)
			return ret;
	}

	safexcel_hw_setup_cdesc_rings(priv);
	safexcel_hw_setup_rdesc_rings(priv);

	return 0;
}