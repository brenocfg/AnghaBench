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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static int ldb_asm(uint32_t addr, uint32_t *valp)
{
	uint32_t val;
	int err;

	asm volatile (
		"movi	%0, 0\n"
		"1:\n"
		"ldb	%1, (%2)\n"
		"br	3f\n"
		"2:\n"
		"movi	%0, 1\n"
		"br	3f\n"
		".section __ex_table,\"a\"\n"
		".align 2\n"
		".long	1b, 2b\n"
		".previous\n"
		"3:\n"
		: "=&r"(err), "=r"(val)
		: "r" (addr)
	);

	*valp = val;

	return err;
}