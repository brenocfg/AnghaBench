#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int id; } ;
typedef  TYPE_1__ gentity_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_11__ {int /*<<< orphan*/  integer; } ;
struct TYPE_10__ {int num_entities; } ;

/* Variables and functions */
 int ClientNumberFromString (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_TOKEN_CHARS ; 
 int /*<<< orphan*/  Touch_Item (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 TYPE_4__ g_cheats ; 
 TYPE_1__* g_entities ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  qtrue ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_Argv (int,char*,int) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int,char*) ; 

void Cmd_Pickup_f( gentity_t *ent ) {
	gentity_t *e;
	int	id, i;
	char		buffer[MAX_TOKEN_CHARS];

	if ( !g_cheats.integer ) {
		trap_SendServerCommand( ent-g_entities, "print \"Cheats are not enabled on this server.\n\"" );
		return;
	}
	if ( trap_Argc() == 3 ) {
		trap_Argv( 2, buffer, sizeof( buffer ) );
		i = ClientNumberFromString( ent, buffer, qtrue, qtrue );
		if (i == -1) {
			trap_SendServerCommand( ent-g_entities, "print \"Invalid player name\n\"");
		return;
		}
		ent = &g_entities[i];
	} else if ( trap_Argc() != 2 ) {
		trap_SendServerCommand( ent-g_entities, "print \"usage: pickup id <optional player name>\n\"" );
		return;
	}
	trap_Argv( 1, buffer, sizeof( buffer ) );
	id = atoi( buffer );
	for (i = 0; i < level.num_entities; i++) {
		e = &g_entities[i];
		if (e->id && id == e->id) {
			Touch_Item( e, ent, NULL );
		}
	}
}