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
struct thread {int dummy; } ;
struct _umtx_time {int dummy; } ;
struct _umtx_op_args {int /*<<< orphan*/  val; int /*<<< orphan*/  obj; scalar_t__ uaddr1; int /*<<< orphan*/ * uaddr2; } ;

/* Variables and functions */
 int do_wait (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _umtx_time*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int umtx_copyin_umtx_time (int /*<<< orphan*/ *,size_t,struct _umtx_time*) ; 

__attribute__((used)) static int
__umtx_op_wait(struct thread *td, struct _umtx_op_args *uap)
{
	struct _umtx_time timeout, *tm_p;
	int error;

	if (uap->uaddr2 == NULL)
		tm_p = NULL;
	else {
		error = umtx_copyin_umtx_time(
		    uap->uaddr2, (size_t)uap->uaddr1, &timeout);
		if (error != 0)
			return (error);
		tm_p = &timeout;
	}
	return (do_wait(td, uap->obj, uap->val, tm_p, 0, 0));
}