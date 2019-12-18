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
struct _umtx_op_args {int /*<<< orphan*/  uaddr1; int /*<<< orphan*/  val; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int do_set_ceiling (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__umtx_op_set_ceiling(struct thread *td, struct _umtx_op_args *uap)
{

	return (do_set_ceiling(td, uap->obj, uap->val, uap->uaddr1));
}