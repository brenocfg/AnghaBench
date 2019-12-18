#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* pending; void* print; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ serverStatus_t ;
typedef  int /*<<< orphan*/  netadrtype_t ;
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  serverAddress; scalar_t__ demoplaying; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 TYPE_1__* CL_GetServerStatus (int /*<<< orphan*/ ) ; 
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
 TYPE_2__ clc ; 
 void* qtrue ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void CL_ServerStatus_f(void) {
	netadr_t	to, *toptr = NULL;
	char		*server;
	serverStatus_t *serverStatus;
	int			argc;
	netadrtype_t	family = NA_UNSPEC;

	argc = Cmd_Argc();

	if ( argc != 2 && argc != 3 )
	{
		if (clc.state != CA_ACTIVE || clc.demoplaying)
		{
			Com_Printf ("Not connected to a server.\n");
			Com_Printf( "usage: serverstatus [-4|-6] server\n");
			return;
		}

		toptr = &clc.serverAddress;
	}
	
	if(!toptr)
	{
		Com_Memset( &to, 0, sizeof(netadr_t) );
	
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

		toptr = &to;
		if ( !NET_StringToAdr( server, toptr, family ) )
			return;
	}

	NET_OutOfBandPrint( NS_CLIENT, *toptr, "getstatus" );

	serverStatus = CL_GetServerStatus( *toptr );
	serverStatus->address = *toptr;
	serverStatus->print = qtrue;
	serverStatus->pending = qtrue;
}