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
struct thread {int /*<<< orphan*/  td_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TDF_BOUND ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 

void
sched_unbind(struct thread* td)
{
	THREAD_LOCK_ASSERT(td, MA_OWNED);
	KASSERT(td == curthread, ("sched_unbind: can only bind curthread"));
	td->td_flags &= ~TDF_BOUND;
}