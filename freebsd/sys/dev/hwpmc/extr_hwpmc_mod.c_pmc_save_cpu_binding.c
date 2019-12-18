#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pmc_binding {int /*<<< orphan*/  pb_cpu; int /*<<< orphan*/  pb_bound; } ;
struct TYPE_5__ {int /*<<< orphan*/  td_oncpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BND ; 
 int /*<<< orphan*/  CPU ; 
 int /*<<< orphan*/  PMCDBG0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  PMCDBG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  sched_is_bound (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
pmc_save_cpu_binding(struct pmc_binding *pb)
{
	PMCDBG0(CPU,BND,2, "save-cpu");
	thread_lock(curthread);
	pb->pb_bound = sched_is_bound(curthread);
	pb->pb_cpu   = curthread->td_oncpu;
	thread_unlock(curthread);
	PMCDBG1(CPU,BND,2, "save-cpu cpu=%d", pb->pb_cpu);
}