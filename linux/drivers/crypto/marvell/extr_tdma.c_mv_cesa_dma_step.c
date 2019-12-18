#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* first; } ;
struct mv_cesa_req {TYPE_2__ chain; struct mv_cesa_engine* engine; } ;
struct mv_cesa_engine {scalar_t__ regs; } ;
struct TYPE_3__ {int cur_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CESA_SA_CFG ; 
 int CESA_SA_CFG_ACT_CH0_IDMA ; 
 int CESA_SA_CFG_CH0_W_IDMA ; 
 int CESA_SA_CFG_MULTI_PKT ; 
 int CESA_SA_CFG_PARA_DIS ; 
 scalar_t__ CESA_SA_CMD ; 
 int CESA_SA_CMD_EN_CESA_SA_ACCL0 ; 
 int /*<<< orphan*/  CESA_SA_INT_ACC0_IDMA_DONE ; 
 scalar_t__ CESA_TDMA_CONTROL ; 
 int CESA_TDMA_DST_BURST_128B ; 
 int CESA_TDMA_EN ; 
 scalar_t__ CESA_TDMA_NEXT_ADDR ; 
 int CESA_TDMA_NO_BYTE_SWAP ; 
 int CESA_TDMA_SRC_BURST_128B ; 
 int /*<<< orphan*/  mv_cesa_set_int_mask (struct mv_cesa_engine*,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void mv_cesa_dma_step(struct mv_cesa_req *dreq)
{
	struct mv_cesa_engine *engine = dreq->engine;

	writel_relaxed(0, engine->regs + CESA_SA_CFG);

	mv_cesa_set_int_mask(engine, CESA_SA_INT_ACC0_IDMA_DONE);
	writel_relaxed(CESA_TDMA_DST_BURST_128B | CESA_TDMA_SRC_BURST_128B |
		       CESA_TDMA_NO_BYTE_SWAP | CESA_TDMA_EN,
		       engine->regs + CESA_TDMA_CONTROL);

	writel_relaxed(CESA_SA_CFG_ACT_CH0_IDMA | CESA_SA_CFG_MULTI_PKT |
		       CESA_SA_CFG_CH0_W_IDMA | CESA_SA_CFG_PARA_DIS,
		       engine->regs + CESA_SA_CFG);
	writel_relaxed(dreq->chain.first->cur_dma,
		       engine->regs + CESA_TDMA_NEXT_ADDR);
	BUG_ON(readl(engine->regs + CESA_SA_CMD) &
	       CESA_SA_CMD_EN_CESA_SA_ACCL0);
	writel(CESA_SA_CMD_EN_CESA_SA_ACCL0, engine->regs + CESA_SA_CMD);
}