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
struct mtk_cqdma_pchan {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MTK_CQDMA_EN ; 
 int MTK_CQDMA_EN_BIT ; 
 int /*<<< orphan*/  MTK_CQDMA_TIMEOUT_POLL ; 
 int /*<<< orphan*/  MTK_CQDMA_USEC_POLL ; 
 int readl_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_cqdma_poll_engine_done(struct mtk_cqdma_pchan *pc, bool atomic)
{
	u32 status = 0;

	if (!atomic)
		return readl_poll_timeout(pc->base + MTK_CQDMA_EN,
					  status,
					  !(status & MTK_CQDMA_EN_BIT),
					  MTK_CQDMA_USEC_POLL,
					  MTK_CQDMA_TIMEOUT_POLL);

	return readl_poll_timeout_atomic(pc->base + MTK_CQDMA_EN,
					 status,
					 !(status & MTK_CQDMA_EN_BIT),
					 MTK_CQDMA_USEC_POLL,
					 MTK_CQDMA_TIMEOUT_POLL);
}