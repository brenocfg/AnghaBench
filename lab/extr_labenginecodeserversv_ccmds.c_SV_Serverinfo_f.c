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
struct TYPE_2__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVAR_SERVERINFO ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_InfoString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Info_Print (int /*<<< orphan*/ ) ; 
 TYPE_1__* com_sv_running ; 

__attribute__((used)) static void SV_Serverinfo_f( void ) {
	// make sure server is running
	if ( !com_sv_running->integer ) {
		Com_Printf( "Server is not running.\n" );
		return;
	}

	Com_Printf ("Server info settings:\n");
	Info_Print ( Cvar_InfoString( CVAR_SERVERINFO ) );
}