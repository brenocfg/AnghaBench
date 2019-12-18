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
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct pl08x_txd {int /*<<< orphan*/  ccfg; int /*<<< orphan*/ * llis_va; TYPE_1__ vd; } ;
struct pl08x_phy_chan {scalar_t__ reg_config; scalar_t__ reg_control; scalar_t__ ftdmac020; int /*<<< orphan*/  id; } ;
struct pl08x_driver_data {scalar_t__ base; } ;
struct pl08x_dma_chan {struct pl08x_txd* at; int /*<<< orphan*/  vc; struct pl08x_phy_chan* phychan; struct pl08x_driver_data* host; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int FTDMAC020_CH_CFG_BUSY ; 
 int FTDMAC020_CH_CSR_EN ; 
 int PL080_CONFIG_ACTIVE ; 
 int PL080_CONFIG_ENABLE ; 
 scalar_t__ PL080_EN_CHAN ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ pl08x_phy_channel_busy (struct pl08x_phy_chan*) ; 
 int /*<<< orphan*/  pl08x_write_lli (struct pl08x_driver_data*,struct pl08x_phy_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct pl08x_txd* to_pl08x_txd (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void pl08x_start_next_txd(struct pl08x_dma_chan *plchan)
{
	struct pl08x_driver_data *pl08x = plchan->host;
	struct pl08x_phy_chan *phychan = plchan->phychan;
	struct virt_dma_desc *vd = vchan_next_desc(&plchan->vc);
	struct pl08x_txd *txd = to_pl08x_txd(&vd->tx);
	u32 val;

	list_del(&txd->vd.node);

	plchan->at = txd;

	/* Wait for channel inactive */
	while (pl08x_phy_channel_busy(phychan))
		cpu_relax();

	pl08x_write_lli(pl08x, phychan, &txd->llis_va[0], txd->ccfg);

	/* Enable the DMA channel */
	/* Do not access config register until channel shows as disabled */
	while (readl(pl08x->base + PL080_EN_CHAN) & BIT(phychan->id))
		cpu_relax();

	/* Do not access config register until channel shows as inactive */
	if (phychan->ftdmac020) {
		val = readl(phychan->reg_config);
		while (val & FTDMAC020_CH_CFG_BUSY)
			val = readl(phychan->reg_config);

		val = readl(phychan->reg_control);
		while (val & FTDMAC020_CH_CSR_EN)
			val = readl(phychan->reg_control);

		writel(val | FTDMAC020_CH_CSR_EN,
		       phychan->reg_control);
	} else {
		val = readl(phychan->reg_config);
		while ((val & PL080_CONFIG_ACTIVE) ||
		       (val & PL080_CONFIG_ENABLE))
			val = readl(phychan->reg_config);

		writel(val | PL080_CONFIG_ENABLE, phychan->reg_config);
	}
}