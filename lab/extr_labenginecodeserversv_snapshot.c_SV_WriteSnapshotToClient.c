#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_10__ {size_t outgoingSequence; } ;
struct TYPE_11__ {scalar_t__ deltaMessage; scalar_t__ state; scalar_t__ rateDelayed; scalar_t__ oldServerTime; int /*<<< orphan*/  name; TYPE_1__ netchan; TYPE_3__* frames; } ;
typedef  TYPE_2__ client_t ;
struct TYPE_12__ {scalar_t__ first_entity; int areabytes; int /*<<< orphan*/  ps; int /*<<< orphan*/  areabits; } ;
typedef  TYPE_3__ clientSnapshot_t ;
struct TYPE_15__ {scalar_t__ time; } ;
struct TYPE_14__ {int integer; } ;
struct TYPE_13__ {scalar_t__ nextSnapshotEntities; scalar_t__ numSnapshotEntities; int snapFlagServerBit; } ;

/* Variables and functions */
 scalar_t__ CS_ACTIVE ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_WriteByte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSG_WriteDeltaPlayerstate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_WriteLong (int /*<<< orphan*/ *,scalar_t__) ; 
 int PACKET_BACKUP ; 
 size_t PACKET_MASK ; 
 int SNAPFLAG_NOT_ACTIVE ; 
 int SNAPFLAG_RATE_DELAYED ; 
 int /*<<< orphan*/  SV_EmitPacketEntities (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_6__ sv ; 
 TYPE_5__* sv_padPackets ; 
 int svc_nop ; 
 int svc_snapshot ; 
 TYPE_4__ svs ; 

__attribute__((used)) static void SV_WriteSnapshotToClient( client_t *client, msg_t *msg ) {
	clientSnapshot_t	*frame, *oldframe;
	int					lastframe;
	int					i;
	int					snapFlags;

	// this is the snapshot we are creating
	frame = &client->frames[ client->netchan.outgoingSequence & PACKET_MASK ];

	// try to use a previous frame as the source for delta compressing the snapshot
	if ( client->deltaMessage <= 0 || client->state != CS_ACTIVE ) {
		// client is asking for a retransmit
		oldframe = NULL;
		lastframe = 0;
	} else if ( client->netchan.outgoingSequence - client->deltaMessage 
		>= (PACKET_BACKUP - 3) ) {
		// client hasn't gotten a good message through in a long time
		Com_DPrintf ("%s: Delta request from out of date packet.\n", client->name);
		oldframe = NULL;
		lastframe = 0;
	} else {
		// we have a valid snapshot to delta from
		oldframe = &client->frames[ client->deltaMessage & PACKET_MASK ];
		lastframe = client->netchan.outgoingSequence - client->deltaMessage;

		// the snapshot's entities may still have rolled off the buffer, though
		if ( oldframe->first_entity <= svs.nextSnapshotEntities - svs.numSnapshotEntities ) {
			Com_DPrintf ("%s: Delta request from out of date entities.\n", client->name);
			oldframe = NULL;
			lastframe = 0;
		}
	}

	MSG_WriteByte (msg, svc_snapshot);

	// NOTE, MRE: now sent at the start of every message from server to client
	// let the client know which reliable clientCommands we have received
	//MSG_WriteLong( msg, client->lastClientCommand );

	// send over the current server time so the client can drift
	// its view of time to try to match
	if( client->oldServerTime ) {
		// The server has not yet got an acknowledgement of the
		// new gamestate from this client, so continue to send it
		// a time as if the server has not restarted. Note from
		// the client's perspective this time is strictly speaking
		// incorrect, but since it'll be busy loading a map at
		// the time it doesn't really matter.
		MSG_WriteLong (msg, sv.time + client->oldServerTime);
	} else {
		MSG_WriteLong (msg, sv.time);
	}

	// what we are delta'ing from
	MSG_WriteByte (msg, lastframe);

	snapFlags = svs.snapFlagServerBit;
	if ( client->rateDelayed ) {
		snapFlags |= SNAPFLAG_RATE_DELAYED;
	}
	if ( client->state != CS_ACTIVE ) {
		snapFlags |= SNAPFLAG_NOT_ACTIVE;
	}

	MSG_WriteByte (msg, snapFlags);

	// send over the areabits
	MSG_WriteByte (msg, frame->areabytes);
	MSG_WriteData (msg, frame->areabits, frame->areabytes);

	// delta encode the playerstate
	if ( oldframe ) {
		MSG_WriteDeltaPlayerstate( msg, &oldframe->ps, &frame->ps );
	} else {
		MSG_WriteDeltaPlayerstate( msg, NULL, &frame->ps );
	}

	// delta encode the entities
	SV_EmitPacketEntities (oldframe, frame, msg);

	// padding for rate debugging
	if ( sv_padPackets->integer ) {
		for ( i = 0 ; i < sv_padPackets->integer ; i++ ) {
			MSG_WriteByte (msg, svc_nop);
		}
	}
}