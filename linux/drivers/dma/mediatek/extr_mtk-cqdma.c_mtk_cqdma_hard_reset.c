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
struct mtk_cqdma_pchan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_CQDMA_HARD_RST_BIT ; 
 int /*<<< orphan*/  MTK_CQDMA_RESET ; 
 int mtk_cqdma_poll_engine_done (struct mtk_cqdma_pchan*,int) ; 
 int /*<<< orphan*/  mtk_dma_clr (struct mtk_cqdma_pchan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dma_set (struct mtk_cqdma_pchan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_cqdma_hard_reset(struct mtk_cqdma_pchan *pc)
{
	mtk_dma_set(pc, MTK_CQDMA_RESET, MTK_CQDMA_HARD_RST_BIT);
	mtk_dma_clr(pc, MTK_CQDMA_RESET, MTK_CQDMA_HARD_RST_BIT);

	return mtk_cqdma_poll_engine_done(pc, true);
}