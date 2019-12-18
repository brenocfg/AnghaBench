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
struct mtk_cqdma_vdesc {int src; int dest; int len; int /*<<< orphan*/  ch; } ;
struct mtk_cqdma_pchan {int dummy; } ;

/* Variables and functions */
 int MTK_CQDMA_ADDR2_SHFIT ; 
 int MTK_CQDMA_ADDR_LIMIT ; 
 int /*<<< orphan*/  MTK_CQDMA_DST ; 
 int /*<<< orphan*/  MTK_CQDMA_DST2 ; 
 int /*<<< orphan*/  MTK_CQDMA_EN ; 
 int MTK_CQDMA_EN_BIT ; 
 int /*<<< orphan*/  MTK_CQDMA_LEN1 ; 
 int /*<<< orphan*/  MTK_CQDMA_RESET ; 
 int /*<<< orphan*/  MTK_CQDMA_SRC ; 
 int /*<<< orphan*/  MTK_CQDMA_SRC2 ; 
 int MTK_CQDMA_WARM_RST_BIT ; 
 int /*<<< orphan*/  cqdma2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mtk_cqdma_poll_engine_done (struct mtk_cqdma_pchan*,int) ; 
 int /*<<< orphan*/  mtk_dma_set (struct mtk_cqdma_pchan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_cqdma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_cqdma_start(struct mtk_cqdma_pchan *pc,
			    struct mtk_cqdma_vdesc *cvd)
{
	/* wait for the previous transaction done */
	if (mtk_cqdma_poll_engine_done(pc, true) < 0)
		dev_err(cqdma2dev(to_cqdma_dev(cvd->ch)), "cqdma wait transaction timeout\n");

	/* warm reset the dma engine for the new transaction */
	mtk_dma_set(pc, MTK_CQDMA_RESET, MTK_CQDMA_WARM_RST_BIT);
	if (mtk_cqdma_poll_engine_done(pc, true) < 0)
		dev_err(cqdma2dev(to_cqdma_dev(cvd->ch)), "cqdma warm reset timeout\n");

	/* setup the source */
	mtk_dma_set(pc, MTK_CQDMA_SRC, cvd->src & MTK_CQDMA_ADDR_LIMIT);
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	mtk_dma_set(pc, MTK_CQDMA_SRC2, cvd->src >> MTK_CQDMA_ADDR2_SHFIT);
#else
	mtk_dma_set(pc, MTK_CQDMA_SRC2, 0);
#endif

	/* setup the destination */
	mtk_dma_set(pc, MTK_CQDMA_DST, cvd->dest & MTK_CQDMA_ADDR_LIMIT);
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	mtk_dma_set(pc, MTK_CQDMA_DST2, cvd->dest >> MTK_CQDMA_ADDR2_SHFIT);
#else
	mtk_dma_set(pc, MTK_CQDMA_DST2, 0);
#endif

	/* setup the length */
	mtk_dma_set(pc, MTK_CQDMA_LEN1, cvd->len);

	/* start dma engine */
	mtk_dma_set(pc, MTK_CQDMA_EN, MTK_CQDMA_EN_BIT);
}