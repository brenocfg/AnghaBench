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
struct umtx_robust_lists_params {int dummy; } ;
struct thread {int dummy; } ;
struct _umtx_op_args {int val; int /*<<< orphan*/  uaddr1; } ;
typedef  int /*<<< orphan*/  rb ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bzero (struct umtx_robust_lists_params*,int) ; 
 int copyin (int /*<<< orphan*/ ,struct umtx_robust_lists_params*,int) ; 
 int umtx_robust_lists (struct thread*,struct umtx_robust_lists_params*) ; 

__attribute__((used)) static int
__umtx_op_robust_lists(struct thread *td, struct _umtx_op_args *uap)
{
	struct umtx_robust_lists_params rb;
	int error;

	if (uap->val > sizeof(rb))
		return (EINVAL);
	bzero(&rb, sizeof(rb));
	error = copyin(uap->uaddr1, &rb, uap->val);
	if (error != 0)
		return (error);
	return (umtx_robust_lists(td, &rb));
}