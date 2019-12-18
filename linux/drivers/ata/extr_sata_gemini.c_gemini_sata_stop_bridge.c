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
struct sata_gemini {int /*<<< orphan*/  sata1_pclk; int /*<<< orphan*/  sata0_pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 

void gemini_sata_stop_bridge(struct sata_gemini *sg, unsigned int bridge)
{
	if (bridge == 0)
		clk_disable(sg->sata0_pclk);
	else if (bridge == 1)
		clk_disable(sg->sata1_pclk);
}