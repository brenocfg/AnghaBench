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
struct umtx_robust_lists_params {int /*<<< orphan*/  robust_inact_offset; int /*<<< orphan*/  robust_priv_list_offset; int /*<<< orphan*/  robust_list_offset; } ;
struct thread {int /*<<< orphan*/  td_rb_inact; int /*<<< orphan*/  td_rbp_list; int /*<<< orphan*/  td_rb_list; } ;

/* Variables and functions */

__attribute__((used)) static int
umtx_robust_lists(struct thread *td, struct umtx_robust_lists_params *rbp)
{

	td->td_rb_list = rbp->robust_list_offset;
	td->td_rbp_list = rbp->robust_priv_list_offset;
	td->td_rb_inact = rbp->robust_inact_offset;
	return (0);
}