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
struct futex_condvar {int /*<<< orphan*/  fc_waiters; } ;
typedef  int /*<<< orphan*/  cloudabi_condvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOUDABI_CONDVAR_HAS_NO_WAITERS ; 
 scalar_t__ futex_queue_count (int /*<<< orphan*/ *) ; 
 int futex_user_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
futex_condvar_unmanage(struct futex_condvar *fc,
    cloudabi_condvar_t *condvar)
{

	if (futex_queue_count(&fc->fc_waiters) != 0)
		return (0);
	return (futex_user_store(condvar, CLOUDABI_CONDVAR_HAS_NO_WAITERS));
}