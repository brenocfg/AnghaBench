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
struct pt_regs {unsigned long ipc; } ;
struct fpu_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ NDS32Insn_OPCODE (unsigned long) ; 
 int NDS32Insn_OPCODE_COP0 (unsigned long) ; 
 int SIGBUS ; 
 int SIGILL ; 
 scalar_t__ __get_user (char,unsigned char*) ; 
 unsigned long be32_to_cpu (unsigned long) ; 
 scalar_t__ cop0_op ; 
#define  fd1_op 131 
#define  fd2_op 130 
 int fpu_emu (struct fpu_struct*,unsigned long) ; 
#define  fs1_op 129 
#define  fs2_op 128 

int do_fpuemu(struct pt_regs *regs, struct fpu_struct *fpu)
{
	unsigned long insn = 0, addr = regs->ipc;
	unsigned long emulpc, contpc;
	unsigned char *pc = (void *)&insn;
	char c;
	int i = 0, ret;

	for (i = 0; i < 4; i++) {
		if (__get_user(c, (unsigned char *)addr++))
			return SIGBUS;
		*pc++ = c;
	}

	insn = be32_to_cpu(insn);

	emulpc = regs->ipc;
	contpc = regs->ipc + 4;

	if (NDS32Insn_OPCODE(insn) != cop0_op)
		return SIGILL;

	switch (NDS32Insn_OPCODE_COP0(insn)) {
	case fs1_op:
	case fs2_op:
	case fd1_op:
	case fd2_op:
		{
			/* a real fpu computation instruction */
			ret = fpu_emu(fpu, insn);
			if (!ret)
				regs->ipc = contpc;
		}
		break;

	default:
		return SIGILL;
	}

	return ret;
}