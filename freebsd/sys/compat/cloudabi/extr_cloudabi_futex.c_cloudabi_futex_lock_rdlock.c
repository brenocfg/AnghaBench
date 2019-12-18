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
typedef  int /*<<< orphan*/  cloudabi_timestamp_t ;
typedef  int /*<<< orphan*/  cloudabi_scope_t ;
typedef  int /*<<< orphan*/  cloudabi_lock_t ;
typedef  int /*<<< orphan*/  cloudabi_clockid_t ;

/* Variables and functions */
 int futex_lock_lookup (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct futex_lock**) ; 
 int futex_lock_rdlock (struct futex_lock*,struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  futex_lock_release (struct futex_lock*) ; 

int
cloudabi_futex_lock_rdlock(struct thread *td, cloudabi_lock_t *lock,
    cloudabi_scope_t scope, cloudabi_clockid_t clock_id,
    cloudabi_timestamp_t timeout, cloudabi_timestamp_t precision, bool abstime)
{
	struct futex_lock *fl;
	int error;

	/* Look up lock object. */
	error = futex_lock_lookup(td, lock, scope, &fl);
	if (error != 0)
		return (error);

	error = futex_lock_rdlock(fl, td, lock, clock_id, timeout,
	    precision, abstime);
	futex_lock_release(fl);
	return (error);
}