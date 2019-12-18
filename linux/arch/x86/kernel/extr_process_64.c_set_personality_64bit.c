#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/  personality; TYPE_2__* mm; } ;
struct TYPE_9__ {int /*<<< orphan*/  orig_ax; } ;
struct TYPE_7__ {scalar_t__ ia32_compat; } ;
struct TYPE_8__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_IMPLIES_EXEC ; 
 int /*<<< orphan*/  TIF_ADDR32 ; 
 int /*<<< orphan*/  TIF_IA32 ; 
 int /*<<< orphan*/  TIF_X32 ; 
 int /*<<< orphan*/  TS_COMPAT ; 
 int /*<<< orphan*/  __NR_execve ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 TYPE_5__* current_thread_info () ; 
 TYPE_3__* task_pt_regs (TYPE_4__*) ; 

void set_personality_64bit(void)
{
	/* inherit personality from parent */

	/* Make sure to be in 64bit mode */
	clear_thread_flag(TIF_IA32);
	clear_thread_flag(TIF_ADDR32);
	clear_thread_flag(TIF_X32);
	/* Pretend that this comes from a 64bit execve */
	task_pt_regs(current)->orig_ax = __NR_execve;
	current_thread_info()->status &= ~TS_COMPAT;

	/* Ensure the corresponding mm is not marked. */
	if (current->mm)
		current->mm->context.ia32_compat = 0;

	/* TBD: overwrites user setup. Should have two bits.
	   But 64bit processes have always behaved this way,
	   so it's not too bad. The main problem is just that
	   32bit children are affected again. */
	current->personality &= ~READ_IMPLIES_EXEC;
}