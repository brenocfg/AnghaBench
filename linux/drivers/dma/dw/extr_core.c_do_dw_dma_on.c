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
struct dw_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  DW_CFG_DMA_EN ; 
 int /*<<< orphan*/  dma_writel (struct dw_dma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void do_dw_dma_on(struct dw_dma *dw)
{
	dma_writel(dw, CFG, DW_CFG_DMA_EN);
}