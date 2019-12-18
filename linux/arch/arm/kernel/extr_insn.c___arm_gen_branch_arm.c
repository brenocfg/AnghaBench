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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long
__arm_gen_branch_arm(unsigned long pc, unsigned long addr, bool link)
{
	unsigned long opcode = 0xea000000;
	long offset;

	if (link)
		opcode |= 1 << 24;

	offset = (long)addr - (long)(pc + 8);
	if (unlikely(offset < -33554432 || offset > 33554428)) {
		WARN_ON_ONCE(1);
		return 0;
	}

	offset = (offset >> 2) & 0x00ffffff;

	return opcode | offset;
}