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
 int CPUID_STDEXT3_L1D_FLUSH ; 
 int cpu_stdext_feature3 ; 
 int /*<<< orphan*/ * flush_l1d_hw ; 
 int /*<<< orphan*/ * flush_l1d_sw_abi ; 
 int /*<<< orphan*/ * syscall_ret_l1d_flush ; 
 int syscall_ret_l1d_flush_mode ; 

void
amd64_syscall_ret_flush_l1d_recalc(void)
{
	bool l1d_hw;

	l1d_hw = (cpu_stdext_feature3 & CPUID_STDEXT3_L1D_FLUSH) != 0;
again:
	switch (syscall_ret_l1d_flush_mode) {
	case 0:
		syscall_ret_l1d_flush = NULL;
		break;
	case 1:
		syscall_ret_l1d_flush = l1d_hw ? flush_l1d_hw :
		    flush_l1d_sw_abi;
		break;
	case 2:
		syscall_ret_l1d_flush = l1d_hw ? flush_l1d_hw : NULL;
		break;
	case 3:
		syscall_ret_l1d_flush = flush_l1d_sw_abi;
		break;
	default:
		syscall_ret_l1d_flush_mode = 1;
		goto again;
	}
}