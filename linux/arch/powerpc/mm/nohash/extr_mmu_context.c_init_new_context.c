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
struct TYPE_2__ {scalar_t__ id; scalar_t__ active; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 scalar_t__ MMU_NO_CONTEXT ; 
 int /*<<< orphan*/  pr_hard (char*,struct mm_struct*) ; 
 int /*<<< orphan*/  pte_frag_set (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slice_init_new_context_exec (struct mm_struct*) ; 

int init_new_context(struct task_struct *t, struct mm_struct *mm)
{
	pr_hard("initing context for mm @%p\n", mm);

	/*
	 * We have MMU_NO_CONTEXT set to be ~0. Hence check
	 * explicitly against context.id == 0. This ensures that we properly
	 * initialize context slice details for newly allocated mm's (which will
	 * have id == 0) and don't alter context slice inherited via fork (which
	 * will have id != 0).
	 */
	if (mm->context.id == 0)
		slice_init_new_context_exec(mm);
	mm->context.id = MMU_NO_CONTEXT;
	mm->context.active = 0;
	pte_frag_set(&mm->context, NULL);
	return 0;
}