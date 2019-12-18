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
struct xgene_ahci_context {int /*<<< orphan*/  dev; scalar_t__ csr_diag; } ;

/* Variables and functions */
 scalar_t__ BLOCK_MEM_RDY ; 
 scalar_t__ CFG_MEM_RAM_SHUTDOWN ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int xgene_ahci_init_memram(struct xgene_ahci_context *ctx)
{
	dev_dbg(ctx->dev, "Release memory from shutdown\n");
	writel(0x0, ctx->csr_diag + CFG_MEM_RAM_SHUTDOWN);
	readl(ctx->csr_diag + CFG_MEM_RAM_SHUTDOWN); /* Force a barrier */
	msleep(1);	/* reset may take up to 1ms */
	if (readl(ctx->csr_diag + BLOCK_MEM_RDY) != 0xFFFFFFFF) {
		dev_err(ctx->dev, "failed to release memory from shutdown\n");
		return -ENODEV;
	}
	return 0;
}