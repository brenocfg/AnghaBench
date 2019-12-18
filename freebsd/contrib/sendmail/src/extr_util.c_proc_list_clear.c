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
struct TYPE_2__ {int /*<<< orphan*/  proc_pid; } ;

/* Variables and functions */
 scalar_t__ CurChildren ; 
 int /*<<< orphan*/  NO_PID ; 
 int ProcListSize ; 
 TYPE_1__* ProcListVec ; 

void
proc_list_clear()
{
	int i;

	/* start from 1 since 0 is the daemon itself */
	for (i = 1; i < ProcListSize; i++)
		ProcListVec[i].proc_pid = NO_PID;
	CurChildren = 0;
}