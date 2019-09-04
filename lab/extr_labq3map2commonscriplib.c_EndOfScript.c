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
struct TYPE_3__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  line; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Sys_Printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endofscript ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__* script ; 
 int /*<<< orphan*/  scriptline ; 
 TYPE_1__* scriptstack ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

qboolean EndOfScript( qboolean crossline ){
	if ( !crossline ) {
		Error( "Line %i is incomplete\n",scriptline );
	}

	if ( !strcmp( script->filename, "memory buffer" ) ) {
		endofscript = qtrue;
		return qfalse;
	}

	if ( script->buffer == NULL ) {
		Sys_FPrintf( SYS_WRN, "WARNING: Attempt to free already freed script buffer\n" );
	}
	else{
		free( script->buffer );
	}
	script->buffer = NULL;
	if ( script == scriptstack + 1 ) {
		endofscript = qtrue;
		return qfalse;
	}
	script--;
	scriptline = script->line;
	Sys_Printf( "returning to %s\n", script->filename );
	return GetToken( crossline );
}