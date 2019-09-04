#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ msg_t ;

/* Variables and functions */
 char* Cmd_Argv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cmd_TokenizeString (char*) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Huff_Decompress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSG_BeginReadingOOB (TYPE_1__*) ; 
 int /*<<< orphan*/  MSG_ReadLong (TYPE_1__*) ; 
 char* MSG_ReadStringLine (TYPE_1__*) ; 
 int /*<<< orphan*/  NET_AdrToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  Q_strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  SVC_Info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVC_RemoteCommand (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SVC_Status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_AuthorizeIpPacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_DirectConnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_GetChallenge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SV_ConnectionlessPacket( netadr_t from, msg_t *msg ) {
	char	*s;
	char	*c;

	MSG_BeginReadingOOB( msg );
	MSG_ReadLong( msg );		// skip the -1 marker

	if (!Q_strncmp("connect", (char *) &msg->data[4], 7)) {
		Huff_Decompress(msg, 12);
	}

	s = MSG_ReadStringLine( msg );
	Cmd_TokenizeString( s );

	c = Cmd_Argv(0);
	Com_DPrintf ("SV packet %s : %s\n", NET_AdrToString(from), c);

	if (!Q_stricmp(c, "getstatus")) {
		SVC_Status( from );
  } else if (!Q_stricmp(c, "getinfo")) {
		SVC_Info( from );
	} else if (!Q_stricmp(c, "getchallenge")) {
		SV_GetChallenge(from);
	} else if (!Q_stricmp(c, "connect")) {
		SV_DirectConnect( from );
#ifndef STANDALONE
	} else if (!Q_stricmp(c, "ipAuthorize")) {
		SV_AuthorizeIpPacket( from );
#endif
	} else if (!Q_stricmp(c, "rcon")) {
		SVC_RemoteCommand( from, msg );
	} else if (!Q_stricmp(c, "disconnect")) {
		// if a client starts up a local server, we may see some spurious
		// server disconnect messages when their new server sees our final
		// sequenced messages to the old client
	} else {
		Com_DPrintf ("bad connectionless packet from %s:\n%s\n",
			NET_AdrToString (from), s);
	}
}