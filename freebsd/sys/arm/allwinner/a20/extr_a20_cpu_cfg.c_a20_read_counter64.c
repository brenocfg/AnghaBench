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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int CNT64_RL_EN ; 
 int /*<<< orphan*/  OSC24M_CNT64_CTRL_REG ; 
 int /*<<< orphan*/  OSC24M_CNT64_HIGH_REG ; 
 int /*<<< orphan*/  OSC24M_CNT64_LOW_REG ; 
 int /*<<< orphan*/  a20_cpu_cfg_sc ; 
 int cpu_cfg_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_cfg_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

uint64_t
a20_read_counter64(void)
{
	uint32_t lo, hi;

	/* Latch counter, wait for it to be ready to read. */
	cpu_cfg_write_4(a20_cpu_cfg_sc, OSC24M_CNT64_CTRL_REG, CNT64_RL_EN);
	while (cpu_cfg_read_4(a20_cpu_cfg_sc, OSC24M_CNT64_CTRL_REG) & CNT64_RL_EN)
		continue;

	hi = cpu_cfg_read_4(a20_cpu_cfg_sc, OSC24M_CNT64_HIGH_REG);
	lo = cpu_cfg_read_4(a20_cpu_cfg_sc, OSC24M_CNT64_LOW_REG);

	return (((uint64_t)hi << 32) | lo);
}