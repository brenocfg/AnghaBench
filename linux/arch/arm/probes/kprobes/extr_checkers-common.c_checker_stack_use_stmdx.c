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
struct decode_header {int dummy; } ;
struct arch_probes_insn {int stack_space; } ;
typedef  int probes_opcode_t ;
typedef  enum probes_insn { ____Placeholder_probes_insn } probes_insn ;

/* Variables and functions */
 int INSN_GOOD_NO_SLOT ; 
 int hweight32 (unsigned int) ; 

enum probes_insn checker_stack_use_stmdx(probes_opcode_t insn,
		struct arch_probes_insn *asi,
		const struct decode_header *h)
{
	unsigned int reglist = insn & 0xffff;
	int pbit = insn & (1 << 24);
	asi->stack_space = (hweight32(reglist) - (!pbit ? 1 : 0)) * 4;

	return INSN_GOOD_NO_SLOT;
}