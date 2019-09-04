#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_22__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  userinfo ;
typedef  int /*<<< orphan*/  sharedEntity_t ;
struct TYPE_29__ {scalar_t__ port; } ;
typedef  TYPE_1__ netadr_t ;
struct TYPE_30__ {scalar_t__ port; scalar_t__ type; } ;
struct TYPE_28__ {int qport; TYPE_22__ remoteAddress; } ;
struct TYPE_31__ {scalar_t__ state; int lastConnectTime; int challenge; char* userinfo; char* name; int lastPacketTime; int gamestateMessageNum; scalar_t__ lastSnapshotTime; int /*<<< orphan*/  netchan_start_queue; int /*<<< orphan*/ * netchan_end_queue; TYPE_17__ netchan; int /*<<< orphan*/ * gentity; scalar_t__ reliableSequence; scalar_t__ reliableAcknowledge; } ;
typedef  TYPE_2__ client_t ;
struct TYPE_32__ {int challenge; int pingTime; void* connected; void* wasrefused; int /*<<< orphan*/  adr; } ;
typedef  TYPE_3__ challenge_t ;
struct TYPE_38__ {int integer; } ;
struct TYPE_37__ {int value; } ;
struct TYPE_36__ {int integer; } ;
struct TYPE_35__ {int /*<<< orphan*/  string; } ;
struct TYPE_34__ {int integer; } ;
struct TYPE_33__ {int time; TYPE_2__* clients; TYPE_3__* challenges; } ;
struct TYPE_27__ {int integer; } ;
struct TYPE_26__ {int value; } ;

