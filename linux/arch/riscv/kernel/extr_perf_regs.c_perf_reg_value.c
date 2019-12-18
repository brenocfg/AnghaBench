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
typedef  unsigned long u64 ;
typedef  scalar_t__ u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ PERF_REG_RISCV_MAX ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

u64 perf_reg_value(struct pt_regs *regs, int idx)
{
	if (WARN_ON_ONCE((u32)idx >= PERF_REG_RISCV_MAX))
		return 0;

	return ((unsigned long *)regs)[idx];
}