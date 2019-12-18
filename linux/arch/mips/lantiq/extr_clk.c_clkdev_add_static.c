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
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 TYPE_1__* cpu_clk_generic ; 

void clkdev_add_static(unsigned long cpu, unsigned long fpi,
			unsigned long io, unsigned long ppe)
{
	cpu_clk_generic[0].rate = cpu;
	cpu_clk_generic[1].rate = fpi;
	cpu_clk_generic[2].rate = io;
	cpu_clk_generic[3].rate = ppe;
}