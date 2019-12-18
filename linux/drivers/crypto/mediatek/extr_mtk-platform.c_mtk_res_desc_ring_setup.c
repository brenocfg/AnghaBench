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
struct mtk_sys_cap {int /*<<< orphan*/  hia_opt; } ;
struct mtk_cryp {scalar_t__ base; TYPE_1__** ring; } ;
struct TYPE_2__ {int res_dma; } ;

/* Variables and functions */
 int MTK_CNT_RST ; 
 int MTK_DESC_FETCH_SIZE (int) ; 
 int MTK_DESC_FETCH_THRESH (int) ; 
 int MTK_DESC_OFF ; 
 int MTK_DESC_OFFSET (int) ; 
 int MTK_DESC_OVL_IRQ_EN ; 
 int MTK_DESC_RING_SZ ; 
 int MTK_DESC_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_DESC_SZ ; 
 int MTK_RDR_PROC_MODE ; 
 int MTK_RDR_PROC_THRESH ; 
 int MTK_RDR_STAT_CLR ; 
 int MTK_RES_FIFO_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ RDR_BASE_ADDR_HI (int) ; 
 scalar_t__ RDR_BASE_ADDR_LO (int) ; 
 scalar_t__ RDR_CFG (int) ; 
 scalar_t__ RDR_DESC_SIZE (int) ; 
 scalar_t__ RDR_DMA_CFG (int) ; 
 scalar_t__ RDR_PREP_COUNT (int) ; 
 scalar_t__ RDR_PREP_PNTR (int) ; 
 scalar_t__ RDR_PROC_COUNT (int) ; 
 scalar_t__ RDR_PROC_PNTR (int) ; 
 scalar_t__ RDR_RING_SIZE (int) ; 
 scalar_t__ RDR_STAT (int) ; 
 scalar_t__ RDR_THRESH (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_res_desc_ring_setup(struct mtk_cryp *cryp,
				    int i, struct mtk_sys_cap *cap)
{
	u32 rndup = 2;
	u32 count = ((1 << MTK_RES_FIFO_SIZE(cap->hia_opt)) / rndup) - 1;

	/* Temporarily disable external triggering */
	writel(0, cryp->base + RDR_CFG(i));

	/* Clear RDR count */
	writel(MTK_CNT_RST, cryp->base + RDR_PREP_COUNT(i));
	writel(MTK_CNT_RST, cryp->base + RDR_PROC_COUNT(i));

	writel(0, cryp->base + RDR_PREP_PNTR(i));
	writel(0, cryp->base + RDR_PROC_PNTR(i));
	writel(0, cryp->base + RDR_DMA_CFG(i));

	/* Configure RDR host address space */
	writel(0, cryp->base + RDR_BASE_ADDR_HI(i));
	writel(cryp->ring[i]->res_dma, cryp->base + RDR_BASE_ADDR_LO(i));

	writel(MTK_DESC_RING_SZ, cryp->base + RDR_RING_SIZE(i));
	writel(MTK_RDR_STAT_CLR, cryp->base + RDR_STAT(i));

	/*
	 * RDR manager generates update interrupts on a per-completed-packet,
	 * and the rd_proc_thresh_irq interrupt is fired when proc_pkt_count
	 * for the RDR exceeds the number of packets.
	 */
	writel(MTK_RDR_PROC_THRESH | MTK_RDR_PROC_MODE,
	       cryp->base + RDR_THRESH(i));

	/*
	 * Configure a threshold and time-out value for the processed
	 * result descriptors (or complete packets) that are written to
	 * the RDR.
	 */
	writel(MTK_DESC_SIZE(MTK_DESC_SZ) | MTK_DESC_OFFSET(MTK_DESC_OFF),
	       cryp->base + RDR_DESC_SIZE(i));

	/*
	 * Configure HIA fetch size and fetch threshold that are used to
	 * fetch blocks of multiple descriptors.
	 */
	writel(MTK_DESC_FETCH_SIZE(count * MTK_DESC_OFF) |
	       MTK_DESC_FETCH_THRESH(count * rndup) |
	       MTK_DESC_OVL_IRQ_EN,
		   cryp->base + RDR_CFG(i));
}