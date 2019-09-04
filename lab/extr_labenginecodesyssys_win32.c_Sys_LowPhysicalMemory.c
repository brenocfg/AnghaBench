#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {scalar_t__ dwTotalPhys; } ;
typedef  TYPE_1__ MEMORYSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalMemoryStatus (TYPE_1__*) ; 
 scalar_t__ MEM_THRESHOLD ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Sys_LowPhysicalMemory( void )
{
	MEMORYSTATUS stat;
	GlobalMemoryStatus (&stat);
	return (stat.dwTotalPhys <= MEM_THRESHOLD) ? qtrue : qfalse;
}