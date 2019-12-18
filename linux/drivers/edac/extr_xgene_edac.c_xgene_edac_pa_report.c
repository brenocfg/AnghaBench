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
struct xgene_edac_dev_ctx {scalar_t__ dev_csr; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  dev; struct xgene_edac_dev_ctx* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRADDRH_RD (int) ; 
 scalar_t__ IOBAXIS0TRANSERRINTSTS ; 
 scalar_t__ IOBAXIS0TRANSERRREQINFOH ; 
 scalar_t__ IOBAXIS0TRANSERRREQINFOL ; 
 int IOBAXIS0_M_ILLEGAL_ACCESS_MASK ; 
 scalar_t__ IOBAXIS1TRANSERRINTSTS ; 
 scalar_t__ IOBAXIS1TRANSERRREQINFOH ; 
 scalar_t__ IOBAXIS1TRANSERRREQINFOL ; 
 scalar_t__ IOBPATRANSERRINTSTS ; 
 int IOBPA_M_RDATA_CORRUPT_MASK ; 
 int IOBPA_M_REQIDRAM_CORRUPT_MASK ; 
 int IOBPA_M_TRANS_CORRUPT_MASK ; 
 int IOBPA_M_WDATA_CORRUPT_MASK ; 
 int IOBPA_RDATA_CORRUPT_MASK ; 
 int IOBPA_REQIDRAM_CORRUPT_MASK ; 
 int IOBPA_TRANS_CORRUPT_MASK ; 
 int IOBPA_WDATA_CORRUPT_MASK ; 
 scalar_t__ REQTYPE_RD (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void xgene_edac_pa_report(struct edac_device_ctl_info *edac_dev)
{
	struct xgene_edac_dev_ctx *ctx = edac_dev->pvt_info;
	u32 err_addr_lo;
	u32 err_addr_hi;
	u32 reg;

	/* IOB Processing agent transaction error interrupt */
	reg = readl(ctx->dev_csr + IOBPATRANSERRINTSTS);
	if (!reg)
		goto chk_iob_axi0;
	dev_err(edac_dev->dev, "IOB processing agent (PA) transaction error\n");
	if (reg & IOBPA_RDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA read data RAM error\n");
	if (reg & IOBPA_M_RDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB PA read data RAM error\n");
	if (reg & IOBPA_WDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA write data RAM error\n");
	if (reg & IOBPA_M_WDATA_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB PA write data RAM error\n");
	if (reg & IOBPA_TRANS_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA transaction error\n");
	if (reg & IOBPA_M_TRANS_CORRUPT_MASK)
		dev_err(edac_dev->dev, "Multiple IOB PA transaction error\n");
	if (reg & IOBPA_REQIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev, "IOB PA transaction ID RAM error\n");
	if (reg & IOBPA_M_REQIDRAM_CORRUPT_MASK)
		dev_err(edac_dev->dev,
			"Multiple IOB PA transaction ID RAM error\n");
	writel(reg, ctx->dev_csr + IOBPATRANSERRINTSTS);

chk_iob_axi0:
	/* IOB AXI0 Error */
	reg = readl(ctx->dev_csr + IOBAXIS0TRANSERRINTSTS);
	if (!reg)
		goto chk_iob_axi1;
	err_addr_lo = readl(ctx->dev_csr + IOBAXIS0TRANSERRREQINFOL);
	err_addr_hi = readl(ctx->dev_csr + IOBAXIS0TRANSERRREQINFOH);
	dev_err(edac_dev->dev,
		"%sAXI slave 0 illegal %s access @ 0x%02X.%08X (0x%08X)\n",
		reg & IOBAXIS0_M_ILLEGAL_ACCESS_MASK ? "Multiple " : "",
		REQTYPE_RD(err_addr_hi) ? "read" : "write",
		ERRADDRH_RD(err_addr_hi), err_addr_lo, err_addr_hi);
	writel(reg, ctx->dev_csr + IOBAXIS0TRANSERRINTSTS);

chk_iob_axi1:
	/* IOB AXI1 Error */
	reg = readl(ctx->dev_csr + IOBAXIS1TRANSERRINTSTS);
	if (!reg)
		return;
	err_addr_lo = readl(ctx->dev_csr + IOBAXIS1TRANSERRREQINFOL);
	err_addr_hi = readl(ctx->dev_csr + IOBAXIS1TRANSERRREQINFOH);
	dev_err(edac_dev->dev,
		"%sAXI slave 1 illegal %s access @ 0x%02X.%08X (0x%08X)\n",
		reg & IOBAXIS0_M_ILLEGAL_ACCESS_MASK ? "Multiple " : "",
		REQTYPE_RD(err_addr_hi) ? "read" : "write",
		ERRADDRH_RD(err_addr_hi), err_addr_lo, err_addr_hi);
	writel(reg, ctx->dev_csr + IOBAXIS1TRANSERRINTSTS);
}