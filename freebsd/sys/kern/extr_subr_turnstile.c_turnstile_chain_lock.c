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
struct turnstile_chain {int /*<<< orphan*/  tc_lock; } ;
struct lock_object {int dummy; } ;

/* Variables and functions */
 struct turnstile_chain* TC_LOOKUP (struct lock_object*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 

void
turnstile_chain_lock(struct lock_object *lock)
{
	struct turnstile_chain *tc;

	tc = TC_LOOKUP(lock);
	mtx_lock_spin(&tc->tc_lock);
}