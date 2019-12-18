#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pmc_binding {int /*<<< orphan*/  pb_cpu; scalar_t__ pb_bound; } ;
struct TYPE_6__ {int /*<<< orphan*/  td_oncpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BND ; 
 int /*<<< orphan*/  CPU ; 
 int /*<<< orphan*/  PMCDBG0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  PMCDBG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  sched_bind (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_unbind (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
pmc_restore_cpu_binding(struct pmc_binding *pb)
{
	PMCDBG2(CPU,BND,2, "restore-cpu curcpu=%d restore=%d",
	    curthread->td_oncpu, pb->pb_cpu);
	thread_lock(curthread);
	if (pb->pb_bound)
		sched_bind(curthread, pb->pb_cpu);
	else
		sched_unbind(curthread);
	thread_unlock(curthread);
	PMCDBG0(CPU,BND,2, "restore-cpu done");
}