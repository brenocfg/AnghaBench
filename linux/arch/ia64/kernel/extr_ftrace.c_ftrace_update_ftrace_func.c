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
struct fnptr {unsigned long ip; } ;
typedef  scalar_t__ ftrace_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 scalar_t__ ftrace_call ; 
 scalar_t__ ftrace_stub ; 
 int /*<<< orphan*/  ia64_patch_imm64 (unsigned long,unsigned long) ; 

int ftrace_update_ftrace_func(ftrace_func_t func)
{
	unsigned long ip;
	unsigned long addr = ((struct fnptr *)ftrace_call)->ip;

	if (func == ftrace_stub)
		return 0;
	ip = ((struct fnptr *)func)->ip;

	ia64_patch_imm64(addr + 2, ip);

	flush_icache_range(addr, addr + 16);
	return 0;
}