#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_17__ {scalar_t__ giType; int /*<<< orphan*/  classname; } ;
typedef  TYPE_4__ gitem_t ;
struct TYPE_15__ {int /*<<< orphan*/  trDelta; scalar_t__ trTime; int /*<<< orphan*/  trType; } ;
struct TYPE_16__ {int modelindex2; int /*<<< orphan*/  eFlags; TYPE_2__ pos; TYPE_4__* modelindex; int /*<<< orphan*/  eType; } ;
struct TYPE_14__ {int /*<<< orphan*/  contents; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
struct TYPE_18__ {int /*<<< orphan*/  flags; scalar_t__ nextthink; int /*<<< orphan*/  think; TYPE_3__ s; int /*<<< orphan*/  touch; TYPE_1__ r; TYPE_4__* item; int /*<<< orphan*/  classname; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_20__ {scalar_t__ integer; } ;
struct TYPE_19__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENTS_TRIGGER ; 
 int /*<<< orphan*/  EF_BOUNCE_HALF ; 
 int /*<<< orphan*/  ET_ITEM ; 
 int /*<<< orphan*/  FL_DROPPED_ITEM ; 
 scalar_t__ GT_CTF ; 
 int /*<<< orphan*/  G_FreeEntity ; 
 int /*<<< orphan*/  G_SetOrigin (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* G_Spawn () ; 
 int /*<<< orphan*/  ITEM_RADIUS ; 
 scalar_t__ IT_TEAM ; 
 int /*<<< orphan*/  TR_GRAVITY ; 
 int /*<<< orphan*/  Team_CheckDroppedItem (TYPE_5__*) ; 
 int /*<<< orphan*/  Team_DroppedFlagThink ; 
 int /*<<< orphan*/  Touch_Item ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bg_itemlist ; 
 TYPE_8__ g_gametype ; 
 TYPE_7__ level ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_5__*) ; 

gentity_t *LaunchItem( gitem_t *item, vec3_t origin, vec3_t velocity ) {
	gentity_t	*dropped;

	dropped = G_Spawn();

	dropped->s.eType = ET_ITEM;
	dropped->s.modelindex = item - bg_itemlist;	// store item number in modelindex
	dropped->s.modelindex2 = 1; // This is non-zero is it's a dropped item

	dropped->classname = item->classname;
	dropped->item = item;
	VectorSet (dropped->r.mins, -ITEM_RADIUS, -ITEM_RADIUS, -ITEM_RADIUS);
	VectorSet (dropped->r.maxs, ITEM_RADIUS, ITEM_RADIUS, ITEM_RADIUS);
	dropped->r.contents = CONTENTS_TRIGGER;

	dropped->touch = Touch_Item;

	G_SetOrigin( dropped, origin );
	dropped->s.pos.trType = TR_GRAVITY;
	dropped->s.pos.trTime = level.time;
	VectorCopy( velocity, dropped->s.pos.trDelta );

	dropped->s.eFlags |= EF_BOUNCE_HALF;
#ifdef MISSIONPACK
	if ((g_gametype.integer == GT_CTF || g_gametype.integer == GT_1FCTF)			&& item->giType == IT_TEAM) { // Special case for CTF flags
#else
	if (g_gametype.integer == GT_CTF && item->giType == IT_TEAM) { // Special case for CTF flags
#endif
		dropped->think = Team_DroppedFlagThink;
		dropped->nextthink = level.time + 30000;
		Team_CheckDroppedItem( dropped );
	} else { // auto-remove after 30 seconds
		dropped->think = G_FreeEntity;
		dropped->nextthink = level.time + 30000;
	}

	dropped->flags = FL_DROPPED_ITEM;

	trap_LinkEntity (dropped);

	return dropped;
}