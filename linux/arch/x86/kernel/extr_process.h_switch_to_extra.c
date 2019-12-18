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
 int /*<<< orphan*/  CONFIG_SMP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned long _TIF_SPEC_IB ; 
 unsigned long _TIF_WORK_CTXSW_NEXT ; 
 unsigned long _TIF_WORK_CTXSW_PREV ; 
 int /*<<< orphan*/  __switch_to_xtra (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_to_cond_stibp ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void switch_to_extra(struct task_struct *prev,
				   struct task_struct *next)
{
	unsigned long next_tif = task_thread_info(next)->flags;
	unsigned long prev_tif = task_thread_info(prev)->flags;

	if (IS_ENABLED(CONFIG_SMP)) {
		/*
		 * Avoid __switch_to_xtra() invocation when conditional
		 * STIBP is disabled and the only different bit is
		 * TIF_SPEC_IB. For CONFIG_SMP=n TIF_SPEC_IB is not
		 * in the TIF_WORK_CTXSW masks.
		 */
		if (!static_branch_likely(&switch_to_cond_stibp)) {
			prev_tif &= ~_TIF_SPEC_IB;
			next_tif &= ~_TIF_SPEC_IB;
		}
	}

	/*
	 * __switch_to_xtra() handles debug registers, i/o bitmaps,
	 * speculation mitigations etc.
	 */
	if (unlikely(next_tif & _TIF_WORK_CTXSW_NEXT ||
		     prev_tif & _TIF_WORK_CTXSW_PREV))
		__switch_to_xtra(prev, next);
}