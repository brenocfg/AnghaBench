#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sysEvent_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_14__ {int /*<<< orphan*/  integer; int /*<<< orphan*/  modified; } ;
struct TYPE_13__ {scalar_t__ integer; } ;
struct TYPE_12__ {scalar_t__* string; } ;
struct TYPE_11__ {char* string; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* screen_shape ) (int*,int*,int*,int*) ;} ;
struct TYPE_10__ {TYPE_1__ calls; } ;
typedef  TYPE_2__ DeepmindContext ;

/* Variables and functions */
 char* BASEGAME ; 
 int /*<<< orphan*/  CL_Init () ; 
 int /*<<< orphan*/  CL_InitKeyCommands () ; 
 int /*<<< orphan*/  CL_StartHunkUsers (int /*<<< orphan*/ ) ; 
 int CVAR_ARCHIVE ; 
 int CVAR_CHEAT ; 
 int CVAR_INIT ; 
 int CVAR_LATCH ; 
 int CVAR_NORESTART ; 
 int CVAR_PROTECTED ; 
 int CVAR_ROM ; 
 int CVAR_SERVERINFO ; 
 int CVAR_SYSTEMINFO ; 
 int CVAR_TEMP ; 
 int /*<<< orphan*/  Cbuf_Init () ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_CompleteCfgName ; 
 int /*<<< orphan*/  Cmd_Init () ; 
 int /*<<< orphan*/  Cmd_SetCommandCompletionFunc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_AddStartupCommands () ; 
 int /*<<< orphan*/  Com_Crash_f ; 
 int /*<<< orphan*/  Com_DetectAltivec () ; 
 int /*<<< orphan*/  Com_DetectSSE () ; 
 int /*<<< orphan*/  Com_Error_f ; 
 int /*<<< orphan*/  Com_ExecuteCfg () ; 
 int /*<<< orphan*/  Com_Freeze_f ; 
 int /*<<< orphan*/  Com_GameRestart_f ; 
 int /*<<< orphan*/  Com_InitHunkMemory () ; 
 int /*<<< orphan*/  Com_InitJournaling () ; 
 int /*<<< orphan*/  Com_InitPushEvent () ; 
 int /*<<< orphan*/  Com_InitRand () ; 
 int /*<<< orphan*/  Com_InitSmallZoneMemory () ; 
 int /*<<< orphan*/  Com_InitZoneMemory () ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Milliseconds () ; 
 int /*<<< orphan*/  Com_ParseCommandLine (char*) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  Com_Quit_f ; 
 int /*<<< orphan*/  Com_RandomBytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Com_Setenv_f ; 
 int /*<<< orphan*/  Com_StartupVariable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Com_WriteConfig_f ; 
 int /*<<< orphan*/  Cvar_CheckRange (TYPE_7__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* Cvar_Get (char*,char*,int) ; 
 int /*<<< orphan*/  Cvar_Init () ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  Cvar_SetValue (char*,int) ; 
 int /*<<< orphan*/  FS_FCreateOpenPipeFile (scalar_t__*) ; 
 int /*<<< orphan*/  FS_GetCurrentGameDir () ; 
 int /*<<< orphan*/  FS_InitFilesystem () ; 
 char* GAMENAME_FOR_MASTER ; 
 int MAX_QUEUED_EVENTS ; 
 int /*<<< orphan*/  MSG_ReportChangeVectors_f ; 
 int /*<<< orphan*/  Netchan_Init (int) ; 
 int /*<<< orphan*/  PLATFORM_STRING ; 
 int /*<<< orphan*/  PRODUCT_DATE ; 
 int /*<<< orphan*/  PROTOCOL_VERSION ; 
 int /*<<< orphan*/  Q3_VERSION ; 
 int /*<<< orphan*/  SV_Init () ; 
 int /*<<< orphan*/  Sys_Error (char*) ; 
 int /*<<< orphan*/  Sys_Init () ; 
 int /*<<< orphan*/  Sys_InitPIDFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_Init () ; 
 int /*<<< orphan*/  abortframe ; 
 void* cl_packetdelay ; 
 void* cl_paused ; 
 void* com_abnormalExit ; 
 void* com_altivec ; 
 void* com_ansiColor ; 
 void* com_basegame ; 
 void* com_blood ; 
 void* com_buildScript ; 
 void* com_busyWait ; 
 void* com_cameraMode ; 
 void* com_cl_running ; 
 TYPE_7__* com_dedicated ; 
 TYPE_6__* com_developer ; 
 void* com_fixedtime ; 
 int /*<<< orphan*/  com_frameTime ; 
 int /*<<< orphan*/  com_fullyInitialized ; 
 void* com_gamename ; 
 void* com_homepath ; 
 void* com_logToStdErr ; 
 void* com_logfile ; 
 void* com_maxfps ; 
 void* com_maxfpsMinimized ; 
 void* com_maxfpsUnfocused ; 
 void* com_minimized ; 
 TYPE_5__* com_pipefile ; 
 TYPE_4__* com_protocol ; 
 void* com_showtrace ; 
 void* com_speeds ; 
 void* com_standalone ; 
 void* com_sv_running ; 
 void* com_timedemo ; 
 void* com_timescale ; 
 void* com_unfocused ; 
 void* com_version ; 
 void* com_writeConfig ; 
 void* con_autochat ; 
 int cvar_modifiedFlags ; 
 TYPE_2__* dmlab_context () ; 
 int /*<<< orphan*/ * eventQueue ; 
 int /*<<< orphan*/  pipefile ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int*,int*) ; 
 void* sv_packetdelay ; 
 void* sv_paused ; 
 char* va (char*,int /*<<< orphan*/ ,...) ; 

