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

/* Variables and functions */
 int /*<<< orphan*/  CPU_ABSENT (int) ; 
 int* DPCPU_ID_PTR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  pcputicks ; 
 int ticks ; 

void
hardclock_sync(int cpu)
{
	int *t;
	KASSERT(!CPU_ABSENT(cpu), ("Absent CPU %d", cpu));
	t = DPCPU_ID_PTR(cpu, pcputicks);

	*t = ticks;
}