#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  state; } ;
struct TYPE_14__ {scalar_t__ realtime; } ;
struct TYPE_13__ {int /*<<< orphan*/  integer; } ;
struct TYPE_12__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_DISCONNECTED ; 
 int /*<<< orphan*/  CL_ClearState () ; 
 int /*<<< orphan*/  CL_Clientinfo_f ; 
 int /*<<< orphan*/  CL_CompleteDemoName ; 
 int /*<<< orphan*/  CL_CompletePlayerName ; 
 int /*<<< orphan*/  CL_CompleteRcon ; 
 int /*<<< orphan*/  CL_Configstrings_f ; 
 int /*<<< orphan*/  CL_Connect_f ; 
 int /*<<< orphan*/  CL_Disconnect_f ; 
 int /*<<< orphan*/  CL_ForwardToServer_f ; 
 int /*<<< orphan*/  CL_GenerateQKey () ; 
 int /*<<< orphan*/  CL_GlobalServers_f ; 
 int /*<<< orphan*/  CL_InitInput () ; 
 int /*<<< orphan*/  CL_InitRef () ; 
 int /*<<< orphan*/  CL_LocalServers_f ; 
 int /*<<< orphan*/  CL_OpenedPK3List_f ; 
 int /*<<< orphan*/  CL_Ping_f ; 
 int /*<<< orphan*/  CL_PlayCinematic_f ; 
 int /*<<< orphan*/  CL_PlayDemo_f ; 
 int /*<<< orphan*/  CL_Rcon_f ; 
 int /*<<< orphan*/  CL_Reconnect_f ; 
 int /*<<< orphan*/  CL_Record_f ; 
 int /*<<< orphan*/  CL_ReferencedPK3List_f ; 
 int /*<<< orphan*/  CL_Sayto_f ; 
 int /*<<< orphan*/  CL_ServerStatus_f ; 
 int /*<<< orphan*/  CL_SetModel_f ; 
 int /*<<< orphan*/  CL_ShowIP_f ; 
 int /*<<< orphan*/  CL_Snd_Restart_f ; 
 int /*<<< orphan*/  CL_StopRecord_f ; 
 int /*<<< orphan*/  CL_StopVideo_f ; 
 int /*<<< orphan*/  CL_UpdateCustomItems_f ; 
 int /*<<< orphan*/  CL_UpdateGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_Vid_Restart_f ; 
 int /*<<< orphan*/  CL_Video_f ; 
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int CVAR_PROTECTED ; 
 int CVAR_ROM ; 
 int CVAR_SERVERINFO ; 
 int CVAR_TEMP ; 
 int CVAR_USERINFO ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_SetCommandCompletionFunc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Con_Init () ; 
 int /*<<< orphan*/  Cvar_CheckRange (TYPE_1__*,float,int,int /*<<< orphan*/ ) ; 
 void* Cvar_Get (char*,char*,int) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 char* DEFAULT_CURL_LIB ; 
 int MAX_JOYSTICK_AXIS ; 
 int /*<<< orphan*/  SCR_Init () ; 
 void* cl_activeAction ; 
 void* cl_allowDownload ; 
 void* cl_anglespeedkey ; 
 void* cl_autoRecordDemo ; 
 void* cl_aviFrameRate ; 
 void* cl_aviMotionJpeg ; 
 void* cl_cURLLib ; 
 void* cl_conXOffset ; 
 void* cl_consoleKeys ; 
 void* cl_forceavidemo ; 
 void* cl_freelook ; 
 void* cl_freezeDemo ; 
 void* cl_guidServerUniq ; 
 void* cl_inGameVideo ; 
 void* cl_lanForcePackets ; 
 void* cl_maxpackets ; 
 void* cl_motd ; 
 void* cl_motdString ; 
 void* cl_mouseAccel ; 
 TYPE_1__* cl_mouseAccelOffset ; 
 void* cl_mouseAccelStyle ; 
 void* cl_mumbleScale ; 
 void* cl_noprint ; 
 int /*<<< orphan*/  cl_oldGameSet ; 
 void* cl_packetdup ; 
 void* cl_pitchspeed ; 
 void* cl_rate ; 
 void* cl_run ; 
 void* cl_sensitivity ; 
 void* cl_serverStatusResendTime ; 
 void* cl_showMouseRate ; 
 void* cl_showSend ; 
 void* cl_showTimeDelta ; 
 void* cl_shownet ; 
 void* cl_timeNudge ; 
 void* cl_timedemo ; 
 void* cl_timedemoLog ; 
 void* cl_timeout ; 
 void* cl_useMumble ; 
 TYPE_1__* cl_voip ; 
 void* cl_voipCaptureMult ; 
 void* cl_voipGainDuringCapture ; 
 void* cl_voipProtocol ; 
 void* cl_voipSend ; 
 void* cl_voipSendTarget ; 
 void* cl_voipShowMeter ; 
 void* cl_voipUseVAD ; 
 void* cl_voipVADThreshold ; 
 void* cl_yawspeed ; 
 TYPE_8__ clc ; 
 TYPE_7__ cls ; 
 TYPE_6__* com_dedicated ; 
 int /*<<< orphan*/  com_fullyInitialized ; 
 void* j_forward ; 
 TYPE_1__* j_forward_axis ; 
 void* j_pitch ; 
 TYPE_1__* j_pitch_axis ; 
 void* j_side ; 
 TYPE_1__* j_side_axis ; 
 void* j_up ; 
 TYPE_1__* j_up_axis ; 
 void* j_yaw ; 
 TYPE_1__* j_yaw_axis ; 
 void* m_filter ; 
 void* m_forward ; 
 void* m_pitch ; 
 void* m_side ; 
 void* m_yaw ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 void* rconAddress ; 
 void* rcon_client_password ; 

