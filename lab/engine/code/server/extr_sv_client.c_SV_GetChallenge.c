#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_17__ {scalar_t__ type; int /*<<< orphan*/ * ip; } ;
typedef  TYPE_1__ netadr_t ;
struct TYPE_18__ {int time; int clientChallenge; unsigned int firstTime; unsigned int challenge; int pingTime; TYPE_1__ adr; void* wasrefused; void* connected; } ;
typedef  TYPE_2__ challenge_t ;
struct TYPE_24__ {int /*<<< orphan*/  string; } ;
struct TYPE_23__ {scalar_t__ integer; } ;
struct TYPE_22__ {int /*<<< orphan*/  integer; } ;
struct TYPE_21__ {int /*<<< orphan*/  integer; } ;
struct TYPE_20__ {int /*<<< orphan*/  string; } ;
struct TYPE_16__ {scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/ * ip; } ;
struct TYPE_19__ {unsigned int time; TYPE_12__ authorizeAddress; TYPE_2__* challenges; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHORIZE_SERVER_NAME ; 
 int AUTHORIZE_TIMEOUT ; 
 char* BASEGAME ; 
 int /*<<< orphan*/  BigShort (int /*<<< orphan*/ ) ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,...) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 char* Cvar_VariableString (char*) ; 
 scalar_t__ Cvar_VariableValue (char*) ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 int MAX_CHALLENGES ; 
 int MAX_CHALLENGES_MULTI ; 
 scalar_t__ NA_BAD ; 
 scalar_t__ NA_IP ; 
 int /*<<< orphan*/  NET_AdrToString (TYPE_1__) ; 
 scalar_t__ NET_CompareAdr (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  NET_OutOfBandPrint (int /*<<< orphan*/ ,...) ; 
 scalar_t__ NET_StringToAdr (int /*<<< orphan*/ ,TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  NS_SERVER ; 
 int /*<<< orphan*/  PORT_AUTHORIZE ; 
 scalar_t__ SVC_RateLimit (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ SVC_RateLimitAddress (TYPE_1__,int,int) ; 
 int /*<<< orphan*/  Sys_IsLANAddress (TYPE_1__) ; 
 int atoi (char*) ; 
 TYPE_8__* com_gamename ; 
 TYPE_7__* com_legacyprotocol ; 
 TYPE_6__* com_protocol ; 
 TYPE_5__* com_standalone ; 
 int /*<<< orphan*/  outboundLeakyBucket ; 
 void* qfalse ; 
 int qtrue ; 
 scalar_t__ rand () ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* sv_strictAuth ; 
 TYPE_3__ svs ; 

void SV_GetChallenge(netadr_t from)
{
	int		i;
	int		oldest;
	int		oldestTime;
	int		oldestClientTime;
	int		clientChallenge;
	challenge_t	*challenge;
	qboolean wasfound = qfalse;
	char *gameName;
	qboolean gameMismatch;

	// ignore if we are in single player
	if ( Cvar_VariableValue( "g_gametype" ) == GT_SINGLE_PLAYER || Cvar_VariableValue("ui_singlePlayerActive")) {
		return;
	}

	// Prevent using getchallenge as an amplifier
	if ( SVC_RateLimitAddress( from, 10, 1000 ) ) {
		Com_DPrintf( "SV_GetChallenge: rate limit from %s exceeded, dropping request\n",
			NET_AdrToString( from ) );
		return;
	}

	// Allow getchallenge to be DoSed relatively easily, but prevent
	// excess outbound bandwidth usage when being flooded inbound
	if ( SVC_RateLimit( &outboundLeakyBucket, 10, 100 ) ) {
		Com_DPrintf( "SV_GetChallenge: rate limit exceeded, dropping request\n" );
		return;
	}

	gameName = Cmd_Argv(2);

#ifdef LEGACY_PROTOCOL
	// gamename is optional for legacy protocol
	if (com_legacyprotocol->integer && !*gameName)
		gameMismatch = qfalse;
	else
#endif
		gameMismatch = !*gameName || strcmp(gameName, com_gamename->string) != 0;

	// reject client if the gamename string sent by the client doesn't match ours
	if (gameMismatch)
	{
		NET_OutOfBandPrint(NS_SERVER, from, "print\nGame mismatch: This is a %s server\n",
			com_gamename->string);
		return;
	}

	oldest = 0;
	oldestClientTime = oldestTime = 0x7fffffff;

	// see if we already have a challenge for this ip
	challenge = &svs.challenges[0];
	clientChallenge = atoi(Cmd_Argv(1));

	for(i = 0 ; i < MAX_CHALLENGES ; i++, challenge++)
	{
		if(!challenge->connected && NET_CompareAdr(from, challenge->adr))
		{
			wasfound = qtrue;
			
			if(challenge->time < oldestClientTime)
				oldestClientTime = challenge->time;
		}
		
		if(wasfound && i >= MAX_CHALLENGES_MULTI)
		{
			i = MAX_CHALLENGES;
			break;
		}
		
		if(challenge->time < oldestTime)
		{
			oldestTime = challenge->time;
			oldest = i;
		}
	}

	if (i == MAX_CHALLENGES)
	{
		// this is the first time this client has asked for a challenge
		challenge = &svs.challenges[oldest];
		challenge->clientChallenge = clientChallenge;
		challenge->adr = from;
		challenge->firstTime = svs.time;
		challenge->connected = qfalse;
	}

	// always generate a new challenge number, so the client cannot circumvent sv_maxping
	challenge->challenge = ( ((unsigned int)rand() << 16) ^ (unsigned int)rand() ) ^ svs.time;
	challenge->wasrefused = qfalse;
	challenge->time = svs.time;

#ifndef STANDALONE
	// Drop the authorize stuff if this client is coming in via v6 as the auth server does not support ipv6.
	// Drop also for addresses coming in on local LAN and for stand-alone games independent from id's assets.
	if(challenge->adr.type == NA_IP && !com_standalone->integer && !Sys_IsLANAddress(from))
	{
		// look up the authorize server's IP
		if (svs.authorizeAddress.type == NA_BAD)
		{
			Com_Printf( "Resolving %s\n", AUTHORIZE_SERVER_NAME );
			
			if (NET_StringToAdr(AUTHORIZE_SERVER_NAME, &svs.authorizeAddress, NA_IP))
			{
				svs.authorizeAddress.port = BigShort( PORT_AUTHORIZE );
				Com_Printf( "%s resolved to %i.%i.%i.%i:%i\n", AUTHORIZE_SERVER_NAME,
					svs.authorizeAddress.ip[0], svs.authorizeAddress.ip[1],
					svs.authorizeAddress.ip[2], svs.authorizeAddress.ip[3],
					BigShort( svs.authorizeAddress.port ) );
			}
		}

		// we couldn't contact the auth server, let them in.
		if(svs.authorizeAddress.type == NA_BAD)
			Com_Printf("Couldn't resolve auth server address\n");

		// if they have been challenging for a long time and we
		// haven't heard anything from the authorize server, go ahead and
		// let them in, assuming the id server is down
		else if(svs.time - oldestClientTime > AUTHORIZE_TIMEOUT)
			Com_DPrintf( "authorize server timed out\n" );
		else
		{
			// otherwise send their ip to the authorize server
			const char *game;

			Com_DPrintf( "sending getIpAuthorize for %s\n", NET_AdrToString( from ));
		
			game = Cvar_VariableString( "fs_game" );
			if (game[0] == 0) {
				game = BASEGAME;
			}
			
			// the 0 is for backwards compatibility with obsolete sv_allowanonymous flags
			// getIpAuthorize <challenge> <IP> <game> 0 <auth-flag>
			NET_OutOfBandPrint( NS_SERVER, svs.authorizeAddress,
				"getIpAuthorize %i %i.%i.%i.%i %s 0 %s",  challenge->challenge,
				from.ip[0], from.ip[1], from.ip[2], from.ip[3], game, sv_strictAuth->string );
			
			return;
		}
	}
#endif

	challenge->pingTime = svs.time;
	NET_OutOfBandPrint(NS_SERVER, challenge->adr, "challengeResponse %d %d %d",
			   challenge->challenge, clientChallenge, com_protocol->integer);
}