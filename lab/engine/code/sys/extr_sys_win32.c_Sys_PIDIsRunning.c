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
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  processes ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnumProcesses (int*,int,int*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean Sys_PIDIsRunning( int pid )
{
	DWORD processes[ 1024 ];
	DWORD numBytes, numProcesses;
	int i;

	if( !EnumProcesses( processes, sizeof( processes ), &numBytes ) )
		return qfalse; // Assume it's not running

	numProcesses = numBytes / sizeof( DWORD );

	// Search for the pid
	for( i = 0; i < numProcesses; i++ )
	{
		if( processes[ i ] == pid )
			return qtrue;
	}

	return qfalse;
}