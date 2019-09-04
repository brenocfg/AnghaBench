#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int integer; } ;
struct TYPE_23__ {int integer; } ;
struct TYPE_22__ {int integer; } ;
struct TYPE_21__ {scalar_t__ integer; } ;
struct TYPE_20__ {scalar_t__ integer; } ;
struct TYPE_19__ {scalar_t__ integer; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_17__ {int /*<<< orphan*/  integer; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_15__ {void* modified; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {scalar_t__ integer; void* modified; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_FlushMemory () ; 
 int /*<<< orphan*/  CL_Frame (int) ; 
 int /*<<< orphan*/  Cbuf_Execute () ; 
 int /*<<< orphan*/  Com_DetectAltivec () ; 
 int Com_EventLoop () ; 
 int Com_ModifyMsec (int) ; 
 int /*<<< orphan*/  Com_Printf (char*,int,int,int,int,...) ; 
 int /*<<< orphan*/  Com_ReadFromPipe () ; 
 int Com_TimeVal (int) ; 
 int /*<<< orphan*/  Com_WriteConfiguration () ; 
 int /*<<< orphan*/  Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_Frame () ; 
 int /*<<< orphan*/  NET_FlushPacketQueue () ; 
 int /*<<< orphan*/  NET_Sleep (int) ; 
 int /*<<< orphan*/  SV_Frame (int) ; 
 int SV_FrameMsec () ; 
 int SV_SendQueuedPackets () ; 
 int /*<<< orphan*/  SV_Shutdown (char*) ; 
 int Sys_Milliseconds () ; 
 int /*<<< orphan*/  abortframe ; 
 TYPE_12__* com_altivec ; 
 TYPE_11__* com_busyWait ; 
 TYPE_10__* com_dedicated ; 
 int /*<<< orphan*/  com_frameNumber ; 
 int com_frameTime ; 
 TYPE_9__* com_maxfps ; 
 TYPE_8__* com_maxfpsMinimized ; 
 TYPE_7__* com_maxfpsUnfocused ; 
 TYPE_6__* com_minimized ; 
 TYPE_5__* com_showtrace ; 
 TYPE_4__* com_speeds ; 
 TYPE_3__* com_sv_running ; 
 TYPE_2__* com_timedemo ; 
 TYPE_1__* com_unfocused ; 
 void* qfalse ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 scalar_t__ time_backend ; 
 scalar_t__ time_frontend ; 
 scalar_t__ time_game ; 

void Com_Frame( void ) {

	int		msec, minMsec;
	int		timeVal, timeValSV;
	static int	lastTime = 0, bias = 0;
 
	int		timeBeforeFirstEvents;
	int		timeBeforeServer;
	int		timeBeforeEvents;
	int		timeBeforeClient;
	int		timeAfter;
  

	if ( setjmp (abortframe) ) {
		return;			// an ERR_DROP was thrown
	}

	timeBeforeFirstEvents =0;
	timeBeforeServer =0;
	timeBeforeEvents =0;
	timeBeforeClient = 0;
	timeAfter = 0;

	// write config file if anything changed
	Com_WriteConfiguration(); 

	//
	// main event loop
	//
	if ( com_speeds->integer ) {
		timeBeforeFirstEvents = Sys_Milliseconds ();
	}

	// Figure out how much time we have
	if(!com_timedemo->integer)
	{
		if(com_dedicated->integer)
			minMsec = SV_FrameMsec();
		else
		{
			if(com_minimized->integer && com_maxfpsMinimized->integer > 0)
				minMsec = 1000 / com_maxfpsMinimized->integer;
			else if(com_unfocused->integer && com_maxfpsUnfocused->integer > 0)
				minMsec = 1000 / com_maxfpsUnfocused->integer;
			else if(com_maxfps->integer > 0)
				minMsec = 1000 / com_maxfps->integer;
			else
				minMsec = 1;
			
			timeVal = com_frameTime - lastTime;
			bias += timeVal - minMsec;
			
			if(bias > minMsec)
				bias = minMsec;
			
			// Adjust minMsec if previous frame took too long to render so
			// that framerate is stable at the requested value.
			minMsec -= bias;
		}
	}
	else
		minMsec = 1;

	do
	{
		if(com_sv_running->integer)
		{
			timeValSV = SV_SendQueuedPackets();
			
			timeVal = Com_TimeVal(minMsec);

			if(timeValSV < timeVal)
				timeVal = timeValSV;
		}
		else
			timeVal = Com_TimeVal(minMsec);
		
		if(com_busyWait->integer || timeVal < 1)
			NET_Sleep(0);
		else
			NET_Sleep(timeVal - 1);
	} while(com_maxfps->integer && Com_TimeVal(minMsec));
	
	IN_Frame();

	lastTime = com_frameTime;
	com_frameTime = Com_EventLoop();
	
	msec = com_frameTime - lastTime;

	Cbuf_Execute ();

	if (com_altivec->modified)
	{
		Com_DetectAltivec();
		com_altivec->modified = qfalse;
	}

	// mess with msec if needed
	msec = Com_ModifyMsec(msec);

	//
	// server side
	//
	if ( com_speeds->integer ) {
		timeBeforeServer = Sys_Milliseconds ();
	}

	SV_Frame( msec );

	// if "dedicated" has been modified, start up
	// or shut down the client system.
	// Do this after the server may have started,
	// but before the client tries to auto-connect
	if ( com_dedicated->modified ) {
		// get the latched value
		Cvar_Get( "dedicated", "0", 0 );
		com_dedicated->modified = qfalse;
		if ( !com_dedicated->integer ) {
			SV_Shutdown( "dedicated set to 0" );
			CL_FlushMemory();
		}
	}

#ifndef DEDICATED
	//
	// client system
	//
	//
	// run event loop a second time to get server to client packets
	// without a frame of latency
	//
	if ( com_speeds->integer ) {
		timeBeforeEvents = Sys_Milliseconds ();
	}
	Com_EventLoop();
	Cbuf_Execute ();


	//
	// client side
	//
	if ( com_speeds->integer ) {
		timeBeforeClient = Sys_Milliseconds ();
	}

	CL_Frame( msec );

	if ( com_speeds->integer ) {
		timeAfter = Sys_Milliseconds ();
	}
#else
	if ( com_speeds->integer ) {
		timeAfter = Sys_Milliseconds ();
		timeBeforeEvents = timeAfter;
		timeBeforeClient = timeAfter;
	}
#endif


	NET_FlushPacketQueue();

	//
	// report timing information
	//
	if ( com_speeds->integer ) {
		int			all, sv, ev, cl;

		all = timeAfter - timeBeforeServer;
		sv = timeBeforeEvents - timeBeforeServer;
		ev = timeBeforeServer - timeBeforeFirstEvents + timeBeforeClient - timeBeforeEvents;
		cl = timeAfter - timeBeforeClient;
		sv -= time_game;
		cl -= time_frontend + time_backend;

		Com_Printf ("frame:%i all:%3i sv:%3i ev:%3i cl:%3i gm:%3i rf:%3i bk:%3i\n", 
					 com_frameNumber, all, sv, ev, cl, time_game, time_frontend, time_backend );
	}	

	//
	// trace optimization tracking
	//
	if ( com_showtrace->integer ) {
	
		extern	int c_traces, c_brush_traces, c_patch_traces;
		extern	int	c_pointcontents;

		Com_Printf ("%4i traces  (%ib %ip) %4i points\n", c_traces,
			c_brush_traces, c_patch_traces, c_pointcontents);
		c_traces = 0;
		c_brush_traces = 0;
		c_patch_traces = 0;
		c_pointcontents = 0;
	}

	Com_ReadFromPipe( );

	com_frameNumber++;
}