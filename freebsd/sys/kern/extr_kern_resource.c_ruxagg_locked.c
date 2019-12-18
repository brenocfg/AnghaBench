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
struct thread {scalar_t__ td_iticks; scalar_t__ td_sticks; scalar_t__ td_uticks; scalar_t__ td_incruntime; int /*<<< orphan*/  td_proc; } ;
struct rusage_ext {int /*<<< orphan*/  rux_iticks; int /*<<< orphan*/  rux_sticks; int /*<<< orphan*/  rux_uticks; int /*<<< orphan*/  rux_runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_STATLOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ruxagg_locked(struct rusage_ext *rux, struct thread *td)
{

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	PROC_STATLOCK_ASSERT(td->td_proc, MA_OWNED);
	rux->rux_runtime += td->td_incruntime;
	rux->rux_uticks += td->td_uticks;
	rux->rux_sticks += td->td_sticks;
	rux->rux_iticks += td->td_iticks;
}