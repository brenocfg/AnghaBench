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
struct pt_regs {int /*<<< orphan*/ * gr; int /*<<< orphan*/  iir; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARISC_KGDB_COMPILED_BREAK_INSN ; 
 int /*<<< orphan*/  PSW_R ; 
 int /*<<< orphan*/  kgdb_arch_set_pc (struct pt_regs*,unsigned long) ; 
 int /*<<< orphan*/ * kgdb_contthread ; 
 int /*<<< orphan*/  kgdb_hex2long (char**,unsigned long*) ; 
 int kgdb_single_step ; 
 int /*<<< orphan*/  mtctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_instruction_queue (struct pt_regs*) ; 

int kgdb_arch_handle_exception(int trap, int signo,
		int err_code, char *inbuf, char *outbuf,
		struct pt_regs *regs)
{
	unsigned long addr;
	char *p = inbuf + 1;

	switch (inbuf[0]) {
	case 'D':
	case 'c':
	case 'k':
		kgdb_contthread = NULL;
		kgdb_single_step = 0;

		if (kgdb_hex2long(&p, &addr))
			kgdb_arch_set_pc(regs, addr);
		else if (trap == 9 && regs->iir ==
				PARISC_KGDB_COMPILED_BREAK_INSN)
			step_instruction_queue(regs);
		return 0;
	case 's':
		kgdb_single_step = 1;
		if (kgdb_hex2long(&p, &addr)) {
			kgdb_arch_set_pc(regs, addr);
		} else if (trap == 9 && regs->iir ==
				PARISC_KGDB_COMPILED_BREAK_INSN) {
			step_instruction_queue(regs);
			mtctl(-1, 0);
		} else {
			mtctl(0, 0);
		}
		regs->gr[0] |= PSW_R;
		return 0;

	}
	return -1;
}