#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_buf {int /*<<< orphan*/  buffer; } ;
struct pt_regs {int nip; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int NR_INSN_TO_PRINT ; 
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  __access_ok (unsigned long,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ probe_kernel_address (void const*,int) ; 
 int /*<<< orphan*/  seq_buf_clear (struct seq_buf*) ; 
 int /*<<< orphan*/  seq_buf_has_overflowed (struct seq_buf*) ; 
 int /*<<< orphan*/  seq_buf_init (struct seq_buf*,char*,int) ; 
 int /*<<< orphan*/  seq_buf_printf (struct seq_buf*,char*,...) ; 

void show_user_instructions(struct pt_regs *regs)
{
	unsigned long pc;
	int n = NR_INSN_TO_PRINT;
	struct seq_buf s;
	char buf[96]; /* enough for 8 times 9 + 2 chars */

	pc = regs->nip - (NR_INSN_TO_PRINT * 3 / 4 * sizeof(int));

	/*
	 * Make sure the NIP points at userspace, not kernel text/data or
	 * elsewhere.
	 */
	if (!__access_ok(pc, NR_INSN_TO_PRINT * sizeof(int), USER_DS)) {
		pr_info("%s[%d]: Bad NIP, not dumping instructions.\n",
			current->comm, current->pid);
		return;
	}

	seq_buf_init(&s, buf, sizeof(buf));

	while (n) {
		int i;

		seq_buf_clear(&s);

		for (i = 0; i < 8 && n; i++, n--, pc += sizeof(int)) {
			int instr;

			if (probe_kernel_address((const void *)pc, instr)) {
				seq_buf_printf(&s, "XXXXXXXX ");
				continue;
			}
			seq_buf_printf(&s, regs->nip == pc ? "<%08x> " : "%08x ", instr);
		}

		if (!seq_buf_has_overflowed(&s))
			pr_info("%s[%d]: code: %s\n", current->comm,
				current->pid, s.buffer);
	}
}