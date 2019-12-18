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
struct futex_condvar {scalar_t__ fc_waitcount; int /*<<< orphan*/  fc_lock; int /*<<< orphan*/  fc_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  futex_lock_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ futex_queue_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
futex_condvar_assert(const struct futex_condvar *fc)
{

	KASSERT(fc->fc_waitcount >= futex_queue_count(&fc->fc_waiters),
	    ("Total number of waiters cannot be smaller than the wait queue"));
	futex_lock_assert(fc->fc_lock);
}