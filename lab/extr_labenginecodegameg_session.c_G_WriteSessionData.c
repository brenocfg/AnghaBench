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
struct TYPE_5__ {scalar_t__ connected; } ;
struct TYPE_8__ {TYPE_1__ pers; } ;
struct TYPE_7__ {int /*<<< orphan*/  integer; } ;
struct TYPE_6__ {int maxclients; TYPE_4__* clients; } ;

/* Variables and functions */
 scalar_t__ CON_CONNECTED ; 
 int /*<<< orphan*/  G_WriteClientSessionData (TYPE_4__*) ; 
 TYPE_3__ g_gametype ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  trap_Cvar_Set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void G_WriteSessionData( void ) {
	int		i;

	trap_Cvar_Set( "session", va("%i", g_gametype.integer) );

	for ( i = 0 ; i < level.maxclients ; i++ ) {
		if ( level.clients[i].pers.connected == CON_CONNECTED ) {
			G_WriteClientSessionData( &level.clients[i] );
		}
	}
}