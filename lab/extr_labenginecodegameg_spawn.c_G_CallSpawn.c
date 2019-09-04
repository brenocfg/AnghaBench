#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* spawn ) (TYPE_2__*) ;scalar_t__ name; } ;
typedef  TYPE_1__ spawn_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  gitem_t ;
struct TYPE_8__ {int /*<<< orphan*/  classname; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BG_FindItemByClassName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Printf (char*,...) ; 
 int /*<<< orphan*/  G_SpawnItem (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__* spawns ; 
 int /*<<< orphan*/  strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

qboolean G_CallSpawn( gentity_t *ent ) {
	spawn_t	*s;
	gitem_t	*item;

	if ( !ent->classname ) {
		G_Printf ("G_CallSpawn: NULL classname\n");
		return qfalse;
	}

	// check item spawn functions
	item = BG_FindItemByClassName( ent->classname );
	if ( item ) {
		G_SpawnItem( ent, item );
		return qtrue;
	}

	// check normal spawn functions
	for ( s=spawns ; s->name ; s++ ) {
		if ( !strcmp(s->name, ent->classname) ) {
			// found it
			s->spawn(ent);
			return qtrue;
		}
	}
	G_Printf ("%s doesn't have a spawn function\n", ent->classname);
	return qfalse;
}