/* Variables and functions */
 scalar_t__ CS_CONNECTED ; 
 scalar_t__ CS_FREE ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,...) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  GAME_CLIENT_CONNECT ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,char*) ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_CHALLENGES ; 
 int MAX_INFO_STRING ; 
 scalar_t__ NA_BOT ; 
 char* NET_AdrToString (TYPE_1__) ; 
 scalar_t__ NET_CompareAdr (TYPE_1__,int /*<<< orphan*/ ) ; 
 scalar_t__ NET_CompareBaseAdr (TYPE_1__,TYPE_22__) ; 
 scalar_t__ NET_IsLocalAddress (TYPE_1__) ; 
 int /*<<< orphan*/  NET_OutOfBandPrint (int /*<<< orphan*/ ,TYPE_1__,char*,...) ; 
 int /*<<< orphan*/  NS_SERVER ; 
 int /*<<< orphan*/  Netchan_Setup (int /*<<< orphan*/ ,TYPE_17__*,TYPE_1__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * SV_GentityNum (int) ; 
 int /*<<< orphan*/  SV_Heartbeat_f () ; 
 scalar_t__ SV_IsBanned (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_UserinfoChanged (TYPE_2__*) ; 
 int /*<<< orphan*/  Sys_IsLANAddress (TYPE_1__) ; 
 intptr_t VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 char* VM_ExplicitArgPtr (int /*<<< orphan*/ ,intptr_t) ; 
 int atoi (char*) ; 
 TYPE_11__* com_protocol ; 
 int /*<<< orphan*/  gvm ; 
 int /*<<< orphan*/  qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 TYPE_10__* sv_maxPing ; 
 TYPE_9__* sv_maxclients ; 
 TYPE_8__* sv_minPing ; 
 TYPE_7__* sv_privateClients ; 
 TYPE_6__* sv_privatePassword ; 
 TYPE_5__* sv_reconnectlimit ; 
 TYPE_4__ svs ; 

void SV_DirectConnect( netadr_t from ) {
	char		userinfo[MAX_INFO_STRING];
	int			i;
	client_t	*cl, *newcl;
	client_t	temp;
	sharedEntity_t *ent;
	int			clientNum;
	int			version;
	int			qport;
	int			challenge;
	char		*password;
	int			startIndex;
	intptr_t		denied;
	int			count;
	char		*ip;
#ifdef LEGACY_PROTOCOL
	qboolean	compat = qfalse;
#endif

	Com_DPrintf ("SVC_DirectConnect ()\n");
	
	// Check whether this client is banned.
	if(SV_IsBanned(&from, qfalse))
	{
		NET_OutOfBandPrint(NS_SERVER, from, "print\nYou are banned from this server.\n");
		return;
	}

	Q_strncpyz( userinfo, Cmd_Argv(1), sizeof(userinfo) );

	version = atoi(Info_ValueForKey(userinfo, "protocol"));
	
#ifdef LEGACY_PROTOCOL
	if(version > 0 && com_legacyprotocol->integer == version)
		compat = qtrue;
	else
#endif
	{
		if(version != com_protocol->integer)
		{
			NET_OutOfBandPrint(NS_SERVER, from, "print\nServer uses protocol version %i "
					   "(yours is %i).\n", com_protocol->integer, version);
			Com_DPrintf("    rejected connect from version %i\n", version);
			return;
		}
	}

	challenge = atoi( Info_ValueForKey( userinfo, "challenge" ) );
	qport = atoi( Info_ValueForKey( userinfo, "qport" ) );

	// quick reject
	for (i=0,cl=svs.clients ; i < sv_maxclients->integer ; i++,cl++) {
		if ( cl->state == CS_FREE ) {
			continue;
		}
		if ( NET_CompareBaseAdr( from, cl->netchan.remoteAddress )
			&& ( cl->netchan.qport == qport 
			|| from.port == cl->netchan.remoteAddress.port ) ) {
			if (( svs.time - cl->lastConnectTime) 
				< (sv_reconnectlimit->integer * 1000)) {
				Com_DPrintf ("%s:reconnect rejected : too soon\n", NET_AdrToString (from));
				return;
			}
			break;
		}
	}
	
	// don't let "ip" overflow userinfo string
	if ( NET_IsLocalAddress (from) )
		ip = "localhost";
	else
		ip = (char *)NET_AdrToString( from );
	if( ( strlen( ip ) + strlen( userinfo ) + 4 ) >= MAX_INFO_STRING ) {
		NET_OutOfBandPrint( NS_SERVER, from,
			"print\nUserinfo string length exceeded.  "
			"Try removing setu cvars from your config.\n" );
		return;
	}
	Info_SetValueForKey( userinfo, "ip", ip );

	// see if the challenge is valid (LAN clients don't need to challenge)
	if (!NET_IsLocalAddress(from))
	{
		int ping;
		challenge_t *challengeptr;

		for (i=0; i<MAX_CHALLENGES; i++)
		{
			if (NET_CompareAdr(from, svs.challenges[i].adr))
			{
				if(challenge == svs.challenges[i].challenge)
					break;
			}
		}

		if (i == MAX_CHALLENGES)
		{
			NET_OutOfBandPrint( NS_SERVER, from, "print\nNo or bad challenge for your address.\n" );
			return;
		}
	
		challengeptr = &svs.challenges[i];
		
		if(challengeptr->wasrefused)
		{
			// Return silently, so that error messages written by the server keep being displayed.
			return;
		}

		ping = svs.time - challengeptr->pingTime;

		// never reject a LAN client based on ping
		if ( !Sys_IsLANAddress( from ) ) {
			if ( sv_minPing->value && ping < sv_minPing->value ) {
				NET_OutOfBandPrint( NS_SERVER, from, "print\nServer is for high pings only\n" );
				Com_DPrintf ("Client %i rejected on a too low ping\n", i);
				challengeptr->wasrefused = qtrue;
				return;
			}
			if ( sv_maxPing->value && ping > sv_maxPing->value ) {
				NET_OutOfBandPrint( NS_SERVER, from, "print\nServer is for low pings only\n" );
				Com_DPrintf ("Client %i rejected on a too high ping\n", i);
				challengeptr->wasrefused = qtrue;
				return;
			}
		}

		Com_Printf("Client %i connecting with %i challenge ping\n", i, ping);
		challengeptr->connected = qtrue;
	}

	newcl = &temp;
	Com_Memset (newcl, 0, sizeof(client_t));

	// if there is already a slot for this ip, reuse it
	for (i=0,cl=svs.clients ; i < sv_maxclients->integer ; i++,cl++) {
		if ( cl->state == CS_FREE ) {
			continue;
		}
		if ( NET_CompareBaseAdr( from, cl->netchan.remoteAddress )
			&& ( cl->netchan.qport == qport 
			|| from.port == cl->netchan.remoteAddress.port ) ) {
			Com_Printf ("%s:reconnect\n", NET_AdrToString (from));
			newcl = cl;

			// this doesn't work because it nukes the players userinfo

//			// disconnect the client from the game first so any flags the
//			// player might have are dropped
//			VM_Call( gvm, GAME_CLIENT_DISCONNECT, newcl - svs.clients );
			//
			goto gotnewcl;
		}
	}

	// find a client slot
	// if "sv_privateClients" is set > 0, then that number
	// of client slots will be reserved for connections that
	// have "password" set to the value of "sv_privatePassword"
	// Info requests will report the maxclients as if the private
	// slots didn't exist, to prevent people from trying to connect
	// to a full server.
	// This is to allow us to reserve a couple slots here on our
	// servers so we can play without having to kick people.

	// check for privateClient password
	password = Info_ValueForKey( userinfo, "password" );
	if ( *password && !strcmp( password, sv_privatePassword->string ) ) {
		startIndex = 0;
	} else {
		// skip past the reserved slots
		startIndex = sv_privateClients->integer;
	}

	newcl = NULL;
	for ( i = startIndex; i < sv_maxclients->integer ; i++ ) {
		cl = &svs.clients[i];
		if (cl->state == CS_FREE) {
			newcl = cl;
			break;
		}
	}

	if ( !newcl ) {
		if ( NET_IsLocalAddress( from ) ) {
			count = 0;
			for ( i = startIndex; i < sv_maxclients->integer ; i++ ) {
				cl = &svs.clients[i];
				if (cl->netchan.remoteAddress.type == NA_BOT) {
					count++;
				}
			}
			// if they're all bots
			if (count >= sv_maxclients->integer - startIndex) {
				SV_DropClient(&svs.clients[sv_maxclients->integer - 1], "only bots on server");
				newcl = &svs.clients[sv_maxclients->integer - 1];
			}
			else {
				Com_Error( ERR_FATAL, "server is full on local connect" );
				return;
			}
		}
		else {
			NET_OutOfBandPrint( NS_SERVER, from, "print\nServer is full.\n" );
			Com_DPrintf ("Rejected a connection.\n");
			return;
		}
	}

	// we got a newcl, so reset the reliableSequence and reliableAcknowledge
	cl->reliableAcknowledge = 0;
	cl->reliableSequence = 0;

gotnewcl:	
	// build a new connection
	// accept the new client
	// this is the only place a client_t is ever initialized
	*newcl = temp;
	clientNum = newcl - svs.clients;
	ent = SV_GentityNum( clientNum );
	newcl->gentity = ent;

	// save the challenge
	newcl->challenge = challenge;

	// save the address
#ifdef LEGACY_PROTOCOL
	newcl->compat = compat;
	Netchan_Setup(NS_SERVER, &newcl->netchan, from, qport, challenge, compat);
#else
	Netchan_Setup(NS_SERVER, &newcl->netchan, from, qport, challenge, qfalse);
#endif
	// init the netchan queue
	newcl->netchan_end_queue = &newcl->netchan_start_queue;

	// save the userinfo
	Q_strncpyz( newcl->userinfo, userinfo, sizeof(newcl->userinfo) );

	// get the game a chance to reject this connection or modify the userinfo
	denied = VM_Call( gvm, GAME_CLIENT_CONNECT, clientNum, qtrue, qfalse ); // firstTime = qtrue
	if ( denied ) {
		// we can't just use VM_ArgPtr, because that is only valid inside a VM_Call
		char *str = VM_ExplicitArgPtr( gvm, denied );

		NET_OutOfBandPrint( NS_SERVER, from, "print\n%s\n", str );
		Com_DPrintf ("Game rejected a connection: %s.\n", str);
		return;
	}

	SV_UserinfoChanged( newcl );

	// send the connect packet to the client
	NET_OutOfBandPrint(NS_SERVER, from, "connectResponse %d", challenge);

	Com_DPrintf( "Going from CS_FREE to CS_CONNECTED for %s\n", newcl->name );

	newcl->state = CS_CONNECTED;
	newcl->lastSnapshotTime = 0;
	newcl->lastPacketTime = svs.time;
	newcl->lastConnectTime = svs.time;
	
	// when we receive the first packet from the client, we will
	// notice that it is from a different serverid and that the
	// gamestate message was not just sent, forcing a retransmit
	newcl->gamestateMessageNum = -1;

	// if this was the first client on the server, or the last client
	// the server can hold, send a heartbeat to the master.
	count = 0;
	for (i=0,cl=svs.clients ; i < sv_maxclients->integer ; i++,cl++) {
		if ( svs.clients[i].state >= CS_CONNECTED ) {
			count++;
		}
	}
	if ( count == 1 || count == sv_maxclients->integer ) {
		SV_Heartbeat_f();
	}
}