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
struct sprd_dma_dev {int /*<<< orphan*/  ashb_clk; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_dma_enable(struct sprd_dma_dev *sdev)
{
	int ret;

	ret = clk_prepare_enable(sdev->clk);
	if (ret)
		return ret;

	/*
	 * The ashb_clk is optional and only for AGCP DMA controller, so we
	 * need add one condition to check if the ashb_clk need enable.
	 */
	if (!IS_ERR(sdev->ashb_clk))
		ret = clk_prepare_enable(sdev->ashb_clk);

	return ret;
}