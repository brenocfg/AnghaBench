#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  client_t ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {scalar_t__ integer; } ;
struct TYPE_6__ {int integer; } ;
struct TYPE_5__ {int numSnapshotEntities; scalar_t__ initialized; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int MAX_SNAPSHOT_ENTITIES ; 
 int /*<<< orphan*/  NET_JoinMulticast6 () ; 
 int PACKET_BACKUP ; 
 int /*<<< orphan*/  SV_BoundMaxClients (int) ; 
 int /*<<< orphan*/  Z_Malloc (int) ; 
 TYPE_4__* com_dedicated ; 
 scalar_t__ qtrue ; 
 TYPE_3__* sv_killserver ; 
 TYPE_2__* sv_maxclients ; 
 TYPE_1__ svs ; 

__attribute__((used)) static void SV_Startup( void ) {
	if ( svs.initialized ) {
		Com_Error( ERR_FATAL, "SV_Startup: svs.initialized" );
	}
	SV_BoundMaxClients( 1 );

	svs.clients = Z_Malloc (sizeof(client_t) * sv_maxclients->integer );
	if ( com_dedicated->integer ) {
		svs.numSnapshotEntities = sv_maxclients->integer * PACKET_BACKUP * MAX_SNAPSHOT_ENTITIES;
	} else {
		// we don't need nearly as many when playing locally
		svs.numSnapshotEntities = sv_maxclients->integer * 4 * MAX_SNAPSHOT_ENTITIES;
	}
	svs.initialized = qtrue;

	// Don't respect sv_killserver unless a server is actually running
	if ( sv_killserver->integer ) {
		Cvar_Set( "sv_killserver", "0" );
	}

	Cvar_Set( "sv_running", "1" );
	
	// Join the ipv6 multicast group now that a map is running so clients can scan for us on the local network.
	NET_JoinMulticast6();
}