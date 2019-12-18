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
typedef  int u64 ;

/* Variables and functions */
 int EINVAL ; 
 int PERF_REG_X86_RESERVED ; 
 int REG_NOSUPPORT ; 

int perf_reg_validate(u64 mask)
{
	if (!mask || (mask & (REG_NOSUPPORT | PERF_REG_X86_RESERVED)))
		return -EINVAL;

	return 0;
}