void CL_Init( void ) {
	Com_Printf( "----- Client Initialization -----\n" );

	Con_Init ();

	if(!com_fullyInitialized)
	{
		CL_ClearState();
		clc.state = CA_DISCONNECTED;	// no longer CA_UNINITIALIZED
		cl_oldGameSet = qfalse;
	}

	cls.realtime = 0;

	CL_InitInput ();

	//
	// register our variables
	//
	cl_noprint = Cvar_Get( "cl_noprint", "0", 0 );
#ifdef UPDATE_SERVER_NAME
	cl_motd = Cvar_Get ("cl_motd", "1", 0);
#endif

	cl_timeout = Cvar_Get ("cl_timeout", "200", 0);

	cl_timeNudge = Cvar_Get ("cl_timeNudge", "0", CVAR_TEMP );
	cl_shownet = Cvar_Get ("cl_shownet", "0", CVAR_TEMP );
	cl_showSend = Cvar_Get ("cl_showSend", "0", CVAR_TEMP );
	cl_showTimeDelta = Cvar_Get ("cl_showTimeDelta", "0", CVAR_TEMP );
	cl_freezeDemo = Cvar_Get ("cl_freezeDemo", "0", CVAR_TEMP );
	rcon_client_password = Cvar_Get ("rconPassword", "", CVAR_TEMP );
	cl_activeAction = Cvar_Get( "activeAction", "", CVAR_TEMP );

	cl_timedemo = Cvar_Get ("timedemo", "0", 0);
	cl_timedemoLog = Cvar_Get ("cl_timedemoLog", "", CVAR_ARCHIVE);
	cl_autoRecordDemo = Cvar_Get ("cl_autoRecordDemo", "0", CVAR_ARCHIVE);
	cl_aviFrameRate = Cvar_Get ("cl_aviFrameRate", "25", CVAR_ARCHIVE);
	cl_aviMotionJpeg = Cvar_Get ("cl_aviMotionJpeg", "1", CVAR_ARCHIVE);
	cl_forceavidemo = Cvar_Get ("cl_forceavidemo", "0", 0);

	rconAddress = Cvar_Get ("rconAddress", "", 0);

	cl_yawspeed = Cvar_Get ("cl_yawspeed", "140", CVAR_ARCHIVE);
	cl_pitchspeed = Cvar_Get ("cl_pitchspeed", "140", CVAR_ARCHIVE);
	cl_anglespeedkey = Cvar_Get ("cl_anglespeedkey", "1.5", 0);

	cl_maxpackets = Cvar_Get ("cl_maxpackets", "30", CVAR_ARCHIVE );
	cl_packetdup = Cvar_Get ("cl_packetdup", "1", CVAR_ARCHIVE );

	cl_run = Cvar_Get ("cl_run", "1", CVAR_ARCHIVE);
	cl_sensitivity = Cvar_Get ("sensitivity", "5", CVAR_ARCHIVE);
	cl_mouseAccel = Cvar_Get ("cl_mouseAccel", "0", CVAR_ARCHIVE);
	cl_freelook = Cvar_Get( "cl_freelook", "1", CVAR_ARCHIVE );

	// 0: legacy mouse acceleration
	// 1: new implementation
	cl_mouseAccelStyle = Cvar_Get( "cl_mouseAccelStyle", "0", CVAR_ARCHIVE );
	// offset for the power function (for style 1, ignored otherwise)
	// this should be set to the max rate value
	cl_mouseAccelOffset = Cvar_Get( "cl_mouseAccelOffset", "5", CVAR_ARCHIVE );
	Cvar_CheckRange(cl_mouseAccelOffset, 0.001f, 50000.0f, qfalse);

	cl_showMouseRate = Cvar_Get ("cl_showmouserate", "0", 0);

	cl_allowDownload = Cvar_Get ("cl_allowDownload", "0", CVAR_ARCHIVE);
#ifdef USE_CURL_DLOPEN
	cl_cURLLib = Cvar_Get("cl_cURLLib", DEFAULT_CURL_LIB, CVAR_ARCHIVE | CVAR_PROTECTED);
#endif

	cl_conXOffset = Cvar_Get ("cl_conXOffset", "0", 0);
#ifdef __APPLE__
	// In game video is REALLY slow in Mac OS X right now due to driver slowness
	cl_inGameVideo = Cvar_Get ("r_inGameVideo", "0", CVAR_ARCHIVE);
#else
	cl_inGameVideo = Cvar_Get ("r_inGameVideo", "1", CVAR_ARCHIVE);
#endif

	cl_serverStatusResendTime = Cvar_Get ("cl_serverStatusResendTime", "750", 0);

	// init autoswitch so the ui will have it correctly even
	// if the cgame hasn't been started
	Cvar_Get ("cg_autoswitch", "1", CVAR_ARCHIVE);

	m_pitch = Cvar_Get ("m_pitch", "0.022", CVAR_ARCHIVE);
	m_yaw = Cvar_Get ("m_yaw", "0.022", CVAR_ARCHIVE);
	m_forward = Cvar_Get ("m_forward", "0.25", CVAR_ARCHIVE);
	m_side = Cvar_Get ("m_side", "0.25", CVAR_ARCHIVE);
#ifdef __APPLE__
	// Input is jittery on OS X w/o this
	m_filter = Cvar_Get ("m_filter", "1", CVAR_ARCHIVE);
#else
	m_filter = Cvar_Get ("m_filter", "0", CVAR_ARCHIVE);
#endif

	j_pitch =        Cvar_Get ("j_pitch",        "0.022", CVAR_ARCHIVE);
	j_yaw =          Cvar_Get ("j_yaw",          "-0.022", CVAR_ARCHIVE);
	j_forward =      Cvar_Get ("j_forward",      "-0.25", CVAR_ARCHIVE);
	j_side =         Cvar_Get ("j_side",         "0.25", CVAR_ARCHIVE);
	j_up =           Cvar_Get ("j_up",           "0", CVAR_ARCHIVE);

	j_pitch_axis =   Cvar_Get ("j_pitch_axis",   "3", CVAR_ARCHIVE);
	j_yaw_axis =     Cvar_Get ("j_yaw_axis",     "2", CVAR_ARCHIVE);
	j_forward_axis = Cvar_Get ("j_forward_axis", "1", CVAR_ARCHIVE);
	j_side_axis =    Cvar_Get ("j_side_axis",    "0", CVAR_ARCHIVE);
	j_up_axis =      Cvar_Get ("j_up_axis",      "4", CVAR_ARCHIVE);

	Cvar_CheckRange(j_pitch_axis, 0, MAX_JOYSTICK_AXIS-1, qtrue);
	Cvar_CheckRange(j_yaw_axis, 0, MAX_JOYSTICK_AXIS-1, qtrue);
	Cvar_CheckRange(j_forward_axis, 0, MAX_JOYSTICK_AXIS-1, qtrue);
	Cvar_CheckRange(j_side_axis, 0, MAX_JOYSTICK_AXIS-1, qtrue);
	Cvar_CheckRange(j_up_axis, 0, MAX_JOYSTICK_AXIS-1, qtrue);

	cl_motdString = Cvar_Get( "cl_motdString", "", CVAR_ROM );

	Cvar_Get( "cl_maxPing", "800", CVAR_ARCHIVE );

	cl_lanForcePackets = Cvar_Get ("cl_lanForcePackets", "1", CVAR_ARCHIVE);

	cl_guidServerUniq = Cvar_Get ("cl_guidServerUniq", "1", CVAR_ARCHIVE);

	// ~ and `, as keys and characters
	cl_consoleKeys = Cvar_Get( "cl_consoleKeys", "~ ` 0x7e 0x60", CVAR_ARCHIVE);

	// userinfo
	Cvar_Get ("name", "UnnamedPlayer", CVAR_USERINFO | CVAR_ARCHIVE );
	cl_rate = Cvar_Get ("rate", "25000", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("snaps", "20", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("model", "sarge", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("headmodel", "sarge", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("team_model", "james", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("team_headmodel", "*james", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("g_redTeam", "Stroggs", CVAR_SERVERINFO | CVAR_ARCHIVE);
	Cvar_Get ("g_blueTeam", "Pagans", CVAR_SERVERINFO | CVAR_ARCHIVE);
	Cvar_Get ("color1",  "4", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("color2", "5", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("handicap", "100", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("teamtask", "0", CVAR_USERINFO );
	Cvar_Get ("sex", "male", CVAR_USERINFO | CVAR_ARCHIVE );
	Cvar_Get ("cl_anonymous", "0", CVAR_USERINFO | CVAR_ARCHIVE );

	Cvar_Get ("password", "", CVAR_USERINFO);
	Cvar_Get ("cg_predictItems", "1", CVAR_USERINFO | CVAR_ARCHIVE );

#ifdef USE_MUMBLE
	cl_useMumble = Cvar_Get ("cl_useMumble", "0", CVAR_ARCHIVE | CVAR_LATCH);
	cl_mumbleScale = Cvar_Get ("cl_mumbleScale", "0.0254", CVAR_ARCHIVE);
#endif

#ifdef USE_VOIP
	cl_voipSend = Cvar_Get ("cl_voipSend", "0", 0);
	cl_voipSendTarget = Cvar_Get ("cl_voipSendTarget", "spatial", 0);
	cl_voipGainDuringCapture = Cvar_Get ("cl_voipGainDuringCapture", "0.2", CVAR_ARCHIVE);
	cl_voipCaptureMult = Cvar_Get ("cl_voipCaptureMult", "2.0", CVAR_ARCHIVE);
	cl_voipUseVAD = Cvar_Get ("cl_voipUseVAD", "0", CVAR_ARCHIVE);
	cl_voipVADThreshold = Cvar_Get ("cl_voipVADThreshold", "0.25", CVAR_ARCHIVE);
	cl_voipShowMeter = Cvar_Get ("cl_voipShowMeter", "1", CVAR_ARCHIVE);

	cl_voip = Cvar_Get ("cl_voip", "1", CVAR_ARCHIVE);
	Cvar_CheckRange( cl_voip, 0, 1, qtrue );
	cl_voipProtocol = Cvar_Get ("cl_voipProtocol", cl_voip->integer ? "opus" : "", CVAR_USERINFO | CVAR_ROM);
#endif


	// cgame might not be initialized before menu is used
	Cvar_Get ("cg_viewsize", "100", CVAR_ARCHIVE );
	// Make sure cg_stereoSeparation is zero as that variable is deprecated and should not be used anymore.
	Cvar_Get ("cg_stereoSeparation", "0", CVAR_ROM);

	//
	// register our commands
	//
	Cmd_AddCommand ("cmd", CL_ForwardToServer_f);
	Cmd_AddCommand ("configstrings", CL_Configstrings_f);
	Cmd_AddCommand ("clientinfo", CL_Clientinfo_f);
	Cmd_AddCommand ("snd_restart", CL_Snd_Restart_f);
	Cmd_AddCommand ("vid_restart", CL_Vid_Restart_f);
	Cmd_AddCommand ("disconnect", CL_Disconnect_f);
	Cmd_AddCommand ("record", CL_Record_f);
	Cmd_AddCommand ("demo", CL_PlayDemo_f);
	Cmd_SetCommandCompletionFunc( "demo", CL_CompleteDemoName );
	Cmd_AddCommand ("cinematic", CL_PlayCinematic_f);
	Cmd_AddCommand ("stoprecord", CL_StopRecord_f);
	Cmd_AddCommand ("connect", CL_Connect_f);
	Cmd_AddCommand ("reconnect", CL_Reconnect_f);
	Cmd_AddCommand ("localservers", CL_LocalServers_f);
	Cmd_AddCommand ("globalservers", CL_GlobalServers_f);
	Cmd_AddCommand ("rcon", CL_Rcon_f);
	Cmd_SetCommandCompletionFunc( "rcon", CL_CompleteRcon );
	Cmd_AddCommand ("ping", CL_Ping_f );
	Cmd_AddCommand ("serverstatus", CL_ServerStatus_f );
	Cmd_AddCommand ("showip", CL_ShowIP_f );
	Cmd_AddCommand ("fs_openedList", CL_OpenedPK3List_f );
	Cmd_AddCommand ("fs_referencedList", CL_ReferencedPK3List_f );
	Cmd_AddCommand ("model", CL_SetModel_f );
	Cmd_AddCommand ("video", CL_Video_f );
	Cmd_AddCommand ("stopvideo", CL_StopVideo_f );
	Cmd_AddCommand ("updatecustomitems", CL_UpdateCustomItems_f );
	if( !com_dedicated->integer ) {
		Cmd_AddCommand ("sayto", CL_Sayto_f );
		Cmd_SetCommandCompletionFunc( "sayto", CL_CompletePlayerName );
	}
	CL_InitRef();

	SCR_Init ();

//	Cbuf_Execute ();

	Cvar_Set( "cl_running", "1" );

	CL_GenerateQKey();
	Cvar_Get( "cl_guid", "", CVAR_USERINFO | CVAR_ROM );
	CL_UpdateGUID( NULL, 0 );

	Com_Printf( "----- Client Initialization Complete -----\n" );
}