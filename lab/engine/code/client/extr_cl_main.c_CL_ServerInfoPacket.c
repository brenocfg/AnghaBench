#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_16__ {int type; } ;
typedef  TYPE_1__ netadr_t ;
typedef  int /*<<< orphan*/  msg_t ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_22__ {scalar_t__ port; } ;
struct TYPE_21__ {char* info; scalar_t__ time; scalar_t__ start; TYPE_8__ adr; } ;
struct TYPE_20__ {scalar_t__ pingUpdateSource; int numlocalservers; TYPE_13__* localServers; } ;
struct TYPE_19__ {int /*<<< orphan*/  string; } ;
struct TYPE_18__ {int integer; } ;
struct TYPE_17__ {int integer; } ;
struct TYPE_15__ {TYPE_8__ adr; } ;

/* Variables and functions */
 scalar_t__ AS_LOCAL ; 
 int /*<<< orphan*/  CL_InitServerInfo (TYPE_13__*,TYPE_1__*) ; 
 int /*<<< orphan*/  CL_SetServerInfoByAddress (TYPE_1__,char*,scalar_t__) ; 
 int /*<<< orphan*/  Com_DPrintf (char*,...) ; 
 int /*<<< orphan*/  Com_Printf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Info_SetValueForKey (char*,char*,int /*<<< orphan*/ ) ; 
 char* Info_ValueForKey (char*,char*) ; 
 int MAX_INFO_STRING ; 
 int MAX_OTHER_SERVERS ; 
 int MAX_PINGREQUESTS ; 
 char* MSG_ReadString (int /*<<< orphan*/ *) ; 
#define  NA_BROADCAST 130 
#define  NA_IP 129 
#define  NA_IP6 128 
 int /*<<< orphan*/  NET_AdrToString (TYPE_1__) ; 
 int /*<<< orphan*/  NET_AdrToStringwPort (TYPE_1__) ; 
 scalar_t__ NET_CompareAdr (TYPE_1__,TYPE_8__) ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 
 scalar_t__ Sys_Milliseconds () ; 
 int atoi (char*) ; 
 TYPE_6__* cl_pinglist ; 
 TYPE_5__ cls ; 
 TYPE_4__* com_gamename ; 
 TYPE_3__* com_legacyprotocol ; 
 TYPE_2__* com_protocol ; 
 int qfalse ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  va (char*,int) ; 

void CL_ServerInfoPacket( netadr_t from, msg_t *msg ) {
	int		i, type;
	char	info[MAX_INFO_STRING];
	char	*infoString;
	int		prot;
	char	*gamename;
	qboolean gameMismatch;

	infoString = MSG_ReadString( msg );

	// if this isn't the correct gamename, ignore it
	gamename = Info_ValueForKey( infoString, "gamename" );

#ifdef LEGACY_PROTOCOL
	// gamename is optional for legacy protocol
	if (com_legacyprotocol->integer && !*gamename)
		gameMismatch = qfalse;
	else
#endif
		gameMismatch = !*gamename || strcmp(gamename, com_gamename->string) != 0;

	if (gameMismatch)
	{
		Com_DPrintf( "Game mismatch in info packet: %s\n", infoString );
		return;
	}

	// if this isn't the correct protocol version, ignore it
	prot = atoi( Info_ValueForKey( infoString, "protocol" ) );

	if(prot != com_protocol->integer
#ifdef LEGACY_PROTOCOL
	   && prot != com_legacyprotocol->integer
#endif
	  )
	{
		Com_DPrintf( "Different protocol info packet: %s\n", infoString );
		return;
	}

	// iterate servers waiting for ping response
	for (i=0; i<MAX_PINGREQUESTS; i++)
	{
		if ( cl_pinglist[i].adr.port && !cl_pinglist[i].time && NET_CompareAdr( from, cl_pinglist[i].adr ) )
		{
			// calc ping time
			cl_pinglist[i].time = Sys_Milliseconds() - cl_pinglist[i].start;
			Com_DPrintf( "ping time %dms from %s\n", cl_pinglist[i].time, NET_AdrToString( from ) );

			// save of info
			Q_strncpyz( cl_pinglist[i].info, infoString, sizeof( cl_pinglist[i].info ) );

			// tack on the net type
			// NOTE: make sure these types are in sync with the netnames strings in the UI
			switch (from.type)
			{
				case NA_BROADCAST:
				case NA_IP:
					type = 1;
					break;
				case NA_IP6:
					type = 2;
					break;
				default:
					type = 0;
					break;
			}
			Info_SetValueForKey( cl_pinglist[i].info, "nettype", va("%d", type) );
			CL_SetServerInfoByAddress(from, infoString, cl_pinglist[i].time);

			return;
		}
	}

	// if not just sent a local broadcast or pinging local servers
	if (cls.pingUpdateSource != AS_LOCAL) {
		return;
	}

	for ( i = 0 ; i < MAX_OTHER_SERVERS ; i++ ) {
		// empty slot
		if ( cls.localServers[i].adr.port == 0 ) {
			break;
		}

		// avoid duplicate
		if ( NET_CompareAdr( from, cls.localServers[i].adr ) ) {
			return;
		}
	}

	if ( i == MAX_OTHER_SERVERS ) {
		Com_DPrintf( "MAX_OTHER_SERVERS hit, dropping infoResponse\n" );
		return;
	}

	// add this to the list
	cls.numlocalservers = i+1;
	CL_InitServerInfo( &cls.localServers[i], &from );

	Q_strncpyz( info, MSG_ReadString( msg ), MAX_INFO_STRING );
	if (strlen(info)) {
		if (info[strlen(info)-1] != '\n') {
			Q_strcat(info, sizeof(info), "\n");
		}
		Com_Printf( "%s: %s", NET_AdrToStringwPort( from ), info );
	}
}