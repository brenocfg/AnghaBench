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
struct imx_rngc {scalar_t__ base; } ;

/* Variables and functions */
 int RNGC_CMD_CLR_ERR ; 
 int RNGC_CMD_CLR_INT ; 
 scalar_t__ RNGC_COMMAND ; 
 scalar_t__ RNGC_CONTROL ; 
 int RNGC_CTRL_MASK_DONE ; 
 int RNGC_CTRL_MASK_ERROR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void imx_rngc_irq_mask_clear(struct imx_rngc *rngc)
{
	u32 ctrl, cmd;

	/* mask interrupts */
	ctrl = readl(rngc->base + RNGC_CONTROL);
	ctrl |= RNGC_CTRL_MASK_DONE | RNGC_CTRL_MASK_ERROR;
	writel(ctrl, rngc->base + RNGC_CONTROL);

	/*
	 * CLR_INT clears the interrupt only if there's no error
	 * CLR_ERR clear the interrupt and the error register if there
	 * is an error
	 */
	cmd = readl(rngc->base + RNGC_COMMAND);
	cmd |= RNGC_CMD_CLR_INT | RNGC_CMD_CLR_ERR;
	writel(cmd, rngc->base + RNGC_COMMAND);
}