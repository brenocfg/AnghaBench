#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ serverTime; } ;
typedef  TYPE_3__ usercmd_t ;
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  nullcmd ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_19__ {scalar_t__ serverTime; } ;
struct TYPE_21__ {int deltaMessage; int messageAcknowledge; int reliableAcknowledge; scalar_t__ pureAuthentic; scalar_t__ state; TYPE_2__ lastUsercmd; int /*<<< orphan*/  name; int /*<<< orphan*/  gotCP; TYPE_1__* frames; int /*<<< orphan*/ * reliableCommands; } ;
typedef  TYPE_4__ client_t ;
struct TYPE_24__ {int checksumFeed; } ;
struct TYPE_23__ {scalar_t__ integer; } ;
struct TYPE_22__ {int /*<<< orphan*/  time; } ;
struct TYPE_18__ {int /*<<< orphan*/  messageAcked; } ;

/* Variables and functions */
 scalar_t__ CS_ACTIVE ; 
 scalar_t__ CS_PRIMED ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int MAX_PACKET_USERCMDS ; 
 int MAX_RELIABLE_COMMANDS ; 
 int MSG_HashKey (int /*<<< orphan*/ ,int) ; 
 int MSG_ReadByte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_ReadDeltaUsercmdKey (int /*<<< orphan*/ *,int,TYPE_3__*,TYPE_3__*) ; 
 size_t PACKET_MASK ; 
 int /*<<< orphan*/  SV_ClientEnterWorld (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SV_ClientThink (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  SV_SendClientGameState (TYPE_4__*) ; 
 TYPE_7__ sv ; 
 TYPE_6__* sv_pure ; 
 TYPE_5__ svs ; 

__attribute__((used)) static void SV_UserMove( client_t *cl, msg_t *msg, qboolean delta ) {
	int			i, key;
	int			cmdCount;
	usercmd_t	nullcmd;
	usercmd_t	cmds[MAX_PACKET_USERCMDS];
	usercmd_t	*cmd, *oldcmd;

	if ( delta ) {
		cl->deltaMessage = cl->messageAcknowledge;
	} else {
		cl->deltaMessage = -1;
	}

	cmdCount = MSG_ReadByte( msg );

	if ( cmdCount < 1 ) {
		Com_Printf( "cmdCount < 1\n" );
		return;
	}

	if ( cmdCount > MAX_PACKET_USERCMDS ) {
		Com_Printf( "cmdCount > MAX_PACKET_USERCMDS\n" );
		return;
	}

	// use the checksum feed in the key
	key = sv.checksumFeed;
	// also use the message acknowledge
	key ^= cl->messageAcknowledge;
	// also use the last acknowledged server command in the key
	key ^= MSG_HashKey(cl->reliableCommands[ cl->reliableAcknowledge & (MAX_RELIABLE_COMMANDS-1) ], 32);

	Com_Memset( &nullcmd, 0, sizeof(nullcmd) );
	oldcmd = &nullcmd;
	for ( i = 0 ; i < cmdCount ; i++ ) {
		cmd = &cmds[i];
		MSG_ReadDeltaUsercmdKey( msg, key, oldcmd, cmd );
		oldcmd = cmd;
	}

	// save time for ping calculation
	cl->frames[ cl->messageAcknowledge & PACKET_MASK ].messageAcked = svs.time;

	// TTimo
	// catch the no-cp-yet situation before SV_ClientEnterWorld
	// if CS_ACTIVE, then it's time to trigger a new gamestate emission
	// if not, then we are getting remaining parasite usermove commands, which we should ignore
	if (sv_pure->integer != 0 && cl->pureAuthentic == 0 && !cl->gotCP) {
		if (cl->state == CS_ACTIVE)
		{
			// we didn't get a cp yet, don't assume anything and just send the gamestate all over again
			Com_DPrintf( "%s: didn't get cp command, resending gamestate\n", cl->name);
			SV_SendClientGameState( cl );
		}
		return;
	}			
	
	// if this is the first usercmd we have received
	// this gamestate, put the client into the world
	if ( cl->state == CS_PRIMED ) {
		SV_ClientEnterWorld( cl, &cmds[0] );
		// the moves can be processed normaly
	}
	
	// a bad cp command was sent, drop the client
	if (sv_pure->integer != 0 && cl->pureAuthentic == 0) {		
		SV_DropClient( cl, "Cannot validate pure client!");
		return;
	}

	if ( cl->state != CS_ACTIVE ) {
		cl->deltaMessage = -1;
		return;
	}

	// usually, the first couple commands will be duplicates
	// of ones we have previously received, but the servertimes
	// in the commands will cause them to be immediately discarded
	for ( i =  0 ; i < cmdCount ; i++ ) {
		// if this is a cmd from before a map_restart ignore it
		if ( cmds[i].serverTime > cmds[cmdCount-1].serverTime ) {
			continue;
		}
		// extremely lagged or cmd from before a map_restart
		//if ( cmds[i].serverTime > svs.time + 3000 ) {
		//	continue;
		//}
		// don't execute if this is an old cmd which is already executed
		// these old cmds are included when cl_packetdup > 0
		if ( cmds[i].serverTime <= cl->lastUsercmd.serverTime ) {
			continue;
		}
		SV_ClientThink (cl, &cmds[ i ]);
	}
}