void Com_Init( char *commandLine ) {
	DeepmindContext* ctx = dmlab_context();
	int width, height, buff_width, buff_height;
	char	*s;
	int	qport;

	Com_Printf( "%s %s %s\n", Q3_VERSION, PLATFORM_STRING, PRODUCT_DATE );

	if ( setjmp (abortframe) ) {
		Sys_Error ("Error during initialization");
	}

	// Clear queues
	Com_Memset( &eventQueue[ 0 ], 0, MAX_QUEUED_EVENTS * sizeof( sysEvent_t ) );

	// initialize the weak pseudo-random number generator for use later.
	Com_InitRand();

	// do this before anything else decides to push events
	Com_InitPushEvent();

	Com_InitSmallZoneMemory();
	Cvar_Init ();

	// prepare enough of the subsystems to handle
	// cvar and command buffer management
	Com_ParseCommandLine( commandLine );

//	Swap_Init ();
	Cbuf_Init ();

	Com_DetectSSE();

	// override anything from the config files with command line args
	Com_StartupVariable( NULL );

	Com_InitZoneMemory();
	Cmd_Init ();

	// get the developer cvar set as early as possible
	com_developer = Cvar_Get("developer", "0", CVAR_TEMP);

	// done early so bind command exists
	CL_InitKeyCommands();

	com_standalone = Cvar_Get("com_standalone", "0", CVAR_ROM);
	com_basegame = Cvar_Get("com_basegame", BASEGAME, CVAR_INIT);
	com_homepath = Cvar_Get("com_homepath", "", CVAR_INIT|CVAR_PROTECTED);

	FS_InitFilesystem ();

	Com_InitJournaling();

	// Add some commands here already so users can use them from config files
	Cmd_AddCommand ("setenv", Com_Setenv_f);
	if (com_developer && com_developer->integer)
	{
		Cmd_AddCommand ("error", Com_Error_f);
		Cmd_AddCommand ("crash", Com_Crash_f);
		Cmd_AddCommand ("freeze", Com_Freeze_f);
	}
	Cmd_AddCommand ("quit", Com_Quit_f);
	Cmd_AddCommand ("changeVectors", MSG_ReportChangeVectors_f );
	Cmd_AddCommand ("writeconfig", Com_WriteConfig_f );
	Cmd_SetCommandCompletionFunc( "writeconfig", Cmd_CompleteCfgName );
	Cmd_AddCommand("game_restart", Com_GameRestart_f);

	Com_ExecuteCfg();

	// override anything from the config files with command line args
	Com_StartupVariable( NULL );

  // get dedicated here for proper hunk megs initialization
#ifdef DEDICATED
	com_dedicated = Cvar_Get ("dedicated", "1", CVAR_INIT);
	Cvar_CheckRange( com_dedicated, 1, 2, qtrue );
#else
	com_dedicated = Cvar_Get ("dedicated", "0", CVAR_LATCH);
	Cvar_CheckRange( com_dedicated, 0, 2, qtrue );
#endif
	// allocate the stack based hunk allocator
	Com_InitHunkMemory();

	// if any archived cvars are modified after this, we will trigger a writing
	// of the config file
	cvar_modifiedFlags &= ~CVAR_ARCHIVE;

	//
	// init commands and vars
	//
	com_altivec = Cvar_Get ("com_altivec", "1", CVAR_ARCHIVE);
	com_maxfps = Cvar_Get ("com_maxfps", "85", CVAR_ARCHIVE);
	com_blood = Cvar_Get ("com_blood", "1", CVAR_ARCHIVE);

	com_logfile = Cvar_Get ("logfile", "0", CVAR_TEMP );

	com_timescale = Cvar_Get ("timescale", "1", CVAR_CHEAT | CVAR_SYSTEMINFO );
	com_fixedtime = Cvar_Get ("fixedtime", "0", CVAR_CHEAT);
	com_showtrace = Cvar_Get ("com_showtrace", "0", CVAR_CHEAT);
	com_speeds = Cvar_Get ("com_speeds", "0", 0);
	com_timedemo = Cvar_Get ("timedemo", "0", CVAR_CHEAT);
	com_cameraMode = Cvar_Get ("com_cameraMode", "0", CVAR_CHEAT);

	cl_paused = Cvar_Get ("cl_paused", "0", CVAR_ROM);
	sv_paused = Cvar_Get ("sv_paused", "0", CVAR_ROM);
	cl_packetdelay = Cvar_Get ("cl_packetdelay", "0", CVAR_CHEAT);
	sv_packetdelay = Cvar_Get ("sv_packetdelay", "0", CVAR_CHEAT);
	com_sv_running = Cvar_Get ("sv_running", "0", CVAR_ROM);
	com_cl_running = Cvar_Get ("cl_running", "0", CVAR_ROM);
	com_buildScript = Cvar_Get( "com_buildScript", "0", 0 );
	com_ansiColor = Cvar_Get( "com_ansiColor", "0", CVAR_ARCHIVE );
  com_logToStdErr = Cvar_Get( "com_logToStdErr", "0", CVAR_ARCHIVE );

	com_unfocused = Cvar_Get( "com_unfocused", "0", CVAR_ROM );
	com_maxfpsUnfocused = Cvar_Get( "com_maxfpsUnfocused", "0", CVAR_ARCHIVE );
	com_minimized = Cvar_Get( "com_minimized", "0", CVAR_ROM );
	com_maxfpsMinimized = Cvar_Get( "com_maxfpsMinimized", "0", CVAR_ARCHIVE );
	com_abnormalExit = Cvar_Get( "com_abnormalExit", "0", CVAR_ROM );
	com_busyWait = Cvar_Get("com_busyWait", "0", CVAR_ARCHIVE);
	com_writeConfig = Cvar_Get("com_writeConfig", "1", CVAR_ARCHIVE);
	Cvar_Get("com_errorMessage", "", CVAR_ROM | CVAR_NORESTART);

#ifdef CINEMATICS_INTRO
	com_introPlayed = Cvar_Get( "com_introplayed", "0", CVAR_ARCHIVE);
#endif

	s = va("%s %s %s", Q3_VERSION, PLATFORM_STRING, PRODUCT_DATE );
	com_version = Cvar_Get ("version", s, CVAR_ROM | CVAR_SERVERINFO );
	com_gamename = Cvar_Get("com_gamename", GAMENAME_FOR_MASTER, CVAR_SERVERINFO | CVAR_INIT);
	com_protocol = Cvar_Get("com_protocol", va("%i", PROTOCOL_VERSION), CVAR_SERVERINFO | CVAR_INIT);
#ifdef LEGACY_PROTOCOL
	com_legacyprotocol = Cvar_Get("com_legacyprotocol", va("%i", PROTOCOL_LEGACY_VERSION), CVAR_INIT);

	// Keep for compatibility with old mods / mods that haven't updated yet.
	if(com_legacyprotocol->integer > 0)
		Cvar_Get("protocol", com_legacyprotocol->string, CVAR_ROM);
	else
#endif
		Cvar_Get("protocol", com_protocol->string, CVAR_ROM);

#ifndef DEDICATED
	con_autochat = Cvar_Get("con_autochat", "1", CVAR_ARCHIVE);
#endif

	Sys_Init();

	Sys_InitPIDFile( FS_GetCurrentGameDir() );

	// Pick a random port value
	Com_RandomBytes( (byte*)&qport, sizeof(int) );
	Netchan_Init( qport & 0xffff );

	VM_Init();
	SV_Init();

	com_dedicated->modified = qfalse;
#ifndef DEDICATED
	ctx->calls.screen_shape(&width, &height, &buff_width, &buff_height);
	Cvar_SetValue("r_customwidth", width);
	Cvar_SetValue("r_customheight", height);
	Cvar_SetValue("r_buffwidth", buff_width);
	Cvar_SetValue("r_buffheight", buff_height);
	Cvar_Set("r_mode", "-1");
	CL_Init();
#endif

	// set com_frameTime so that if a map is started on the
	// command line it will still be able to count on com_frameTime
	// being random enough for a serverid
	com_frameTime = Com_Milliseconds();

	// add + commands from command line
	if ( !Com_AddStartupCommands() ) {
		// if the user didn't give any commands, run default action
		if ( !com_dedicated->integer ) {
#ifdef CINEMATICS_LOGO
			Cbuf_AddText ("cinematic " CINEMATICS_LOGO "\n");
#endif
#ifdef CINEMATICS_INTRO
			if( !com_introPlayed->integer ) {
				Cvar_Set( com_introPlayed->name, "1" );
				Cvar_Set( "nextmap", "cinematic " CINEMATICS_INTRO );
			}
#endif
		}
	}

	// start in full screen ui mode
	Cvar_Set("r_uiFullScreen", "1");

	CL_StartHunkUsers( qfalse );

	// make sure single player is off by default
	Cvar_Set("ui_singlePlayerActive", "0");

	com_fullyInitialized = qtrue;

	// always set the cvar, but only print the info if it makes sense.
	Com_DetectAltivec();
#if idppc
	Com_Printf ("Altivec support is %s\n", com_altivec->integer ? "enabled" : "disabled");
#endif

	com_pipefile = Cvar_Get( "com_pipefile", "", CVAR_ARCHIVE|CVAR_LATCH );
	if( com_pipefile->string[0] )
	{
		pipefile = FS_FCreateOpenPipeFile( com_pipefile->string );
	}

	Com_Printf ("--- Common Initialization Complete ---\n");
}