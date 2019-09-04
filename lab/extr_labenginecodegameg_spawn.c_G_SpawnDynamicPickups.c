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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_5__ {int numSpawnVars; int /*<<< orphan*/  spawning; scalar_t__ spawnVarChars; scalar_t__** spawnVars; scalar_t__ numSpawnVarChars; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_DROPPED_ITEM ; 
 TYPE_1__* G_SpawnGEntityFromSpawnVars () ; 
 int MAX_SPAWN_VARS ; 
 int /*<<< orphan*/  dmlab_clear_dynamic_spawn_entities () ; 
 int dmlab_dynamic_spawn_entity_count () ; 
 int /*<<< orphan*/  dmlab_read_dynamic_spawn_entity (int,scalar_t__,scalar_t__*,int**,int*) ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void G_SpawnDynamicPickups( void ) {
	gentity_t* ent;
	int i, ent_id, entity_count;
	int spawnVarsOffset[MAX_SPAWN_VARS][2];	// key / value pairs offsets
	entity_count = dmlab_dynamic_spawn_entity_count();
	if (entity_count == 0) {
		return;
	}

	level.spawning = qtrue;
	level.numSpawnVars = 0;

	for (ent_id = 0; ent_id < entity_count; ++ent_id) {
		level.numSpawnVars = 0;
		level.numSpawnVarChars = 0;

		dmlab_read_dynamic_spawn_entity(
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
		ent = G_SpawnGEntityFromSpawnVars();
		if (ent) ent->flags |= FL_DROPPED_ITEM;
	}
	dmlab_clear_dynamic_spawn_entities();
	level.spawning = qfalse;
}