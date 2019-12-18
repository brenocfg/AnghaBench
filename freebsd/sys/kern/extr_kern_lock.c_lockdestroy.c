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
struct lock {scalar_t__ lk_lock; scalar_t__ lk_recurse; scalar_t__ lk_exslpfail; int /*<<< orphan*/  lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ LK_UNLOCKED ; 
 int /*<<< orphan*/  lock_destroy (int /*<<< orphan*/ *) ; 

void
lockdestroy(struct lock *lk)
{

	KASSERT(lk->lk_lock == LK_UNLOCKED, ("lockmgr still held"));
	KASSERT(lk->lk_recurse == 0, ("lockmgr still recursed"));
	KASSERT(lk->lk_exslpfail == 0, ("lockmgr still exclusive waiters"));
	lock_destroy(&lk->lock_object);
}