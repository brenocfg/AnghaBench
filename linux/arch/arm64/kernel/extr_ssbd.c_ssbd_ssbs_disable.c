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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_AA32_SSBS_BIT ; 
 int /*<<< orphan*/  PSR_SSBS_BIT ; 
 scalar_t__ is_compat_thread (int /*<<< orphan*/ ) ; 
 TYPE_1__* task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 

__attribute__((used)) static void ssbd_ssbs_disable(struct task_struct *task)
{
	u64 val = is_compat_thread(task_thread_info(task)) ?
		  PSR_AA32_SSBS_BIT : PSR_SSBS_BIT;

	task_pt_regs(task)->pstate &= ~val;
}