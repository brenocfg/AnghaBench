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
struct thread_struct {int /*<<< orphan*/  uamor; int /*<<< orphan*/  iamr; int /*<<< orphan*/  amr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pkey_disabled ; 
 int /*<<< orphan*/  read_amr () ; 
 int /*<<< orphan*/  read_iamr () ; 
 int /*<<< orphan*/  read_uamor () ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 

void thread_pkey_regs_save(struct thread_struct *thread)
{
	if (static_branch_likely(&pkey_disabled))
		return;

	/*
	 * TODO: Skip saving registers if @thread hasn't used any keys yet.
	 */
	thread->amr = read_amr();
	thread->iamr = read_iamr();
	thread->uamor = read_uamor();
}