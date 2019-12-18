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
 int MallocCount ; 
 int MallocMax ; 
 int /*<<< orphan*/  MallocPool ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  zallocstats (int /*<<< orphan*/ *) ; 

void
mallocstats(void)
{
	printf("Active Allocations: %d/%d\n", MallocCount, MallocMax);
#ifdef ZALLOCDEBUG
	zallocstats(&MallocPool);
#endif
}