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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_SAMPLE_REGS_ABI_32 ; 
 int /*<<< orphan*/  PERF_SAMPLE_REGS_ABI_64 ; 

u64 perf_reg_abi(struct task_struct *task)
{
#if __riscv_xlen == 64
	return PERF_SAMPLE_REGS_ABI_64;
#else
	return PERF_SAMPLE_REGS_ABI_32;
#endif
}