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
 int MIPS_PERFCTRL_M ; 
 int /*<<< orphan*/  cpu_has_perf ; 
 int read_c0_perfctrl0 () ; 
 int read_c0_perfctrl1 () ; 
 int read_c0_perfctrl2 () ; 

__attribute__((used)) static int __n_counters(void)
{
	if (!cpu_has_perf)
		return 0;
	if (!(read_c0_perfctrl0() & MIPS_PERFCTRL_M))
		return 1;
	if (!(read_c0_perfctrl1() & MIPS_PERFCTRL_M))
		return 2;
	if (!(read_c0_perfctrl2() & MIPS_PERFCTRL_M))
		return 3;

	return 4;
}