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
struct pt_regs {scalar_t__ pc; } ;
struct exception_info {char* member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 unsigned int BKPT_OPCODE ; 
 int /*<<< orphan*/  EXCEPT_TYPE_IXF ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAP_BRKPT ; 
 unsigned int __ffs (unsigned int) ; 
 int /*<<< orphan*/  ack_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_trap (struct exception_info*,struct pt_regs*) ; 
 unsigned int get_iexcept () ; 
 struct exception_info* iexcept_table ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  set_iexcept (unsigned int) ; 

__attribute__((used)) static int process_iexcept(struct pt_regs *regs)
{
	unsigned int iexcept_report = get_iexcept();
	unsigned int iexcept_num;

	ack_exception(EXCEPT_TYPE_IXF);

	pr_err("IEXCEPT: PC[0x%lx]\n", regs->pc);

	while (iexcept_report) {
		iexcept_num = __ffs(iexcept_report);
		iexcept_report &= ~(1 << iexcept_num);
		set_iexcept(iexcept_report);
		if (*(unsigned int *)regs->pc == BKPT_OPCODE) {
			/* This is a breakpoint */
			struct exception_info bkpt_exception = {
				"Oops - undefined instruction",
				  SIGTRAP, TRAP_BRKPT
			};
			do_trap(&bkpt_exception, regs);
			iexcept_report &= ~(0xFF);
			set_iexcept(iexcept_report);
			continue;
		}

		do_trap(&iexcept_table[iexcept_num], regs);
	}
	return 0;
}