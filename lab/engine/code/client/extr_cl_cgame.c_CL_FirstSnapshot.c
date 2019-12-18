#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int snapFlags; scalar_t__ serverTime; } ;
struct TYPE_12__ {TYPE_1__ snap; scalar_t__ oldServerTime; scalar_t__ serverTimeDelta; } ;
struct TYPE_11__ {scalar_t__* string; } ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_9__ {float* voipGain; int /*<<< orphan*/  voipTargets; void* voipMuteAll; scalar_t__ voipCodecInitialized; void** voipIgnore; int /*<<< orphan*/ * opusDecoder; int /*<<< orphan*/  opusEncoder; scalar_t__ timeDemoBaseTime; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {scalar_t__ realtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_ACTIVE ; 
 int /*<<< orphan*/  CLIENT_WINDOW_TITLE ; 
 int /*<<< orphan*/  CL_Voip_f ; 
 int /*<<< orphan*/  Cbuf_AddText (scalar_t__*) ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int,...) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  OPUS_APPLICATION_VOIP ; 
 int SNAPFLAG_NOT_ACTIVE ; 
 TYPE_6__ cl ; 
 TYPE_5__* cl_activeAction ; 
 TYPE_4__* cl_useMumble ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 
 int /*<<< orphan*/  mumble_islinked () ; 
 int mumble_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_decoder_create (int,int,int*) ; 
 int /*<<< orphan*/  opus_encoder_create (int,int,int /*<<< orphan*/ ,int*) ; 
 void* qfalse ; 
 scalar_t__ qtrue ; 

void CL_FirstSnapshot( void ) {
	// ignore snapshots that don't have entities
	if ( cl.snap.snapFlags & SNAPFLAG_NOT_ACTIVE ) {
		return;
	}
	clc.state = CA_ACTIVE;

	// set the timedelta so we are exactly on this first frame
	cl.serverTimeDelta = cl.snap.serverTime - cls.realtime;
	cl.oldServerTime = cl.snap.serverTime;

	clc.timeDemoBaseTime = cl.snap.serverTime;

	// if this is the first frame of active play,
	// execute the contents of activeAction now
	// this is to allow scripting a timedemo to start right
	// after loading
	if ( cl_activeAction->string[0] ) {
		Cbuf_AddText( cl_activeAction->string );
		Cvar_Set( "activeAction", "" );
	}

#ifdef USE_MUMBLE
	if ((cl_useMumble->integer) && !mumble_islinked()) {
		int ret = mumble_link(CLIENT_WINDOW_TITLE);
		Com_Printf("Mumble: Linking to Mumble application %s\n", ret==0?"ok":"failed");
	}
#endif

#ifdef USE_VOIP
	if (!clc.voipCodecInitialized) {
		int i;
		int error;

		clc.opusEncoder = opus_encoder_create(48000, 1, OPUS_APPLICATION_VOIP, &error);

		if ( error ) {
			Com_DPrintf("VoIP: Error opus_encoder_create %d\n", error);
			return;
		}

		for (i = 0; i < MAX_CLIENTS; i++) {
			clc.opusDecoder[i] = opus_decoder_create(48000, 1, &error);
			if ( error ) {
				Com_DPrintf("VoIP: Error opus_decoder_create(%d) %d\n", i, error);
				return;
			}
			clc.voipIgnore[i] = qfalse;
			clc.voipGain[i] = 1.0f;
		}
		clc.voipCodecInitialized = qtrue;
		clc.voipMuteAll = qfalse;
		Cmd_AddCommand ("voip", CL_Voip_f);
		Cvar_Set("cl_voipSendTarget", "spatial");
		Com_Memset(clc.voipTargets, ~0, sizeof(clc.voipTargets));
	}
#endif
}