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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {size_t iteminfo; int entitynum; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ levelitem_t ;
struct TYPE_10__ {TYPE_1__* iteminfo; } ;
typedef  TYPE_3__ itemconfig_t ;
struct TYPE_11__ {scalar_t__* origin; scalar_t__* lastvisorigin; } ;
typedef  TYPE_4__ aas_entityinfo_t ;
struct TYPE_8__ {int modelindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_EntityInfo (int,TYPE_4__*) ; 
 int AAS_EntityModelindex (int) ; 
 int AAS_NextEntity (int) ; 
 int VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* itemconfig ; 

void BotFindEntityForLevelItem(levelitem_t *li)
{
	int ent, modelindex;
	itemconfig_t *ic;
	aas_entityinfo_t entinfo;
	vec3_t dir;

	ic = itemconfig;
	if (!itemconfig) return;
	for (ent = AAS_NextEntity(0); ent; ent = AAS_NextEntity(ent))
	{
		//get the model index of the entity
		modelindex = AAS_EntityModelindex(ent);
		//
		if (!modelindex) continue;
		//get info about the entity
		AAS_EntityInfo(ent, &entinfo);
		//if the entity is still moving
		if (entinfo.origin[0] != entinfo.lastvisorigin[0] ||
				entinfo.origin[1] != entinfo.lastvisorigin[1] ||
				entinfo.origin[2] != entinfo.lastvisorigin[2]) continue;
		//
		if (ic->iteminfo[li->iteminfo].modelindex == modelindex)
		{
			//check if the entity is very close
			VectorSubtract(li->origin, entinfo.origin, dir);
			if (VectorLength(dir) < 30)
			{
				//found an entity for this level item
				li->entitynum = ent;
			} //end if
		} //end if
	} //end for
}