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
struct task_struct {int dummy; } ;
struct TYPE_2__ {unsigned long flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SPEC_FORCE_UPDATE ; 
 int /*<<< orphan*/  TIF_SPEC_IB ; 
 int /*<<< orphan*/  TIF_SSBD ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ task_spec_ib_disable (struct task_struct*) ; 
 scalar_t__ task_spec_ssb_disable (struct task_struct*) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 
 scalar_t__ test_and_clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long speculation_ctrl_update_tif(struct task_struct *tsk)
{
	if (test_and_clear_tsk_thread_flag(tsk, TIF_SPEC_FORCE_UPDATE)) {
		if (task_spec_ssb_disable(tsk))
			set_tsk_thread_flag(tsk, TIF_SSBD);
		else
			clear_tsk_thread_flag(tsk, TIF_SSBD);

		if (task_spec_ib_disable(tsk))
			set_tsk_thread_flag(tsk, TIF_SPEC_IB);
		else
			clear_tsk_thread_flag(tsk, TIF_SPEC_IB);
	}
	/* Return the updated threadinfo flags*/
	return task_thread_info(tsk)->flags;
}