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
struct axi_dma_chip {int /*<<< orphan*/  cfgr_clk; int /*<<< orphan*/  core_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  axi_dma_disable (struct axi_dma_chip*) ; 
 int /*<<< orphan*/  axi_dma_irq_disable (struct axi_dma_chip*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axi_dma_suspend(struct axi_dma_chip *chip)
{
	axi_dma_irq_disable(chip);
	axi_dma_disable(chip);

	clk_disable_unprepare(chip->core_clk);
	clk_disable_unprepare(chip->cfgr_clk);

	return 0;
}