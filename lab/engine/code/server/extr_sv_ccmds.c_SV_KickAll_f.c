#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_9__ {TYPE_1__ remoteAddress; } ;
struct TYPE_10__ {int /*<<< orphan*/  lastPacketTime; TYPE_2__ netchan; int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ client_t ;
struct TYPE_13__ {int /*<<< orphan*/  integer; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {int /*<<< orphan*/  time; TYPE_3__* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 scalar_t__ NA_LOOPBACK ; 
 int /*<<< orphan*/  SV_DropClient (TYPE_3__*,char*) ; 
 TYPE_6__* com_sv_running ; 
 TYPE_5__* sv_maxclients ; 
 TYPE_4__ svs ; 

__attribute__((used)) static void SV_KickAll_f( void ) {
	client_t *cl;
	int i;

	// make sure server is running
	if( !com_sv_running->integer ) {
		Com_Printf( "Server is not running.\n" );
		return;
	}

	for( i = 0, cl = svs.clients; i < sv_maxclients->integer; i++, cl++ ) {
		if( !cl->state ) {
			continue;
		}

		if( cl->netchan.remoteAddress.type == NA_LOOPBACK ) {
			continue;
		}

		SV_DropClient( cl, "was kicked" );
		cl->lastPacketTime = svs.time; // in case there is a funny zombie
	}
}