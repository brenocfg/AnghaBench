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
 int /*<<< orphan*/  cpu_l2cache_drain_writebuf () ; 
 int /*<<< orphan*/  dsb () ; 

void
arm_irq_memory_barrier(uintptr_t irq)
{

	dsb();
	cpu_l2cache_drain_writebuf();
}