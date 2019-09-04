#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_9__ {TYPE_1__ remoteAddress; } ;
struct TYPE_10__ {scalar_t__ state; scalar_t__ lastSnapshotTime; TYPE_2__ netchan; } ;
typedef  TYPE_3__ client_t ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {TYPE_3__* clients; } ;

/* Variables and functions */
 scalar_t__ CS_CONNECTED ; 
 scalar_t__ NA_LOOPBACK ; 
 int /*<<< orphan*/  SV_SendClientSnapshot (TYPE_3__*) ; 
 int /*<<< orphan*/  SV_SendServerCommand (TYPE_3__*,char*,char*) ; 
 TYPE_5__* sv_maxclients ; 
 TYPE_4__ svs ; 

void SV_FinalMessage( char *message ) {
	int			i, j;
	client_t	*cl;
	
	// send it twice, ignoring rate
	for ( j = 0 ; j < 2 ; j++ ) {
		for (i=0, cl = svs.clients ; i < sv_maxclients->integer ; i++, cl++) {
			if (cl->state >= CS_CONNECTED) {
				// don't send a disconnect to a local client
				if ( cl->netchan.remoteAddress.type != NA_LOOPBACK ) {
					SV_SendServerCommand( cl, "print \"%s\n\"\n", message );
					SV_SendServerCommand( cl, "disconnect \"%s\"", message );
				}
				// force a snapshot to be sent
				cl->lastSnapshotTime = 0;
				SV_SendClientSnapshot( cl );
			}
		}
	}
}