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
 int /*<<< orphan*/  pkey_amr_mask ; 
 int /*<<< orphan*/  pkey_disabled ; 
 int /*<<< orphan*/  pkey_iamr_mask ; 
 int /*<<< orphan*/  pkey_uamor_mask ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_amr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_iamr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uamor (int /*<<< orphan*/ ) ; 

void thread_pkey_regs_init(struct thread_struct *thread)
{
	if (static_branch_likely(&pkey_disabled))
		return;

	thread->amr = pkey_amr_mask;
	thread->iamr = pkey_iamr_mask;
	thread->uamor = pkey_uamor_mask;

	write_uamor(pkey_uamor_mask);
	write_amr(pkey_amr_mask);
	write_iamr(pkey_iamr_mask);
}