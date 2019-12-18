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

int sun3_map_test(unsigned long addr, char *val)
{
	int ret = 0;

	__asm__ __volatile__
		(".globl _sun3_map_test_start\n"
		 "_sun3_map_test_start:\n"
		 "1: moveb (%2), (%0)\n"
		 "   moveq #1, %1\n"
		 "2:\n"
		 ".section .fixup,\"ax\"\n"
		 ".even\n"
		 "3: moveq #0, %1\n"
		 "   jmp 2b\n"
		 ".previous\n"
		 ".section __ex_table,\"a\"\n"
		 ".align 4\n"
		 ".long 1b,3b\n"
		 ".previous\n"
		 ".globl _sun3_map_test_end\n"
		 "_sun3_map_test_end:\n"
		 : "=a"(val), "=r"(ret)
		 : "a"(addr));

	return ret;
}