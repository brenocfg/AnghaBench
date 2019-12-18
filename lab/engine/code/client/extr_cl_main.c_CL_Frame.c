#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  TYPE_1__ qtime_t ;
typedef  int /*<<< orphan*/  mapName ;
struct TYPE_23__ {int value; scalar_t__ integer; } ;
struct TYPE_22__ {scalar_t__ integer; } ;
struct TYPE_21__ {scalar_t__ integer; } ;
struct TYPE_20__ {scalar_t__ state; float aviVideoFrameRemainder; scalar_t__ demorecording; int /*<<< orphan*/  servername; int /*<<< orphan*/  demoplaying; scalar_t__ cURLDisconnected; scalar_t__ downloadCURLM; } ;
struct TYPE_19__ {int realFrametime; int frametime; int realtime; int /*<<< orphan*/  framecount; scalar_t__ cddialog; } ;
struct TYPE_18__ {int /*<<< orphan*/  integer; } ;
struct TYPE_17__ {int /*<<< orphan*/  integer; } ;
struct TYPE_16__ {int value; } ;
struct TYPE_14__ {int /*<<< orphan*/  mapname; } ;
struct TYPE_13__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  CL_CaptureVoip () ; 
 int /*<<< orphan*/  CL_CheckForResend () ; 
 int /*<<< orphan*/  CL_CheckTimeout () ; 
 int /*<<< orphan*/  CL_CheckUserinfo () ; 
 int /*<<< orphan*/  CL_SendCmd () ; 
 int /*<<< orphan*/  CL_SetCGameTime () ; 
 int /*<<< orphan*/  CL_StopRecord_f () ; 
 int /*<<< orphan*/  CL_TakeVideoFrame () ; 
 int /*<<< orphan*/  CL_UpdateMumble () ; 
 scalar_t__ CL_VideoRecording () ; 
 int /*<<< orphan*/  CL_cURL_PerformDownload () ; 
 int /*<<< orphan*/  COM_SkipPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COM_StripExtension (char*,char*,int) ; 
 int /*<<< orphan*/  Cbuf_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_RealTime (TYPE_1__*) ; 
 int /*<<< orphan*/  Con_RunConsole () ; 
 int /*<<< orphan*/  EXEC_NOW ; 
 int KEYCATCH_UI ; 
 int Key_GetCatcher () ; 
 float MAX (float,float) ; 
 int MAX_OSPATH ; 
 int MAX_QPATH ; 
 float MIN (int,float) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCR_DebugGraph (double) ; 
 int /*<<< orphan*/  SCR_RunCinematic () ; 
 int /*<<< orphan*/  SCR_UpdateScreen () ; 
 int /*<<< orphan*/  S_StopAllSounds () ; 
 int /*<<< orphan*/  S_Update () ; 
 int /*<<< orphan*/  UIMENU_MAIN ; 
 int /*<<< orphan*/  UIMENU_NEED_CD ; 
 int /*<<< orphan*/  UI_SET_ACTIVE_MENU ; 
 int /*<<< orphan*/  VM_Call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_11__ cl ; 
 TYPE_10__* cl_autoRecordDemo ; 
 TYPE_9__* cl_aviFrameRate ; 
 TYPE_8__* cl_forceavidemo ; 
 TYPE_7__* cl_timegraph ; 
 TYPE_6__ clc ; 
 TYPE_5__ cls ; 
 TYPE_4__* com_cl_running ; 
 TYPE_3__* com_sv_running ; 
 TYPE_2__* com_timescale ; 
 scalar_t__ qfalse ; 
 char* strstr (char*,char*) ; 
 scalar_t__ uivm ; 
 char* va (char*,char*,char*,char*,...) ; 

void CL_Frame ( int msec ) {

	if ( !com_cl_running->integer ) {
		return;
	}

#ifdef USE_CURL
	if(clc.downloadCURLM) {
		CL_cURL_PerformDownload();
		// we can't process frames normally when in disconnected
		// download mode since the ui vm expects clc.state to be
		// CA_CONNECTED
		if(clc.cURLDisconnected) {
			cls.realFrametime = msec;
			cls.frametime = msec;
			cls.realtime += cls.frametime;
			SCR_UpdateScreen();
			S_Update();
			Con_RunConsole();
			cls.framecount++;
			return;
		}
	}
#endif

	if ( cls.cddialog ) {
		// bring up the cd error dialog if needed
		cls.cddialog = qfalse;
		VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_NEED_CD );
	} else	if ( clc.state == CA_DISCONNECTED && !( Key_GetCatcher( ) & KEYCATCH_UI )
		&& !com_sv_running->integer && uivm ) {
		// if disconnected, bring up the menu
		S_StopAllSounds();
		VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_MAIN );
	}

	// if recording an avi, lock to a fixed fps
	if ( CL_VideoRecording( ) && cl_aviFrameRate->integer && msec) {
		// save the current screen
		if ( clc.state == CA_ACTIVE || cl_forceavidemo->integer) {
			float fps = MIN(cl_aviFrameRate->value * com_timescale->value, 1000.0f);
			float frameDuration = MAX(1000.0f / fps, 1.0f) + clc.aviVideoFrameRemainder;

			CL_TakeVideoFrame( );

			msec = (int)frameDuration;
			clc.aviVideoFrameRemainder = frameDuration - msec;
		}
	}
	
	if( cl_autoRecordDemo->integer ) {
		if( clc.state == CA_ACTIVE && !clc.demorecording && !clc.demoplaying ) {
			// If not recording a demo, and we should be, start one
			qtime_t	now;
			char		*nowString;
			char		*p;
			char		mapName[ MAX_QPATH ];
			char		serverName[ MAX_OSPATH ];

			Com_RealTime( &now );
			nowString = va( "%04d%02d%02d%02d%02d%02d",
					1900 + now.tm_year,
					1 + now.tm_mon,
					now.tm_mday,
					now.tm_hour,
					now.tm_min,
					now.tm_sec );

			Q_strncpyz( serverName, clc.servername, MAX_OSPATH );
			// Replace the ":" in the address as it is not a valid
			// file name character
			p = strstr( serverName, ":" );
			if( p ) {
				*p = '.';
			}

			Q_strncpyz( mapName, COM_SkipPath( cl.mapname ), sizeof( cl.mapname ) );
			COM_StripExtension(mapName, mapName, sizeof(mapName));

			Cbuf_ExecuteText( EXEC_NOW,
					va( "record %s-%s-%s", nowString, serverName, mapName ) );
		}
		else if( clc.state != CA_ACTIVE && clc.demorecording ) {
			// Recording, but not CA_ACTIVE, so stop recording
			CL_StopRecord_f( );
		}
	}

	// save the msec before checking pause
	cls.realFrametime = msec;

	// decide the simulation time
	cls.frametime = msec;

	cls.realtime += cls.frametime;

	if ( cl_timegraph->integer ) {
		SCR_DebugGraph ( cls.realFrametime * 0.25 );
	}

	// see if we need to update any userinfo
	CL_CheckUserinfo();

	// if we haven't gotten a packet in a long time,
	// drop the connection
	CL_CheckTimeout();

	// send intentions now
	CL_SendCmd();

	// resend a connection request if necessary
	CL_CheckForResend();

	// decide on the serverTime to render
	CL_SetCGameTime();

	// update the screen
	SCR_UpdateScreen();

	// update audio
	S_Update();

#ifdef USE_VOIP
	CL_CaptureVoip();
#endif

#ifdef USE_MUMBLE
	CL_UpdateMumble();
#endif

	// advance local effects for next frame
	SCR_RunCinematic();

	Con_RunConsole();

	cls.framecount++;
}