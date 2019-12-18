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
struct futex_lock {int dummy; } ;
struct cloudabi_sys_lock_unlock_args {int /*<<< orphan*/  lock; int /*<<< orphan*/  scope; } ;

/* Variables and functions */
 int futex_lock_lookup (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct futex_lock**) ; 
 int /*<<< orphan*/  futex_lock_release (struct futex_lock*) ; 
 int futex_lock_unlock (struct futex_lock*,struct thread*,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_lock_unlock(struct thread *td,
    struct cloudabi_sys_lock_unlock_args *uap)
{
	struct futex_lock *fl;
	int error;

	error = futex_lock_lookup(td, uap->lock, uap->scope, &fl);
	if (error != 0)
		return (error);
	error = futex_lock_unlock(fl, td, uap->lock);
	futex_lock_release(fl);
	return (error);
}