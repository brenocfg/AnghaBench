#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  gameState; } ;
struct TYPE_9__ {scalar_t__ state; int lastPacketSentTime; int /*<<< orphan*/  serverAddress; int /*<<< orphan*/  servername; int /*<<< orphan*/  connectTime; int /*<<< orphan*/ * serverMessage; } ;
struct TYPE_8__ {int /*<<< orphan*/ * updateInfoString; } ;
struct TYPE_7__ {int /*<<< orphan*/  integer; } ;
struct TYPE_6__ {scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ CA_CHALLENGING ; 
 scalar_t__ CA_CONNECTED ; 
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  CL_CheckForResend () ; 
 int /*<<< orphan*/  CL_Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Con_Close () ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  KEYCATCH_CONSOLE ; 
 int /*<<< orphan*/  Key_SetCatcher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NA_UNSPEC ; 
 int /*<<< orphan*/  NET_StringToAdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RETRANSMIT_TIMEOUT ; 
 int /*<<< orphan*/  SCR_UpdateScreen () ; 
 TYPE_5__ cl ; 
 TYPE_4__ clc ; 
 TYPE_3__ cls ; 
 TYPE_2__* com_cl_running ; 
 TYPE_1__* com_dedicated ; 
 int /*<<< orphan*/  qtrue ; 

void CL_MapLoading( void ) {
	if ( com_dedicated->integer ) {
		clc.state = CA_DISCONNECTED;
		Key_SetCatcher( KEYCATCH_CONSOLE );
		return;
	}

	if ( !com_cl_running->integer ) {
		return;
	}

	Con_Close();
	Key_SetCatcher( 0 );

	// if we are already connected to the local host, stay connected
	if ( clc.state >= CA_CONNECTED && !Q_stricmp( clc.servername, "localhost" ) ) {
		clc.state = CA_CONNECTED;		// so the connect screen is drawn
		Com_Memset( cls.updateInfoString, 0, sizeof( cls.updateInfoString ) );
		Com_Memset( clc.serverMessage, 0, sizeof( clc.serverMessage ) );
		Com_Memset( &cl.gameState, 0, sizeof( cl.gameState ) );
		clc.lastPacketSentTime = -9999;
		SCR_UpdateScreen();
	} else {
		// clear nextmap so the cinematic shutdown doesn't execute it
		Cvar_Set( "nextmap", "" );
		CL_Disconnect( qtrue );
		Q_strncpyz( clc.servername, "localhost", sizeof(clc.servername) );
		clc.state = CA_CHALLENGING;		// so the connect screen is drawn
		Key_SetCatcher( 0 );
		SCR_UpdateScreen();
		clc.connectTime = -RETRANSMIT_TIMEOUT;
		NET_StringToAdr( clc.servername, &clc.serverAddress, NA_UNSPEC);
		// we don't need a challenge on the localhost

		CL_CheckForResend();
	}
}