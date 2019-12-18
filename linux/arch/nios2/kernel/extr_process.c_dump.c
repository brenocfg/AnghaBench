#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {scalar_t__ sp; scalar_t__ ea; int /*<<< orphan*/  fp; int /*<<< orphan*/  ra; int /*<<< orphan*/  orig_r2; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  r7; int /*<<< orphan*/  r6; int /*<<< orphan*/  r5; int /*<<< orphan*/  r4; int /*<<< orphan*/  r3; int /*<<< orphan*/  r2; int /*<<< orphan*/  r1; scalar_t__ estatus; } ;
struct TYPE_4__ {TYPE_1__* mm; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_3__ {scalar_t__ start_stack; scalar_t__ brk; scalar_t__ end_data; scalar_t__ start_data; scalar_t__ end_code; scalar_t__ start_code; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 

void dump(struct pt_regs *fp)
{
	unsigned long	*sp;
	unsigned char	*tp;
	int		i;

	pr_emerg("\nCURRENT PROCESS:\n\n");
	pr_emerg("COMM=%s PID=%d\n", current->comm, current->pid);

	if (current->mm) {
		pr_emerg("TEXT=%08x-%08x DATA=%08x-%08x BSS=%08x-%08x\n",
			(int) current->mm->start_code,
			(int) current->mm->end_code,
			(int) current->mm->start_data,
			(int) current->mm->end_data,
			(int) current->mm->end_data,
			(int) current->mm->brk);
		pr_emerg("USER-STACK=%08x  KERNEL-STACK=%08x\n\n",
			(int) current->mm->start_stack,
			(int)(((unsigned long) current) + THREAD_SIZE));
	}

	pr_emerg("PC: %08lx\n", fp->ea);
	pr_emerg("SR: %08lx    SP: %08lx\n",
		(long) fp->estatus, (long) fp);

	pr_emerg("r1: %08lx    r2: %08lx    r3: %08lx\n",
		fp->r1, fp->r2, fp->r3);

	pr_emerg("r4: %08lx    r5: %08lx    r6: %08lx    r7: %08lx\n",
		fp->r4, fp->r5, fp->r6, fp->r7);
	pr_emerg("r8: %08lx    r9: %08lx    r10: %08lx    r11: %08lx\n",
		fp->r8, fp->r9, fp->r10, fp->r11);
	pr_emerg("r12: %08lx  r13: %08lx    r14: %08lx    r15: %08lx\n",
		fp->r12, fp->r13, fp->r14, fp->r15);
	pr_emerg("or2: %08lx   ra: %08lx     fp: %08lx    sp: %08lx\n",
		fp->orig_r2, fp->ra, fp->fp, fp->sp);
	pr_emerg("\nUSP: %08x   TRAPFRAME: %08x\n",
		(unsigned int) fp->sp, (unsigned int) fp);

	pr_emerg("\nCODE:");
	tp = ((unsigned char *) fp->ea) - 0x20;
	for (sp = (unsigned long *) tp, i = 0; (i < 0x40);  i += 4) {
		if ((i % 0x10) == 0)
			pr_emerg("\n%08x: ", (int) (tp + i));
		pr_emerg("%08x ", (int) *sp++);
	}
	pr_emerg("\n");

	pr_emerg("\nKERNEL STACK:");
	tp = ((unsigned char *) fp) - 0x40;
	for (sp = (unsigned long *) tp, i = 0; (i < 0xc0); i += 4) {
		if ((i % 0x10) == 0)
			pr_emerg("\n%08x: ", (int) (tp + i));
		pr_emerg("%08x ", (int) *sp++);
	}
	pr_emerg("\n");
	pr_emerg("\n");

	pr_emerg("\nUSER STACK:");
	tp = (unsigned char *) (fp->sp - 0x10);
	for (sp = (unsigned long *) tp, i = 0; (i < 0x80); i += 4) {
		if ((i % 0x10) == 0)
			pr_emerg("\n%08x: ", (int) (tp + i));
		pr_emerg("%08x ", (int) *sp++);
	}
	pr_emerg("\n\n");
}