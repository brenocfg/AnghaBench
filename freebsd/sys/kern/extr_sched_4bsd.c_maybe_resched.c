#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {scalar_t__ td_priority; } ;
struct TYPE_2__ {scalar_t__ td_priority; int /*<<< orphan*/  td_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TDF_NEEDRESCHED ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 

__attribute__((used)) static void
maybe_resched(struct thread *td)
{

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	if (td->td_priority < curthread->td_priority)
		curthread->td_flags |= TDF_NEEDRESCHED;
}