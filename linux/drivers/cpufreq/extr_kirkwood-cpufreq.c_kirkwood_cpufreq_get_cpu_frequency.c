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
struct TYPE_2__ {int /*<<< orphan*/  powersave_clk; } ;

/* Variables and functions */
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__ priv ; 

__attribute__((used)) static unsigned int kirkwood_cpufreq_get_cpu_frequency(unsigned int cpu)
{
	return clk_get_rate(priv.powersave_clk) / 1000;
}