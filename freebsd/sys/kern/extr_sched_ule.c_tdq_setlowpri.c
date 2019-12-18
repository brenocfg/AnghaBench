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
struct tdq {scalar_t__ tdq_lowpri; } ;
struct TYPE_2__ {struct thread* pc_curthread; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TDQ_ID (struct tdq*) ; 
 int /*<<< orphan*/  TDQ_LOCK_ASSERT (struct tdq*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pcpu_find (int /*<<< orphan*/ ) ; 
 struct thread* tdq_choose (struct tdq*) ; 

__attribute__((used)) static void
tdq_setlowpri(struct tdq *tdq, struct thread *ctd)
{
	struct thread *td;

	TDQ_LOCK_ASSERT(tdq, MA_OWNED);
	if (ctd == NULL)
		ctd = pcpu_find(TDQ_ID(tdq))->pc_curthread;
	td = tdq_choose(tdq);
	if (td == NULL || td->td_priority > ctd->td_priority)
		tdq->tdq_lowpri = ctd->td_priority;
	else
		tdq->tdq_lowpri = td->td_priority;
}