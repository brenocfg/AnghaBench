#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ring_size; int /*<<< orphan*/  ring_offset; } ;
union ce_ring_size {int w; TYPE_1__ bf; } ;
union ce_ring_control {int w; } ;
struct TYPE_8__ {int bo_sgpd_en; int bo_sa_en; int bo_pd_en; int dynamic_sa_en; int reset_sg; int reset_pdr; int reset_pe; int pe_mode; scalar_t__ bo_td_en; scalar_t__ bo_data_en; } ;
union ce_pe_dma_cfg {int w; TYPE_4__ bf; } ;
struct TYPE_6__ {int /*<<< orphan*/  gdr_size; int /*<<< orphan*/  sdr_size; } ;
union ce_part_ring_size {int w; TYPE_2__ bf; } ;
struct TYPE_7__ {int /*<<< orphan*/  input_threshold; int /*<<< orphan*/  output_threshold; } ;
union ce_io_threshold {int w; TYPE_3__ bf; } ;
typedef  int u32 ;
struct crypto4xx_device {int pdr_pa; int gdr_pa; int sdr_pa; scalar_t__ ce_base; scalar_t__ is_revb; } ;
typedef  int /*<<< orphan*/  rand_num ;

/* Variables and functions */
 scalar_t__ CRYPTO4XX_BYTE_ORDER_CFG ; 
 scalar_t__ CRYPTO4XX_DEVICE_CTRL ; 
 scalar_t__ CRYPTO4XX_GATH_RING_BASE ; 
 scalar_t__ CRYPTO4XX_GATH_RING_BASE_UADDR ; 
 scalar_t__ CRYPTO4XX_INT_CFG ; 
 scalar_t__ CRYPTO4XX_INT_CLR ; 
 scalar_t__ CRYPTO4XX_INT_DESCR_CNT ; 
 scalar_t__ CRYPTO4XX_INT_EN ; 
 scalar_t__ CRYPTO4XX_INT_TIMEOUT_CNT ; 
 scalar_t__ CRYPTO4XX_IO_THRESHOLD ; 
 scalar_t__ CRYPTO4XX_PART_RING_CFG ; 
 scalar_t__ CRYPTO4XX_PART_RING_SIZE ; 
 scalar_t__ CRYPTO4XX_PDR_BASE ; 
 scalar_t__ CRYPTO4XX_PDR_BASE_UADDR ; 
 scalar_t__ CRYPTO4XX_PE_DMA_CFG ; 
 scalar_t__ CRYPTO4XX_PKT_DEST_UADDR ; 
 scalar_t__ CRYPTO4XX_PKT_SRC_UADDR ; 
 scalar_t__ CRYPTO4XX_PRNG_CTRL ; 
 scalar_t__ CRYPTO4XX_PRNG_SEED_H ; 
 scalar_t__ CRYPTO4XX_PRNG_SEED_L ; 
 scalar_t__ CRYPTO4XX_RDR_BASE ; 
 scalar_t__ CRYPTO4XX_RDR_BASE_UADDR ; 
 scalar_t__ CRYPTO4XX_RING_CTRL ; 
 scalar_t__ CRYPTO4XX_RING_SIZE ; 
 scalar_t__ CRYPTO4XX_SA_UADDR ; 
 scalar_t__ CRYPTO4XX_SCAT_RING_BASE ; 
 scalar_t__ CRYPTO4XX_SCAT_RING_BASE_UADDR ; 
 int PPC4XX_BYTE_ORDER ; 
 int PPC4XX_DC_3DES_EN ; 
 int /*<<< orphan*/  PPC4XX_GDR_SIZE ; 
 int /*<<< orphan*/  PPC4XX_INPUT_THRESHOLD ; 
 int PPC4XX_INTERRUPT_CLR ; 
 int PPC4XX_INT_CFG ; 
 int PPC4XX_INT_DESCR_CNT ; 
 int PPC4XX_INT_TIMEOUT_CNT_REVB ; 
 int /*<<< orphan*/  PPC4XX_NUM_PD ; 
 int /*<<< orphan*/  PPC4XX_OUTPUT_THRESHOLD ; 
 int PPC4XX_PD_DONE_INT ; 
 int /*<<< orphan*/  PPC4XX_PD_SIZE ; 
 int PPC4XX_PRNG_CTRL_AUTO_EN ; 
 int /*<<< orphan*/  PPC4XX_SDR_SIZE ; 
 int PPC4XX_SD_BUFFER_SIZE ; 
 int PPC4XX_TMO_ERR_INT ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void crypto4xx_hw_init(struct crypto4xx_device *dev)
{
	union ce_ring_size ring_size;
	union ce_ring_control ring_ctrl;
	union ce_part_ring_size part_ring_size;
	union ce_io_threshold io_threshold;
	u32 rand_num;
	union ce_pe_dma_cfg pe_dma_cfg;
	u32 device_ctrl;

	writel(PPC4XX_BYTE_ORDER, dev->ce_base + CRYPTO4XX_BYTE_ORDER_CFG);
	/* setup pe dma, include reset sg, pdr and pe, then release reset */
	pe_dma_cfg.w = 0;
	pe_dma_cfg.bf.bo_sgpd_en = 1;
	pe_dma_cfg.bf.bo_data_en = 0;
	pe_dma_cfg.bf.bo_sa_en = 1;
	pe_dma_cfg.bf.bo_pd_en = 1;
	pe_dma_cfg.bf.dynamic_sa_en = 1;
	pe_dma_cfg.bf.reset_sg = 1;
	pe_dma_cfg.bf.reset_pdr = 1;
	pe_dma_cfg.bf.reset_pe = 1;
	writel(pe_dma_cfg.w, dev->ce_base + CRYPTO4XX_PE_DMA_CFG);
	/* un reset pe,sg and pdr */
	pe_dma_cfg.bf.pe_mode = 0;
	pe_dma_cfg.bf.reset_sg = 0;
	pe_dma_cfg.bf.reset_pdr = 0;
	pe_dma_cfg.bf.reset_pe = 0;
	pe_dma_cfg.bf.bo_td_en = 0;
	writel(pe_dma_cfg.w, dev->ce_base + CRYPTO4XX_PE_DMA_CFG);
	writel(dev->pdr_pa, dev->ce_base + CRYPTO4XX_PDR_BASE);
	writel(dev->pdr_pa, dev->ce_base + CRYPTO4XX_RDR_BASE);
	writel(PPC4XX_PRNG_CTRL_AUTO_EN, dev->ce_base + CRYPTO4XX_PRNG_CTRL);
	get_random_bytes(&rand_num, sizeof(rand_num));
	writel(rand_num, dev->ce_base + CRYPTO4XX_PRNG_SEED_L);
	get_random_bytes(&rand_num, sizeof(rand_num));
	writel(rand_num, dev->ce_base + CRYPTO4XX_PRNG_SEED_H);
	ring_size.w = 0;
	ring_size.bf.ring_offset = PPC4XX_PD_SIZE;
	ring_size.bf.ring_size   = PPC4XX_NUM_PD;
	writel(ring_size.w, dev->ce_base + CRYPTO4XX_RING_SIZE);
	ring_ctrl.w = 0;
	writel(ring_ctrl.w, dev->ce_base + CRYPTO4XX_RING_CTRL);
	device_ctrl = readl(dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
	device_ctrl |= PPC4XX_DC_3DES_EN;
	writel(device_ctrl, dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
	writel(dev->gdr_pa, dev->ce_base + CRYPTO4XX_GATH_RING_BASE);
	writel(dev->sdr_pa, dev->ce_base + CRYPTO4XX_SCAT_RING_BASE);
	part_ring_size.w = 0;
	part_ring_size.bf.sdr_size = PPC4XX_SDR_SIZE;
	part_ring_size.bf.gdr_size = PPC4XX_GDR_SIZE;
	writel(part_ring_size.w, dev->ce_base + CRYPTO4XX_PART_RING_SIZE);
	writel(PPC4XX_SD_BUFFER_SIZE, dev->ce_base + CRYPTO4XX_PART_RING_CFG);
	io_threshold.w = 0;
	io_threshold.bf.output_threshold = PPC4XX_OUTPUT_THRESHOLD;
	io_threshold.bf.input_threshold  = PPC4XX_INPUT_THRESHOLD;
	writel(io_threshold.w, dev->ce_base + CRYPTO4XX_IO_THRESHOLD);
	writel(0, dev->ce_base + CRYPTO4XX_PDR_BASE_UADDR);
	writel(0, dev->ce_base + CRYPTO4XX_RDR_BASE_UADDR);
	writel(0, dev->ce_base + CRYPTO4XX_PKT_SRC_UADDR);
	writel(0, dev->ce_base + CRYPTO4XX_PKT_DEST_UADDR);
	writel(0, dev->ce_base + CRYPTO4XX_SA_UADDR);
	writel(0, dev->ce_base + CRYPTO4XX_GATH_RING_BASE_UADDR);
	writel(0, dev->ce_base + CRYPTO4XX_SCAT_RING_BASE_UADDR);
	/* un reset pe,sg and pdr */
	pe_dma_cfg.bf.pe_mode = 1;
	pe_dma_cfg.bf.reset_sg = 0;
	pe_dma_cfg.bf.reset_pdr = 0;
	pe_dma_cfg.bf.reset_pe = 0;
	pe_dma_cfg.bf.bo_td_en = 0;
	writel(pe_dma_cfg.w, dev->ce_base + CRYPTO4XX_PE_DMA_CFG);
	/*clear all pending interrupt*/
	writel(PPC4XX_INTERRUPT_CLR, dev->ce_base + CRYPTO4XX_INT_CLR);
	writel(PPC4XX_INT_DESCR_CNT, dev->ce_base + CRYPTO4XX_INT_DESCR_CNT);
	writel(PPC4XX_INT_DESCR_CNT, dev->ce_base + CRYPTO4XX_INT_DESCR_CNT);
	writel(PPC4XX_INT_CFG, dev->ce_base + CRYPTO4XX_INT_CFG);
	if (dev->is_revb) {
		writel(PPC4XX_INT_TIMEOUT_CNT_REVB << 10,
		       dev->ce_base + CRYPTO4XX_INT_TIMEOUT_CNT);
		writel(PPC4XX_PD_DONE_INT | PPC4XX_TMO_ERR_INT,
		       dev->ce_base + CRYPTO4XX_INT_EN);
	} else {
		writel(PPC4XX_PD_DONE_INT, dev->ce_base + CRYPTO4XX_INT_EN);
	}
}