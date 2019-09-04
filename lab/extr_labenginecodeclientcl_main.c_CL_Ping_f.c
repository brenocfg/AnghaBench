#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  adr; scalar_t__ time; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ ping_t ;
typedef  int /*<<< orphan*/  netadrtype_t ;
typedef  int /*<<< orphan*/  netadr_t ;

/* Variables and functions */
 TYPE_1__* CL_GetFreePing () ; 
 int /*<<< orphan*/  CL_SetServerInfoByAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Cmd_Argc () ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  NA_IP ; 
 int /*<<< orphan*/  NA_IP6 ; 
 int /*<<< orphan*/  NA_UNSPEC ; 
 int /*<<< orphan*/  NET_OutOfBandPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NET_StringToAdr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_CLIENT ; 
 int /*<<< orphan*/  Sys_Milliseconds () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void CL_Ping_f( void ) {
	netadr_t	to;
	ping_t*		pingptr;
	char*		server;
	int			argc;
	netadrtype_t	family = NA_UNSPEC;

	argc = Cmd_Argc();

	if ( argc != 2 && argc != 3 ) {
		Com_Printf( "usage: ping [-4|-6] server\n");
		return;	
	}
	
	if(argc == 2)
		server = Cmd_Argv(1);
	else
	{
		if(!strcmp(Cmd_Argv(1), "-4"))
			family = NA_IP;
		else if(!strcmp(Cmd_Argv(1), "-6"))
			family = NA_IP6;
		else
			Com_Printf( "warning: only -4 or -6 as address type understood.\n");
		
		server = Cmd_Argv(2);
	}

	Com_Memset( &to, 0, sizeof(netadr_t) );

	if ( !NET_StringToAdr( server, &to, family ) ) {
		return;
	}

	pingptr = CL_GetFreePing();

	memcpy( &pingptr->adr, &to, sizeof (netadr_t) );
	pingptr->start = Sys_Milliseconds();
	pingptr->time  = 0;

	CL_SetServerInfoByAddress(pingptr->adr, NULL, 0);
		
	NET_OutOfBandPrint( NS_CLIENT, to, "getinfo xxx" );
}