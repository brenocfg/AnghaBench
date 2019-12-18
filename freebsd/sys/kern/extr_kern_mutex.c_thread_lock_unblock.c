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
struct thread {int /*<<< orphan*/ * td_lock; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  atomic_store_rel_ptr (void volatile*,uintptr_t) ; 
 int /*<<< orphan*/  blocked_lock ; 
 int /*<<< orphan*/  mtx_assert (struct mtx*,int /*<<< orphan*/ ) ; 

void
thread_lock_unblock(struct thread *td, struct mtx *new)
{
	mtx_assert(new, MA_OWNED);
	MPASS(td->td_lock == &blocked_lock);
	atomic_store_rel_ptr((volatile void *)&td->td_lock, (uintptr_t)new);
}