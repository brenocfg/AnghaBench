#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tegra_adma {TYPE_1__* cdata; scalar_t__ base_addr; } ;
struct TYPE_2__ {scalar_t__ global_reg_offset; scalar_t__ global_int_clear; } ;

/* Variables and functions */
 scalar_t__ ADMA_GLOBAL_CMD ; 
 scalar_t__ ADMA_GLOBAL_SOFT_RESET ; 
 int /*<<< orphan*/  readl ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  tdma_write (struct tegra_adma*,scalar_t__,int) ; 

__attribute__((used)) static int tegra_adma_init(struct tegra_adma *tdma)
{
	u32 status;
	int ret;

	/* Clear any interrupts */
	tdma_write(tdma, tdma->cdata->global_int_clear, 0x1);

	/* Assert soft reset */
	tdma_write(tdma, ADMA_GLOBAL_SOFT_RESET, 0x1);

	/* Wait for reset to clear */
	ret = readx_poll_timeout(readl,
				 tdma->base_addr +
				 tdma->cdata->global_reg_offset +
				 ADMA_GLOBAL_SOFT_RESET,
				 status, status == 0, 20, 10000);
	if (ret)
		return ret;

	/* Enable global ADMA registers */
	tdma_write(tdma, ADMA_GLOBAL_CMD, 1);

	return 0;
}