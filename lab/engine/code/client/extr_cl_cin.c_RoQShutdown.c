#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; scalar_t__* fileName; scalar_t__ alterGameState; scalar_t__ iFile; int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_DISCONNECTED ; 
 int CL_handle ; 
 int /*<<< orphan*/  Cbuf_ExecuteText (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 char* Cvar_VariableString (char*) ; 
 int /*<<< orphan*/  EXEC_APPEND ; 
 scalar_t__ FMV_IDLE ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 TYPE_2__* cinTable ; 
 TYPE_1__ clc ; 
 size_t currentHandle ; 
 int /*<<< orphan*/  va (char*,char const*) ; 

__attribute__((used)) static void RoQShutdown( void ) {
	const char *s;

	if (!cinTable[currentHandle].buf) {
		return;
	}

	if ( cinTable[currentHandle].status == FMV_IDLE ) {
		return;
	}
	Com_DPrintf("finished cinematic\n");
	cinTable[currentHandle].status = FMV_IDLE;

	if (cinTable[currentHandle].iFile) {
		FS_FCloseFile( cinTable[currentHandle].iFile );
		cinTable[currentHandle].iFile = 0;
	}

	if (cinTable[currentHandle].alterGameState) {
		clc.state = CA_DISCONNECTED;
		// we can't just do a vstr nextmap, because
		// if we are aborting the intro cinematic with
		// a devmap command, nextmap would be valid by
		// the time it was referenced
		s = Cvar_VariableString( "nextmap" );
		if ( s[0] ) {
			Cbuf_ExecuteText( EXEC_APPEND, va("%s\n", s) );
			Cvar_Set( "nextmap", "" );
		}
		CL_handle = -1;
	}
	cinTable[currentHandle].fileName[0] = 0;
	currentHandle = -1;
}