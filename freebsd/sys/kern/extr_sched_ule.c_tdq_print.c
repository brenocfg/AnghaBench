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
struct tdq {char* tdq_name; int tdq_load; int tdq_switchcnt; int tdq_oldswitchcnt; int tdq_idx; int tdq_ridx; int tdq_transferable; int tdq_lowpri; int /*<<< orphan*/  tdq_idle; int /*<<< orphan*/  tdq_timeshare; int /*<<< orphan*/  tdq_realtime; } ;

/* Variables and functions */
 struct tdq* TDQ_CPU (int) ; 
 int TDQ_ID (struct tdq*) ; 
 int /*<<< orphan*/  TDQ_LOCKPTR (struct tdq*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  runq_print (int /*<<< orphan*/ *) ; 

void
tdq_print(int cpu)
{
	struct tdq *tdq;

	tdq = TDQ_CPU(cpu);

	printf("tdq %d:\n", TDQ_ID(tdq));
	printf("\tlock            %p\n", TDQ_LOCKPTR(tdq));
	printf("\tLock name:      %s\n", tdq->tdq_name);
	printf("\tload:           %d\n", tdq->tdq_load);
	printf("\tswitch cnt:     %d\n", tdq->tdq_switchcnt);
	printf("\told switch cnt: %d\n", tdq->tdq_oldswitchcnt);
	printf("\ttimeshare idx:  %d\n", tdq->tdq_idx);
	printf("\ttimeshare ridx: %d\n", tdq->tdq_ridx);
	printf("\tload transferable: %d\n", tdq->tdq_transferable);
	printf("\tlowest priority:   %d\n", tdq->tdq_lowpri);
	printf("\trealtime runq:\n");
	runq_print(&tdq->tdq_realtime);
	printf("\ttimeshare runq:\n");
	runq_print(&tdq->tdq_timeshare);
	printf("\tidle runq:\n");
	runq_print(&tdq->tdq_idle);
}