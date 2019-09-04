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
struct TYPE_2__ {int numSpawnVars; int** spawnVars; int spawnVarChars; int /*<<< orphan*/  spawning; scalar_t__ numSpawnVarChars; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_Error (char*) ; 
 scalar_t__ G_ParseSpawnVars () ; 
 int /*<<< orphan*/  G_SpawnGEntityFromSpawnVars () ; 
 int MAX_SPAWN_VARS ; 
 int /*<<< orphan*/  SP_worldspawn () ; 
 int dmlab_make_extra_entities () ; 
 int /*<<< orphan*/  dmlab_read_extra_entity (int,int,scalar_t__*,int**,int*) ; 
 int /*<<< orphan*/  dmlab_update_spawn_vars (int,scalar_t__*,int**,int*) ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void G_SpawnEntitiesFromString( void ) {
	// allow calls to G_Spawn*()
	int i, ent_id, extra_spawn_count;
	int spawnVarsOffset[MAX_SPAWN_VARS][2];	// key / value pairs offsets
	level.spawning = qtrue;
	level.numSpawnVars = 0;

	// the worldspawn is not an actual entity, but it still
	// has a "spawn" function to perform any global setup
	// needed by a level (setting configstrings or cvars, etc)
	if ( !G_ParseSpawnVars() ) {
		G_Error( "SpawnEntities: no entities" );
	}
	SP_worldspawn();

	// parse ents
	while( G_ParseSpawnVars() ) {
		// Convert to offsets.
		for (i = 0; i < level.numSpawnVars; ++i) {
			spawnVarsOffset[i][0] = level.spawnVars[i][0] - level.spawnVarChars;
			spawnVarsOffset[i][1] = level.spawnVars[i][1] - level.spawnVarChars;
		}

		// Skip if spawn is not required.
		if (!dmlab_update_spawn_vars(
				level.spawnVarChars,
				&level.numSpawnVarChars,
				spawnVarsOffset,
				&level.numSpawnVars)) {
			continue;
		}
		// Convert from offsets.
		for (i = 0; i < level.numSpawnVars; ++i) {
			level.spawnVars[i][0] = level.spawnVarChars + spawnVarsOffset[i][0];
			level.spawnVars[i][1] = level.spawnVarChars + spawnVarsOffset[i][1];
		}
		G_SpawnGEntityFromSpawnVars();
	}
	extra_spawn_count = dmlab_make_extra_entities();
	for (ent_id = 0; ent_id < extra_spawn_count; ++ent_id) {
		level.numSpawnVars = 0;
		level.numSpawnVarChars = 0;
		// Early out if spawn is not required.
		dmlab_read_extra_entity(
				ent_id,
				level.spawnVarChars,
				&level.numSpawnVarChars,
				spawnVarsOffset,
				&level.numSpawnVars);

		// Convert from offsets.
		for (i = 0; i < level.numSpawnVars; ++i) {
			level.spawnVars[i][0] = level.spawnVarChars + spawnVarsOffset[i][0];
			level.spawnVars[i][1] = level.spawnVarChars + spawnVarsOffset[i][1];
		}
		G_SpawnGEntityFromSpawnVars();
	}

	level.spawning = qfalse;			// any future calls to G_Spawn*() will be errors
}