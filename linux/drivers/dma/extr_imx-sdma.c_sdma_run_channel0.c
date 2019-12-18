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
struct sdma_engine {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SDMA_H_CONFIG ; 
 int SDMA_H_CONFIG_CSM ; 
 scalar_t__ SDMA_H_STATSTOP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int readl_relaxed_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  sdma_enable_channel (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int sdma_run_channel0(struct sdma_engine *sdma)
{
	int ret;
	u32 reg;

	sdma_enable_channel(sdma, 0);

	ret = readl_relaxed_poll_timeout_atomic(sdma->regs + SDMA_H_STATSTOP,
						reg, !(reg & 1), 1, 500);
	if (ret)
		dev_err(sdma->dev, "Timeout waiting for CH0 ready\n");

	/* Set bits of CONFIG register with dynamic context switching */
	reg = readl(sdma->regs + SDMA_H_CONFIG);
	if ((reg & SDMA_H_CONFIG_CSM) == 0) {
		reg |= SDMA_H_CONFIG_CSM;
		writel_relaxed(reg, sdma->regs + SDMA_H_CONFIG);
	}

	return ret;
}