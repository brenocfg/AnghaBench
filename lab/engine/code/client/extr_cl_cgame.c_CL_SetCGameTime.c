#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int integer; } ;
struct TYPE_21__ {scalar_t__ integer; } ;
struct TYPE_20__ {scalar_t__ state; int timeDemoStart; int timeDemoLastFrame; int timeDemoMinDuration; int timeDemoMaxDuration; int timeDemoFrames; int* timeDemoDurations; int timeDemoBaseTime; scalar_t__ demoplaying; void* firstDemoFrameSkipped; } ;
struct TYPE_19__ {int realtime; } ;
struct TYPE_18__ {scalar_t__ integer; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* set_map_finished ) (int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  userdata; TYPE_2__ hooks; } ;
struct TYPE_16__ {scalar_t__ integer; } ;
struct TYPE_14__ {int serverTime; int /*<<< orphan*/  valid; } ;
struct TYPE_13__ {int oldFrameServerTime; int serverTime; int serverTimeDelta; int oldServerTime; TYPE_1__ snap; scalar_t__ newSnapshots; void* extrapolatedSnapshot; } ;
struct TYPE_12__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_PRIMED ; 
 int /*<<< orphan*/  CL_AdjustTimeDelta () ; 
 scalar_t__ CL_CheckPaused () ; 
 int /*<<< orphan*/  CL_FirstSnapshot () ; 
 int /*<<< orphan*/  CL_ReadDemoMessage () ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int INT_MAX ; 
 int MAX_TIMEDEMO_DURATIONS ; 
 int Sys_Milliseconds () ; 
 int UCHAR_MAX ; 
 TYPE_11__ cl ; 
 TYPE_10__* cl_freezeDemo ; 
 TYPE_9__* cl_timeNudge ; 
 TYPE_8__* cl_timedemo ; 
 TYPE_7__ clc ; 
 TYPE_6__ cls ; 
 TYPE_5__* com_sv_running ; 
 TYPE_4__* dmlab_context () ; 
 scalar_t__ qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 
 TYPE_3__* sv_paused ; 

void CL_SetCGameTime( void ) {
	// getting a valid frame message ends the connection process
	if ( clc.state != CA_ACTIVE ) {
		if ( clc.state != CA_PRIMED ) {
			return;
		}
		if ( clc.demoplaying ) {
			// we shouldn't get the first snapshot on the same frame
			// as the gamestate, because it causes a bad time skip
			if ( !clc.firstDemoFrameSkipped ) {
				clc.firstDemoFrameSkipped = qtrue;
				return;
			}
			CL_ReadDemoMessage();
		}
		if ( cl.newSnapshots ) {
			cl.newSnapshots = qfalse;
			CL_FirstSnapshot();
		}
		if ( clc.state != CA_ACTIVE ) {
			return;
		}
	}	

	// if we have gotten to this point, cl.snap is guaranteed to be valid
	if ( !cl.snap.valid ) {
		Com_Error( ERR_DROP, "CL_SetCGameTime: !cl.snap.valid" );
	}

	// allow pause in single player
	if ( sv_paused->integer && CL_CheckPaused() && com_sv_running->integer ) {
		// paused
		return;
	}

	if ( cl.snap.serverTime < cl.oldFrameServerTime ) {
		Com_Error( ERR_DROP, "cl.snap.serverTime < cl.oldFrameServerTime" );
	}
	cl.oldFrameServerTime = cl.snap.serverTime;


	// get our current view of time

	if ( clc.demoplaying && cl_freezeDemo->integer ) {
		// cl_freezeDemo is used to lock a demo in place for single frame advances

	} else {
		// cl_timeNudge is a user adjustable cvar that allows more
		// or less latency to be added in the interest of better 
		// smoothness or better responsiveness.
		int tn;
		
		tn = cl_timeNudge->integer;
		if (tn<-30) {
			tn = -30;
		} else if (tn>30) {
			tn = 30;
		}

		cl.serverTime = cls.realtime + cl.serverTimeDelta - tn;

		// guarantee that time will never flow backwards, even if
		// serverTimeDelta made an adjustment or cl_timeNudge was changed
		if ( cl.serverTime < cl.oldServerTime ) {
			cl.serverTime = cl.oldServerTime;
		}
		cl.oldServerTime = cl.serverTime;

		// note if we are almost past the latest frame (without timeNudge),
		// so we will try and adjust back a bit when the next snapshot arrives
		if ( cls.realtime + cl.serverTimeDelta >= cl.snap.serverTime - 5 ) {
			cl.extrapolatedSnapshot = qtrue;
		}
	}

	// if we have gotten new snapshots, drift serverTimeDelta
	// don't do this every frame, or a period of packet loss would
	// make a huge adjustment
	if ( cl.newSnapshots ) {
		CL_AdjustTimeDelta();
	}

	if ( !clc.demoplaying ) {
		return;
	}

	// if we are playing a demo back, we can just keep reading
	// messages from the demo file until the cgame definitely
	// has valid snapshots to interpolate between

	// a timedemo will always use a deterministic set of time samples
	// no matter what speed machine it is run on,
	// while a normal demo may have different time samples
	// each time it is played back
	if ( cl_timedemo->integer ) {
		int now = Sys_Milliseconds( );
		int frameDuration;

		if (!clc.timeDemoStart) {
			clc.timeDemoStart = clc.timeDemoLastFrame = now;
			clc.timeDemoMinDuration = INT_MAX;
			clc.timeDemoMaxDuration = 0;
		}

		frameDuration = now - clc.timeDemoLastFrame;
		clc.timeDemoLastFrame = now;

		// Ignore the first measurement as it'll always be 0
		if( clc.timeDemoFrames > 0 )
		{
			if( frameDuration > clc.timeDemoMaxDuration )
				clc.timeDemoMaxDuration = frameDuration;

			if( frameDuration < clc.timeDemoMinDuration )
				clc.timeDemoMinDuration = frameDuration;

			// 255 ms = about 4fps
			if( frameDuration > UCHAR_MAX )
				frameDuration = UCHAR_MAX;

			clc.timeDemoDurations[ ( clc.timeDemoFrames - 1 ) %
				MAX_TIMEDEMO_DURATIONS ] = frameDuration;
		}

		clc.timeDemoFrames++;
		cl.serverTime = clc.timeDemoBaseTime + clc.timeDemoFrames * 50;
	}

	while ( cl.serverTime >= cl.snap.serverTime ) {
		// feed another messag, which should change
		// the contents of cl.snap
		CL_ReadDemoMessage();
		if ( clc.state != CA_ACTIVE ) {
			dmlab_context()->hooks.set_map_finished(dmlab_context()->userdata, qtrue);
			return;		// end of demo
		}
	}

}