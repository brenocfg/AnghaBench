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
struct pt_regs {unsigned long pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  do_single_step (struct pt_regs*) ; 
 int /*<<< orphan*/  kgdb_cpu_doing_single_step ; 
 int /*<<< orphan*/  kgdb_hex2long (char**,unsigned long*) ; 
 int kgdb_single_step ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  undo_single_step (struct pt_regs*) ; 

int kgdb_arch_handle_exception(int e_vector, int signo, int err_code,
			       char *remcomInBuffer, char *remcomOutBuffer,
			       struct pt_regs *linux_regs)
{
	unsigned long addr;
	char *ptr;

	/* Undo any stepping we may have done */
	undo_single_step(linux_regs);

	switch (remcomInBuffer[0]) {
	case 'c':
	case 's':
		/* try to read optional parameter, pc unchanged if no parm */
		ptr = &remcomInBuffer[1];
		if (kgdb_hex2long(&ptr, &addr))
			linux_regs->pc = addr;
	case 'D':
	case 'k':
		atomic_set(&kgdb_cpu_doing_single_step, -1);

		if (remcomInBuffer[0] == 's') {
			do_single_step(linux_regs);
			kgdb_single_step = 1;

			atomic_set(&kgdb_cpu_doing_single_step,
				   raw_smp_processor_id());
		}

		return 0;
	}

	/* this means that we do not want to exit from the handler: */
	return -1;
}