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
struct thread_struct {scalar_t__ amr; scalar_t__ iamr; scalar_t__ uamor; } ;

/* Variables and functions */
 int /*<<< orphan*/  pkey_disabled ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_amr (scalar_t__) ; 
 int /*<<< orphan*/  write_iamr (scalar_t__) ; 
 int /*<<< orphan*/  write_uamor (scalar_t__) ; 

void thread_pkey_regs_restore(struct thread_struct *new_thread,
			      struct thread_struct *old_thread)
{
	if (static_branch_likely(&pkey_disabled))
		return;

	if (old_thread->amr != new_thread->amr)
		write_amr(new_thread->amr);
	if (old_thread->iamr != new_thread->iamr)
		write_iamr(new_thread->iamr);
	if (old_thread->uamor != new_thread->uamor)
		write_uamor(new_thread->uamor);
}