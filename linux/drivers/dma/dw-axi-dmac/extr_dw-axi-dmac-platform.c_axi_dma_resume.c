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
struct axi_dma_chip {int /*<<< orphan*/  core_clk; int /*<<< orphan*/  cfgr_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  axi_dma_enable (struct axi_dma_chip*) ; 
 int /*<<< orphan*/  axi_dma_irq_enable (struct axi_dma_chip*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axi_dma_resume(struct axi_dma_chip *chip)
{
	int ret;

	ret = clk_prepare_enable(chip->cfgr_clk);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(chip->core_clk);
	if (ret < 0)
		return ret;

	axi_dma_enable(chip);
	axi_dma_irq_enable(chip);

	return 0;
}