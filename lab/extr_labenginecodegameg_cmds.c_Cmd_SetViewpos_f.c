#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
typedef  int /*<<< orphan*/  gentity_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 int MAX_TOKEN_CHARS ; 
 int /*<<< orphan*/  TeleportPlayer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ *) ; 
 size_t YAW ; 
 int /*<<< orphan*/  atof (char*) ; 
 TYPE_1__ g_cheats ; 
 int g_entities ; 
 int trap_Argc () ; 
 int /*<<< orphan*/  trap_Argv (int,char*,int) ; 
 int /*<<< orphan*/  trap_SendServerCommand (int /*<<< orphan*/ *,char*) ; 

void Cmd_SetViewpos_f( gentity_t *ent ) {
	vec3_t		origin, angles;
	char		buffer[MAX_TOKEN_CHARS];
	int			i;

	if ( !g_cheats.integer ) {
		trap_SendServerCommand( ent-g_entities, "print \"Cheats are not enabled on this server.\n\"");
		return;
	}
	if ( trap_Argc() != 5 ) {
		trap_SendServerCommand( ent-g_entities, "print \"usage: setviewpos x y z yaw\n\"");
		return;
	}

	VectorClear( angles );
	for ( i = 0 ; i < 3 ; i++ ) {
		trap_Argv( i + 1, buffer, sizeof( buffer ) );
		origin[i] = atof( buffer );
	}

	trap_Argv( 4, buffer, sizeof( buffer ) );
	angles[YAW] = atof( buffer );

	TeleportPlayer( ent, origin, angles );
}