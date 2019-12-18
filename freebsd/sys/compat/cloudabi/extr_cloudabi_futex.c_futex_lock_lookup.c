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
struct futex_address {int dummy; } ;
typedef  int /*<<< orphan*/  cloudabi_scope_t ;
typedef  int /*<<< orphan*/  cloudabi_lock_t ;

/* Variables and functions */
 int futex_address_create (struct futex_address*,struct thread*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futex_global_lock ; 
 struct futex_lock* futex_lock_lookup_locked (struct futex_address*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
futex_lock_lookup(struct thread *td, const cloudabi_lock_t *address,
    cloudabi_scope_t scope, struct futex_lock **flret)
{
	struct futex_address fa;
	int error;

	error = futex_address_create(&fa, td, address, scope);
	if (error != 0)
		return (error);

	sx_xlock(&futex_global_lock);
	*flret = futex_lock_lookup_locked(&fa);
	return (0);
}