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
struct thread {int /*<<< orphan*/  td_priority; } ;
struct tdq {int /*<<< orphan*/  tdq_lowpri; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 struct thread* PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRI_MAX_IDLE ; 
 int /*<<< orphan*/  TDQ_LOCK_ASSERT (struct tdq*,int /*<<< orphan*/ ) ; 
 struct tdq* TDQ_SELF () ; 
 int /*<<< orphan*/  idlethread ; 
 struct thread* tdq_choose (struct tdq*) ; 
 int /*<<< orphan*/  tdq_runq_rem (struct tdq*,struct thread*) ; 

struct thread *
sched_choose(void)
{
	struct thread *td;
	struct tdq *tdq;

	tdq = TDQ_SELF();
	TDQ_LOCK_ASSERT(tdq, MA_OWNED);
	td = tdq_choose(tdq);
	if (td) {
		tdq_runq_rem(tdq, td);
		tdq->tdq_lowpri = td->td_priority;
		return (td);
	}
	tdq->tdq_lowpri = PRI_MAX_IDLE;
	return (PCPU_GET(idlethread));
}