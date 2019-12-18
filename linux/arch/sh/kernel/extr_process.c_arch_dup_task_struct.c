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
struct TYPE_2__ {scalar_t__ xstate; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  task_xstate_cachep ; 
 int /*<<< orphan*/  unlazy_fpu (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstate_size ; 

int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
{
#ifdef CONFIG_SUPERH32
	unlazy_fpu(src, task_pt_regs(src));
#endif
	*dst = *src;

	if (src->thread.xstate) {
		dst->thread.xstate = kmem_cache_alloc(task_xstate_cachep,
						      GFP_KERNEL);
		if (!dst->thread.xstate)
			return -ENOMEM;
		memcpy(dst->thread.xstate, src->thread.xstate, xstate_size);
	}

	return 0;
}