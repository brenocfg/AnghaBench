#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nullstate ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  msgBuffer ;
struct TYPE_16__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_3__ entityState_t ;
struct TYPE_14__ {int /*<<< orphan*/  outgoingSequence; } ;
struct TYPE_17__ {struct TYPE_17__* reliableSequence; struct TYPE_17__* lastClientCommand; TYPE_1__ netchan; int /*<<< orphan*/  gamestateMessageNum; int /*<<< orphan*/  gotCP; scalar_t__ pureAuthentic; int /*<<< orphan*/  state; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ client_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_19__ {TYPE_4__* checksumFeed; TYPE_2__* svEntities; scalar_t__** configstrings; } ;
struct TYPE_18__ {int clients; } ;
struct TYPE_15__ {TYPE_3__ baseline; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PRIMED ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int MAX_CONFIGSTRINGS ; 
 int MAX_GENTITIES ; 
 int MAX_MSGLEN ; 
 int /*<<< orphan*/  MSG_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MSG_WriteBigString (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  MSG_WriteByte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_WriteDeltaEntity (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_WriteLong (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  MSG_WriteShort (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SV_SendMessageToClient (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  SV_UpdateServerCommandsToClient (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_6__ sv ; 
 int /*<<< orphan*/  svc_EOF ; 
 int /*<<< orphan*/  svc_baseline ; 
 int /*<<< orphan*/  svc_configstring ; 
 int /*<<< orphan*/  svc_gamestate ; 
 TYPE_5__ svs ; 

__attribute__((used)) static void SV_SendClientGameState( client_t *client ) {
	int			start;
	entityState_t	*base, nullstate;
	msg_t		msg;
	byte		msgBuffer[MAX_MSGLEN];

 	Com_DPrintf ("SV_SendClientGameState() for %s\n", client->name);
	Com_DPrintf( "Going from CS_CONNECTED to CS_PRIMED for %s\n", client->name );
	client->state = CS_PRIMED;
	client->pureAuthentic = 0;
	client->gotCP = qfalse;

	// when we receive the first packet from the client, we will
	// notice that it is from a different serverid and that the
	// gamestate message was not just sent, forcing a retransmit
	client->gamestateMessageNum = client->netchan.outgoingSequence;

	MSG_Init( &msg, msgBuffer, sizeof( msgBuffer ) );

	// NOTE, MRE: all server->client messages now acknowledge
	// let the client know which reliable clientCommands we have received
	MSG_WriteLong( &msg, client->lastClientCommand );

	// send any server commands waiting to be sent first.
	// we have to do this cause we send the client->reliableSequence
	// with a gamestate and it sets the clc.serverCommandSequence at
	// the client side
	SV_UpdateServerCommandsToClient( client, &msg );

	// send the gamestate
	MSG_WriteByte( &msg, svc_gamestate );
	MSG_WriteLong( &msg, client->reliableSequence );

	// write the configstrings
	for ( start = 0 ; start < MAX_CONFIGSTRINGS ; start++ ) {
		if (sv.configstrings[start][0]) {
			MSG_WriteByte( &msg, svc_configstring );
			MSG_WriteShort( &msg, start );
			MSG_WriteBigString( &msg, sv.configstrings[start] );
		}
	}

	// write the baselines
	Com_Memset( &nullstate, 0, sizeof( nullstate ) );
	for ( start = 0 ; start < MAX_GENTITIES; start++ ) {
		base = &sv.svEntities[start].baseline;
		if ( !base->number ) {
			continue;
		}
		MSG_WriteByte( &msg, svc_baseline );
		MSG_WriteDeltaEntity( &msg, &nullstate, base, qtrue );
	}

	MSG_WriteByte( &msg, svc_EOF );

	MSG_WriteLong( &msg, client - svs.clients);

	// write the checksum feed
	MSG_WriteLong( &msg, sv.checksumFeed);

	// deliver this to the client
	SV_SendMessageToClient( &msg, client );
}