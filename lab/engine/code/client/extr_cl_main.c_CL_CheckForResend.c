#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_16__ {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int state; scalar_t__ connectTime; int challenge; TYPE_7__ serverAddress; int /*<<< orphan*/  compat; int /*<<< orphan*/  connectPacketCount; scalar_t__ demoplaying; } ;
struct TYPE_14__ {scalar_t__ realtime; } ;
struct TYPE_13__ {int /*<<< orphan*/  string; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {int integer; } ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
#define  CA_CHALLENGING 129 
#define  CA_CONNECTING 128 
 int /*<<< orphan*/  CL_RequestAuthorization () ; 
 int /*<<< orphan*/  CVAR_USERINFO ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  Cvar_InfoString (int /*<<< orphan*/ ) ; 
 int Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,int /*<<< orphan*/ ) ; 
 int MAX_INFO_STRING ; 
 int /*<<< orphan*/  NA_IP ; 
 int /*<<< orphan*/  NET_OutOfBandData (int /*<<< orphan*/ ,TYPE_7__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_OutOfBandPrint (int /*<<< orphan*/ ,TYPE_7__,char*,char*) ; 
 int /*<<< orphan*/  NS_CLIENT ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RETRANSMIT_TIMEOUT ; 
 int /*<<< orphan*/  Sys_IsLANAddress (TYPE_7__) ; 
 TYPE_6__ clc ; 
 TYPE_5__ cls ; 
 TYPE_4__* com_gamename ; 
 TYPE_3__* com_legacyprotocol ; 
 TYPE_2__* com_protocol ; 
 TYPE_1__* com_standalone ; 
 int /*<<< orphan*/  cvar_modifiedFlags ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  va (char*,int) ; 

void CL_CheckForResend( void ) {
	int		port;
	char	info[MAX_INFO_STRING];
	char	data[MAX_INFO_STRING + 10];

	// don't send anything if playing back a demo
	if ( clc.demoplaying ) {
		return;
	}

	// resend if we haven't gotten a reply yet
	if ( clc.state != CA_CONNECTING && clc.state != CA_CHALLENGING ) {
		return;
	}

	if ( cls.realtime - clc.connectTime < RETRANSMIT_TIMEOUT ) {
		return;
	}

	clc.connectTime = cls.realtime;	// for retransmit requests
	clc.connectPacketCount++;


	switch ( clc.state ) {
	case CA_CONNECTING:
		// requesting a challenge .. IPv6 users always get in as authorize server supports no ipv6.
#ifndef STANDALONE
		if (!com_standalone->integer && clc.serverAddress.type == NA_IP && !Sys_IsLANAddress( clc.serverAddress ) )
			CL_RequestAuthorization();
#endif

		// The challenge request shall be followed by a client challenge so no malicious server can hijack this connection.
		// Add the gamename so the server knows we're running the correct game or can reject the client
		// with a meaningful message
		Com_sprintf(data, sizeof(data), "getchallenge %d %s", clc.challenge, com_gamename->string);

		NET_OutOfBandPrint(NS_CLIENT, clc.serverAddress, "%s", data);
		break;
		
	case CA_CHALLENGING:
		// sending back the challenge
		port = Cvar_VariableValue ("net_qport");

		Q_strncpyz( info, Cvar_InfoString( CVAR_USERINFO ), sizeof( info ) );
		
#ifdef LEGACY_PROTOCOL
		if(com_legacyprotocol->integer == com_protocol->integer)
			clc.compat = qtrue;

		if(clc.compat)
			Info_SetValueForKey(info, "protocol", va("%i", com_legacyprotocol->integer));
		else
#endif
			Info_SetValueForKey(info, "protocol", va("%i", com_protocol->integer));
		Info_SetValueForKey( info, "qport", va("%i", port ) );
		Info_SetValueForKey( info, "challenge", va("%i", clc.challenge ) );
		
		Com_sprintf( data, sizeof(data), "connect \"%s\"", info );
		NET_OutOfBandData( NS_CLIENT, clc.serverAddress, (byte *) data, strlen ( data ) );
		// the most current userinfo has been sent, so watch for any
		// newer changes to userinfo variables
		cvar_modifiedFlags &= ~CVAR_USERINFO;
		break;

	default:
		Com_Error( ERR_FATAL, "CL_CheckForResend: bad clc.state" );
	}
}