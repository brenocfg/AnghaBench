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
struct thr_create_initthr_args {int /*<<< orphan*/  tid; int /*<<< orphan*/  ctx; } ;
struct thr_create_args {int /*<<< orphan*/  id; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thr_create_initthr ; 
 int thread_create (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thr_create_initthr_args*) ; 

int
sys_thr_create(struct thread *td, struct thr_create_args *uap)
    /* ucontext_t *ctx, long *id, int flags */
{
	struct thr_create_initthr_args args;
	int error;

	if ((error = copyin(uap->ctx, &args.ctx, sizeof(args.ctx))))
		return (error);
	args.tid = uap->id;
	return (thread_create(td, NULL, thr_create_initthr, &args));
}