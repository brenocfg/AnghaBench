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
struct lock_object {int /*<<< orphan*/  lo_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOCK_LOG_DESTROY (struct lock_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LO_INITIALIZED ; 
 int /*<<< orphan*/  WITNESS_DESTROY (struct lock_object*) ; 
 int /*<<< orphan*/  lock_initialized (struct lock_object*) ; 

void
lock_destroy(struct lock_object *lock)
{

	KASSERT(lock_initialized(lock), ("lock %p is not initialized", lock));
	WITNESS_DESTROY(lock);
	LOCK_LOG_DESTROY(lock, 0);
	lock->lo_flags &= ~LO_INITIALIZED;
}