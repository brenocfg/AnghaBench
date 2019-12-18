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
typedef  scalar_t__ u32 ;
struct uniphier_mdmac_device {scalar_t__ reg_base; } ;
struct uniphier_mdmac_desc {size_t sg_cur; scalar_t__ dir; struct scatterlist* sgl; } ;
struct uniphier_mdmac_chan {int /*<<< orphan*/  chan_id; scalar_t__ reg_ch_base; struct uniphier_mdmac_device* mdev; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ UNIPHIER_MDMAC_CH_DEST_ADDR ; 
 scalar_t__ UNIPHIER_MDMAC_CH_DEST_MODE ; 
 scalar_t__ UNIPHIER_MDMAC_CH_IRQ_EN ; 
 scalar_t__ UNIPHIER_MDMAC_CH_IRQ_REQ ; 
 scalar_t__ UNIPHIER_MDMAC_CH_IRQ__DONE ; 
 scalar_t__ UNIPHIER_MDMAC_CH_MODE__ADDR_FIXED ; 
 scalar_t__ UNIPHIER_MDMAC_CH_MODE__ADDR_INC ; 
 scalar_t__ UNIPHIER_MDMAC_CH_SIZE ; 
 scalar_t__ UNIPHIER_MDMAC_CH_SRC_ADDR ; 
 scalar_t__ UNIPHIER_MDMAC_CH_SRC_MODE ; 
 scalar_t__ UNIPHIER_MDMAC_CMD ; 
 scalar_t__ sg_dma_address (struct scatterlist*) ; 
 scalar_t__ sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void uniphier_mdmac_handle(struct uniphier_mdmac_chan *mc,
				  struct uniphier_mdmac_desc *md)
{
	struct uniphier_mdmac_device *mdev = mc->mdev;
	struct scatterlist *sg;
	u32 irq_flag = UNIPHIER_MDMAC_CH_IRQ__DONE;
	u32 src_mode, src_addr, dest_mode, dest_addr, chunk_size;

	sg = &md->sgl[md->sg_cur];

	if (md->dir == DMA_MEM_TO_DEV) {
		src_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_INC;
		src_addr = sg_dma_address(sg);
		dest_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_FIXED;
		dest_addr = 0;
	} else {
		src_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_FIXED;
		src_addr = 0;
		dest_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_INC;
		dest_addr = sg_dma_address(sg);
	}

	chunk_size = sg_dma_len(sg);

	writel(src_mode, mc->reg_ch_base + UNIPHIER_MDMAC_CH_SRC_MODE);
	writel(dest_mode, mc->reg_ch_base + UNIPHIER_MDMAC_CH_DEST_MODE);
	writel(src_addr, mc->reg_ch_base + UNIPHIER_MDMAC_CH_SRC_ADDR);
	writel(dest_addr, mc->reg_ch_base + UNIPHIER_MDMAC_CH_DEST_ADDR);
	writel(chunk_size, mc->reg_ch_base + UNIPHIER_MDMAC_CH_SIZE);

	/* write 1 to clear */
	writel(irq_flag, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ);

	writel(irq_flag, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_EN);

	writel(BIT(mc->chan_id), mdev->reg_base + UNIPHIER_MDMAC_CMD);
}