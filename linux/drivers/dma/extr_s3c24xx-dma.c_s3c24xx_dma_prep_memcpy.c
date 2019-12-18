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
struct s3c24xx_txd {int width; int disrcc; int didstc; int dcon; int /*<<< orphan*/  vd; int /*<<< orphan*/  dsg_list; } ;
struct s3c24xx_sg {int src_addr; int dst_addr; size_t len; int /*<<< orphan*/  node; } ;
struct s3c24xx_dma_engine {TYPE_1__* pdev; } ;
struct s3c24xx_dma_chan {int /*<<< orphan*/  vc; int /*<<< orphan*/  name; struct s3c24xx_dma_engine* host; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int S3C24XX_DCON_DEMAND ; 
 int S3C24XX_DCON_SERV_WHOLE ; 
 int S3C24XX_DCON_SYNC_HCLK ; 
 size_t S3C24XX_DCON_TC_MASK ; 
 int S3C24XX_DIDSTC_INC_INCREMENT ; 
 int S3C24XX_DIDSTC_LOC_AHB ; 
 int S3C24XX_DISRCC_INC_INCREMENT ; 
 int S3C24XX_DISRCC_LOC_AHB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 struct s3c24xx_sg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3c24xx_dma_free_txd (struct s3c24xx_txd*) ; 
 struct s3c24xx_txd* s3c24xx_dma_get_txd () ; 
 struct s3c24xx_dma_chan* to_s3c24xx_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *s3c24xx_dma_prep_memcpy(
		struct dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		size_t len, unsigned long flags)
{
	struct s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(chan);
	struct s3c24xx_dma_engine *s3cdma = s3cchan->host;
	struct s3c24xx_txd *txd;
	struct s3c24xx_sg *dsg;
	int src_mod, dest_mod;

	dev_dbg(&s3cdma->pdev->dev, "prepare memcpy of %zu bytes from %s\n",
			len, s3cchan->name);

	if ((len & S3C24XX_DCON_TC_MASK) != len) {
		dev_err(&s3cdma->pdev->dev, "memcpy size %zu to large\n", len);
		return NULL;
	}

	txd = s3c24xx_dma_get_txd();
	if (!txd)
		return NULL;

	dsg = kzalloc(sizeof(*dsg), GFP_NOWAIT);
	if (!dsg) {
		s3c24xx_dma_free_txd(txd);
		return NULL;
	}
	list_add_tail(&dsg->node, &txd->dsg_list);

	dsg->src_addr = src;
	dsg->dst_addr = dest;
	dsg->len = len;

	/*
	 * Determine a suitable transfer width.
	 * The DMA controller cannot fetch/store information which is not
	 * naturally aligned on the bus, i.e., a 4 byte fetch must start at
	 * an address divisible by 4 - more generally addr % width must be 0.
	 */
	src_mod = src % 4;
	dest_mod = dest % 4;
	switch (len % 4) {
	case 0:
		txd->width = (src_mod == 0 && dest_mod == 0) ? 4 : 1;
		break;
	case 2:
		txd->width = ((src_mod == 2 || src_mod == 0) &&
			      (dest_mod == 2 || dest_mod == 0)) ? 2 : 1;
		break;
	default:
		txd->width = 1;
		break;
	}

	txd->disrcc = S3C24XX_DISRCC_LOC_AHB | S3C24XX_DISRCC_INC_INCREMENT;
	txd->didstc = S3C24XX_DIDSTC_LOC_AHB | S3C24XX_DIDSTC_INC_INCREMENT;
	txd->dcon |= S3C24XX_DCON_DEMAND | S3C24XX_DCON_SYNC_HCLK |
		     S3C24XX_DCON_SERV_WHOLE;

	return vchan_tx_prep(&s3cchan->vc, &txd->vd, flags);
}