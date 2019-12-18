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

/* Variables and functions */
 unsigned int TIMER10_IRQ_IDX ; 
 unsigned int TIMER1_IRQ_IDX ; 

__attribute__((used)) static inline unsigned int tegra_irq_idx_for_cpu(int cpu, bool tegra20)
{
	if (tegra20)
		return TIMER1_IRQ_IDX + cpu;

	return TIMER10_IRQ_IDX + cpu;
}