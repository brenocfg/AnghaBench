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
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 unsigned long __recover_optprobed_insn (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long __recover_probed_insn (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long recover_probed_instruction(kprobe_opcode_t *buf, unsigned long addr)
{
	unsigned long __addr;

	__addr = __recover_optprobed_insn(buf, addr);
	if (__addr != addr)
		return __addr;

	return __recover_probed_insn(buf, addr);
}