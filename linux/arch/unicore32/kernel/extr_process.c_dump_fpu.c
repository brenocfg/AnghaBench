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
struct thread_info {int* used_cp; int /*<<< orphan*/  fpstate; } ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  elf_fpregset_t ;

/* Variables and functions */
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fp)
{
	struct thread_info *thread = current_thread_info();
	int used_math = thread->used_cp[1] | thread->used_cp[2];

#ifdef CONFIG_UNICORE_FPU_F64
	if (used_math)
		memcpy(fp, &thread->fpstate, sizeof(*fp));
#endif
	return used_math != 0;
}