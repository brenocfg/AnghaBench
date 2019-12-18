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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _save_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ is_fpu_owner () ; 
 scalar_t__ is_msa_enabled () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  save_dsp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_msa (int /*<<< orphan*/ ) ; 

int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
{
	/*
	 * Save any process state which is live in hardware registers to the
	 * parent context prior to duplication. This prevents the new child
	 * state becoming stale if the parent is preempted before copy_thread()
	 * gets a chance to save the parent's live hardware registers to the
	 * child context.
	 */
	preempt_disable();

	if (is_msa_enabled())
		save_msa(current);
	else if (is_fpu_owner())
		_save_fp(current);

	save_dsp(current);

	preempt_enable();

	*dst = *src;
	return 0;
}