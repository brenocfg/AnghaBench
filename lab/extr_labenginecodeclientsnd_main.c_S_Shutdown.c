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
typedef  int /*<<< orphan*/  soundInterface_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* Shutdown ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd_RemoveCommand (char*) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_CodecShutdown () ; 
 TYPE_1__ si ; 
 int /*<<< orphan*/  stub1 () ; 

void S_Shutdown( void )
{
	if( si.Shutdown ) {
		si.Shutdown( );
	}

	Com_Memset( &si, 0, sizeof( soundInterface_t ) );

	Cmd_RemoveCommand( "play" );
	Cmd_RemoveCommand( "music");
	Cmd_RemoveCommand( "stopmusic");
	Cmd_RemoveCommand( "s_list" );
	Cmd_RemoveCommand( "s_stop" );
	Cmd_RemoveCommand( "s_info" );

	S_CodecShutdown( );
}