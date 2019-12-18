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
struct TYPE_10__ {scalar_t__ state; TYPE_2__* gentity; int /*<<< orphan*/ * csUpdated; } ;
typedef  TYPE_3__ client_t ;
struct TYPE_13__ {scalar_t__ state; scalar_t__ restarting; int /*<<< orphan*/ * configstrings; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {TYPE_3__* clients; } ;
struct TYPE_8__ {int svFlags; } ;
struct TYPE_9__ {TYPE_1__ r; } ;

/* Variables and functions */
 scalar_t__ CS_ACTIVE ; 
 scalar_t__ CS_PRIMED ; 
 int CS_SERVERINFO ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  CopyString (char const*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_CONFIGSTRINGS ; 
 scalar_t__ SS_GAME ; 
 int SVF_NOSERVERINFO ; 
 int /*<<< orphan*/  SV_SendConfigstring (TYPE_3__*,int) ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_6__ sv ; 
 TYPE_5__* sv_maxclients ; 
 TYPE_4__ svs ; 

void SV_SetConfigstring (int index, const char *val) {
	int		i;
	client_t	*client;

	if ( index < 0 || index >= MAX_CONFIGSTRINGS ) {
		Com_Error (ERR_DROP, "SV_SetConfigstring: bad index %i", index);
	}

	if ( !val ) {
		val = "";
	}

	// don't bother broadcasting an update if no change
	if ( !strcmp( val, sv.configstrings[ index ] ) ) {
		return;
	}

	// change the string in sv
	Z_Free( sv.configstrings[index] );
	sv.configstrings[index] = CopyString( val );

	// send it to all the clients if we aren't
	// spawning a new server
	if ( sv.state == SS_GAME || sv.restarting ) {

		// send the data to all relevant clients
		for (i = 0, client = svs.clients; i < sv_maxclients->integer ; i++, client++) {
			if ( client->state < CS_ACTIVE ) {
				if ( client->state == CS_PRIMED )
					client->csUpdated[ index ] = qtrue;
				continue;
			}
			// do not always send server info to all clients
			if ( index == CS_SERVERINFO && client->gentity && (client->gentity->r.svFlags & SVF_NOSERVERINFO) ) {
				continue;
			}
		
			SV_SendConfigstring(client, index);
		}
	}
}