#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_15__ {int* endpos; int /*<<< orphan*/  entityNum; scalar_t__ startsolid; } ;
typedef  TYPE_4__ trace_t ;
struct TYPE_14__ {scalar_t__ contents; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_13__ {int* origin; int /*<<< orphan*/  eFlags; int /*<<< orphan*/  groundEntityNum; int /*<<< orphan*/  number; scalar_t__ modelindex2; TYPE_1__* modelindex; int /*<<< orphan*/  eType; } ;
struct TYPE_16__ {int spawnflags; int flags; int /*<<< orphan*/  think; scalar_t__ nextthink; TYPE_3__ r; TYPE_2__ s; TYPE_1__* item; scalar_t__ targetname; int /*<<< orphan*/  classname; int /*<<< orphan*/  use; int /*<<< orphan*/  touch; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_17__ {scalar_t__ time; } ;
struct TYPE_12__ {scalar_t__ giType; } ;

/* Variables and functions */
 scalar_t__ CONTENTS_TRIGGER ; 
 int /*<<< orphan*/  EF_NODRAW ; 
 int /*<<< orphan*/  ET_ITEM ; 
 int FL_TEAMSLAVE ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_5__*) ; 
 int /*<<< orphan*/  G_Printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_5__*,int*) ; 
 int ITEM_RADIUS ; 
 scalar_t__ IT_POWERUP ; 
 int /*<<< orphan*/  MASK_SOLID ; 
 int /*<<< orphan*/  RespawnItem ; 
 int /*<<< orphan*/  Touch_Item ; 
 int /*<<< orphan*/  Use_Item ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int,int,int) ; 
 int bg_itemlist ; 
 int crandom () ; 
 TYPE_8__ level ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_5__*) ; 
 int /*<<< orphan*/  trap_Trace (TYPE_4__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtos (int*) ; 

void FinishSpawningItem( gentity_t *ent ) {
	trace_t		tr;
	vec3_t		dest;

	VectorSet( ent->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS );
	VectorSet( ent->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS );

	ent->s.eType = ET_ITEM;
	ent->s.modelindex = ent->item - bg_itemlist;		// store item number in modelindex
	ent->s.modelindex2 = 0; // zero indicates this isn't a dropped item

	ent->r.contents = CONTENTS_TRIGGER;
	ent->touch = Touch_Item;
	// using an item causes it to respawn
	ent->use = Use_Item;

	if ( ent->spawnflags & 1 ) {
		// suspended
		G_SetOrigin( ent, ent->s.origin );
	} else {
		// drop to floor
		VectorSet( dest, ent->s.origin[0], ent->s.origin[1], ent->s.origin[2] - 4096 );
		trap_Trace( &tr, ent->s.origin, ent->r.mins, ent->r.maxs, dest, ent->s.number, MASK_SOLID );
		if ( tr.startsolid ) {
			G_Printf ("FinishSpawningItem: %s startsolid at %s\n", ent->classname, vtos(ent->s.origin));
			G_FreeEntity( ent );
			return;
		}

		// allow to ride movers
		ent->s.groundEntityNum = tr.entityNum;

		G_SetOrigin( ent, tr.endpos );
	}

	// team slaves and targeted items aren't present at start
	if ( ( ent->flags & FL_TEAMSLAVE ) || ent->targetname ) {
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		return;
	}

	// powerups don't spawn in for a while
	if ( ent->item->giType == IT_POWERUP ) {
		float	respawn;

		respawn = 45 + crandom() * 15;
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		ent->nextthink = level.time + respawn * 1000;
		ent->think = RespawnItem;
		return;
	}


	trap_LinkEntity (ent);
}