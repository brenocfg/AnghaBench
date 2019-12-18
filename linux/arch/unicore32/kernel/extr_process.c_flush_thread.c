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
struct thread_info {int /*<<< orphan*/  fpstate; int /*<<< orphan*/ * used_cp; } ;
struct TYPE_2__ {int /*<<< orphan*/  debug; } ;
struct task_struct {TYPE_1__ thread; } ;
struct fp_state {int dummy; } ;
struct debug_info {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void flush_thread(void)
{
	struct thread_info *thread = current_thread_info();
	struct task_struct *tsk = current;

	memset(thread->used_cp, 0, sizeof(thread->used_cp));
	memset(&tsk->thread.debug, 0, sizeof(struct debug_info));
#ifdef CONFIG_UNICORE_FPU_F64
	memset(&thread->fpstate, 0, sizeof(struct fp_state));
#endif
}