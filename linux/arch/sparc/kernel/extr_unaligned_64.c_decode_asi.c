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
struct pt_regs {int tstate; } ;

/* Variables and functions */
 int ASI_P ; 

__attribute__((used)) static inline int decode_asi(unsigned int insn, struct pt_regs *regs)
{
	if (insn & 0x800000) {
		if (insn & 0x2000)
			return (unsigned char)(regs->tstate >> 24);	/* %asi */
		else
			return (unsigned char)(insn >> 5);		/* imm_asi */
	} else
		return ASI_P;
}