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
struct TYPE_3__ {int /*<<< orphan*/ * sve_state; } ;
struct task_struct {TYPE_1__ thread; } ;
struct TYPE_4__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_THREAD_INFO_IN_TASK ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIF_SVE ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  fpsimd_preserve_current_state () ; 

int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
{
	if (current->mm)
		fpsimd_preserve_current_state();
	*dst = *src;

	/* We rely on the above assignment to initialize dst's thread_flags: */
	BUILD_BUG_ON(!IS_ENABLED(CONFIG_THREAD_INFO_IN_TASK));

	/*
	 * Detach src's sve_state (if any) from dst so that it does not
	 * get erroneously used or freed prematurely.  dst's sve_state
	 * will be allocated on demand later on if dst uses SVE.
	 * For consistency, also clear TIF_SVE here: this could be done
	 * later in copy_process(), but to avoid tripping up future
	 * maintainers it is best not to leave TIF_SVE and sve_state in
	 * an inconsistent state, even temporarily.
	 */
	dst->thread.sve_state = NULL;
	clear_tsk_thread_flag(dst, TIF_SVE);

	return 0;
}