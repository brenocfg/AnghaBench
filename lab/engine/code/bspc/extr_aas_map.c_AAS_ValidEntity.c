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
typedef  int /*<<< orphan*/  entity_t ;

/* Variables and functions */
 scalar_t__ AAS_AlwaysTriggered (int /*<<< orphan*/ ) ; 
 int SPAWNFLAG_NOT_DEATHMATCH ; 
 int /*<<< orphan*/  ValueForKey (int /*<<< orphan*/ *,char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * entities ; 
 int num_entities ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

int AAS_ValidEntity(entity_t *mapent)
{
	int i;
	char target[1024];

	//all world brushes are used for AAS
	if (mapent == &entities[0])
	{
		return true;
	} //end if
	//some of the func_wall brushes are also used for AAS
	else if (!strcmp("func_wall", ValueForKey(mapent, "classname")))
	{
		//Log_Print("found func_wall entity %d\n", mapent - entities);
		//if the func wall is used in deathmatch
		if (!(atoi(ValueForKey(mapent, "spawnflags")) & SPAWNFLAG_NOT_DEATHMATCH))
		{
			//Log_Print("func_wall USED in deathmatch mode %d\n", atoi(ValueForKey(mapent, "spawnflags")));
			return true;
		} //end if
	} //end else if
	else if (!strcmp("func_door_rotating", ValueForKey(mapent, "classname")))
	{
		//if the func_door_rotating is present in deathmatch
		if (!(atoi(ValueForKey(mapent, "spawnflags")) & SPAWNFLAG_NOT_DEATHMATCH))
		{
			//if the func_door_rotating is always activated in deathmatch
			if (AAS_AlwaysTriggered(ValueForKey(mapent, "targetname")))
			{
				//Log_Print("found func_door_rotating in deathmatch\ntargetname %s\n", ValueForKey(mapent, "targetname"));
				return true;
			} //end if
		} //end if
	} //end else if
	else if (!strcmp("trigger_hurt", ValueForKey(mapent, "classname")))
	{
		//"dmg" is the damage, for instance: "dmg" "666"
		return true;
	} //end else if
	else if (!strcmp("trigger_push", ValueForKey(mapent, "classname")))
	{
		return true;
	} //end else if
	else if (!strcmp("trigger_multiple", ValueForKey(mapent, "classname")))
	{
		//find out if the trigger_multiple is pointing to a target_teleporter
		strcpy(target, ValueForKey(mapent, "target"));
		for (i = 0; i < num_entities; i++)
		{
			//if the entity will activate the given targetname
			if (!strcmp(target, ValueForKey(&entities[i], "targetname")))
			{
				if (!strcmp("target_teleporter", ValueForKey(&entities[i], "classname")))
				{
					return true;
				} //end if
			} //end if
		} //end for
	} //end else if
	else if (!strcmp("trigger_teleport", ValueForKey(mapent, "classname")))
	{
		return true;
	} //end else if
	else if (!strcmp("func_static", ValueForKey(mapent, "classname")))
	{
		//FIXME: easy/medium/hard/deathmatch specific?
		return true;
	} //end else if
	else if (!strcmp("func_door", ValueForKey(mapent, "classname")))
	{
		return true;
	} //end else if
	return false;
}