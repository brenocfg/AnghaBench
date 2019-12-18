#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_8__ {int lastClientCommand; scalar_t__ state; scalar_t__ nextReliableTime; int /*<<< orphan*/  lastClientCommandString; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ client_t ;
struct TYPE_11__ {int /*<<< orphan*/  integer; } ;
struct TYPE_10__ {scalar_t__ integer; } ;
struct TYPE_9__ {scalar_t__ time; } ;

/* Variables and functions */
 scalar_t__ CS_ACTIVE ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_sprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int MSG_ReadLong (int /*<<< orphan*/ *) ; 
 char* MSG_ReadString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  SV_ExecuteClientCommand (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_4__* com_cl_running ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__* sv_floodProtect ; 
 TYPE_2__ svs ; 

__attribute__((used)) static qboolean SV_ClientCommand( client_t *cl, msg_t *msg ) {
	int		seq;
	const char	*s;
	qboolean clientOk = qtrue;

	seq = MSG_ReadLong( msg );
	s = MSG_ReadString( msg );

	// see if we have already executed it
	if ( cl->lastClientCommand >= seq ) {
		return qtrue;
	}

	Com_DPrintf( "clientCommand: %s : %i : %s\n", cl->name, seq, s );

	// drop the connection if we have somehow lost commands
	if ( seq > cl->lastClientCommand + 1 ) {
		Com_Printf( "Client %s lost %i clientCommands\n", cl->name, 
			seq - cl->lastClientCommand + 1 );
		SV_DropClient( cl, "Lost reliable commands" );
		return qfalse;
	}

	// malicious users may try using too many string commands
	// to lag other players.  If we decide that we want to stall
	// the command, we will stop processing the rest of the packet,
	// including the usercmd.  This causes flooders to lag themselves
	// but not other people
	// We don't do this when the client hasn't been active yet since it's
	// normal to spam a lot of commands when downloading
	if ( !com_cl_running->integer && 
		cl->state >= CS_ACTIVE &&
		sv_floodProtect->integer && 
		svs.time < cl->nextReliableTime ) {
		// ignore any other text messages from this client but let them keep playing
		// TTimo - moved the ignored verbose to the actual processing in SV_ExecuteClientCommand, only printing if the core doesn't intercept
		clientOk = qfalse;
	} 

	// don't allow another command for one second
	cl->nextReliableTime = svs.time + 1000;

	SV_ExecuteClientCommand( cl, s, clientOk );

	cl->lastClientCommand = seq;
	Com_sprintf(cl->lastClientCommandString, sizeof(cl->lastClientCommandString), "%s", s);

	return qtrue;		// continue procesing
}