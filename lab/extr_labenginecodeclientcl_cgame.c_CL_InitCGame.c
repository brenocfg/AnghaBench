#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vmInterpret_t ;
struct TYPE_5__ {char* stringData; int* stringOffsets; } ;
struct TYPE_8__ {int /*<<< orphan*/  mapname; TYPE_1__ gameState; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; int /*<<< orphan*/  demoplaying; int /*<<< orphan*/  clientNum; int /*<<< orphan*/  lastExecutedServerCommand; int /*<<< orphan*/  serverMessageSequence; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* EndRegistration ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CA_LOADING ; 
 int /*<<< orphan*/  CA_PRIMED ; 
 int /*<<< orphan*/  CG_INIT ; 
 int /*<<< orphan*/  CL_CgameSystemCalls ; 
 size_t CS_SERVERINFO ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,int) ; 
 int /*<<< orphan*/  Com_TouchMemory () ; 
 int /*<<< orphan*/  Com_sprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  Con_ClearNotify () ; 
 int /*<<< orphan*/  Con_Close () ; 
 int /*<<< orphan*/  Cvar_SetCheatState () ; 
 scalar_t__ Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 char* Info_ValueForKey (char const*,char*) ; 
 int /*<<< orphan*/  Sys_LowPhysicalMemory () ; 
 int Sys_Milliseconds () ; 
 scalar_t__ VMI_BYTECODE ; 
 scalar_t__ VMI_COMPILED ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_Create (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cgvm ; 
 TYPE_4__ cl ; 
 int /*<<< orphan*/  cl_connectedToCheatServer ; 
 scalar_t__ cl_connectedToPureServer ; 
 TYPE_3__ clc ; 
 TYPE_2__ re ; 
 int /*<<< orphan*/  stub1 () ; 

void CL_InitCGame( void ) {
	const char			*info;
	const char			*mapname;
	int					t1, t2;
	vmInterpret_t		interpret;

	t1 = Sys_Milliseconds();

	// put away the console
	Con_Close();

	// find the current mapname
	info = cl.gameState.stringData + cl.gameState.stringOffsets[ CS_SERVERINFO ];
	mapname = Info_ValueForKey( info, "mapname" );
	Com_sprintf( cl.mapname, sizeof( cl.mapname ), "maps/%s.bsp", mapname );

	// load the dll or bytecode
	interpret = Cvar_VariableValue("vm_cgame");
	if(cl_connectedToPureServer)
	{
		// if sv_pure is set we only allow qvms to be loaded
		if(interpret != VMI_COMPILED && interpret != VMI_BYTECODE)
			interpret = VMI_COMPILED;
	}

	cgvm = VM_Create( "cgame", CL_CgameSystemCalls, interpret );
	if ( !cgvm ) {
		Com_Error( ERR_DROP, "VM_Create on cgame failed" );
	}
	clc.state = CA_LOADING;

	// init for this gamestate
	// use the lastExecutedServerCommand instead of the serverCommandSequence
	// otherwise server commands sent just before a gamestate are dropped
	VM_Call( cgvm, CG_INIT, clc.serverMessageSequence, clc.lastExecutedServerCommand, clc.clientNum );

	// reset any CVAR_CHEAT cvars registered by cgame
	if ( !clc.demoplaying && !cl_connectedToCheatServer )
		Cvar_SetCheatState();

	// we will send a usercmd this frame, which
	// will cause the server to send us the first snapshot
	clc.state = CA_PRIMED;

	t2 = Sys_Milliseconds();

	Com_Printf( "CL_InitCGame: %5.2f seconds\n", (t2-t1)/1000.0 );

	// have the renderer touch all its images, so they are present
	// on the card even if the driver does deferred loading
	re.EndRegistration();

	// make sure everything is paged in
	if (!Sys_LowPhysicalMemory()) {
		Com_TouchMemory();
	}

	// clear anything that got printed
	Con_ClearNotify ();
}