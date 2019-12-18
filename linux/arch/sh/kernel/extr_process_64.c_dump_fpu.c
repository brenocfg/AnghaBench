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
struct TYPE_4__ {TYPE_1__* xstate; } ;
struct task_struct {TYPE_2__ thread; } ;
struct pt_regs {int /*<<< orphan*/  sr; } ;
typedef  int /*<<< orphan*/  elf_fpregset_t ;
struct TYPE_3__ {int /*<<< orphan*/  hardfpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_FD ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  disable_fpu () ; 
 int /*<<< orphan*/  enable_fpu () ; 
 struct task_struct* last_task_used_math ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  save_fpu (struct task_struct*) ; 
 int /*<<< orphan*/  tsk_used_math (struct task_struct*) ; 

int dump_fpu(struct pt_regs *regs, elf_fpregset_t *fpu)
{
#ifdef CONFIG_SH_FPU
	int fpvalid;
	struct task_struct *tsk = current;

	fpvalid = !!tsk_used_math(tsk);
	if (fpvalid) {
		if (current == last_task_used_math) {
			enable_fpu();
			save_fpu(tsk);
			disable_fpu();
			last_task_used_math = 0;
			regs->sr |= SR_FD;
		}

		memcpy(fpu, &tsk->thread.xstate->hardfpu, sizeof(*fpu));
	}

	return fpvalid;
#else
	return 0; /* Task didn't use the fpu at all. */
#endif
}