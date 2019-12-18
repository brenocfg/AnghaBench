#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int SPAWNFLAG_NOT_DEATHMATCH ; 
 char* ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Warning (char*,int,char*,char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/ * entities ; 
 int* mark_entities ; 
 int num_entities ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int AAS_AlwaysTriggered_r(char *targetname)
{
	int i;

	if (!strlen(targetname)) {
		return false;
	}
	//
	for (i = 0; i < num_entities; i++) {
		// if the entity will activate the given targetname
		if ( !strcmp(targetname, ValueForKey(&entities[i], "target")) ) {
			// if this activator is present in deathmatch
			if (!(atoi(ValueForKey(&entities[i], "spawnflags")) & SPAWNFLAG_NOT_DEATHMATCH)) {
				// if it is a trigger_always entity
				if (!strcmp("trigger_always", ValueForKey(&entities[i], "classname"))) {
					return true;
				}
				// check for possible trigger_always entities activating this entity
				if ( mark_entities[i] ) {
					Warning( "entity %d, classname %s has recursive targetname %s\n", i,
										ValueForKey(&entities[i], "classname"), targetname );
					return false;
				}
				mark_entities[i] = true;
				if ( AAS_AlwaysTriggered_r(ValueForKey(&entities[i], "targetname")) ) {
					return true;
				}
			}
		}
	}
	return false;
}