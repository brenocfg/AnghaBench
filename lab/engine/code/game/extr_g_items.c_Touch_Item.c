#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_37__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_43__ {scalar_t__ contents; int /*<<< orphan*/  svFlags; int /*<<< orphan*/  singleClient; } ;
struct TYPE_42__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_40__ {int /*<<< orphan*/  eFlags; int /*<<< orphan*/  number; int /*<<< orphan*/  modelindex; int /*<<< orphan*/  eventParm; TYPE_4__ pos; } ;
struct TYPE_44__ {int health; int wait; int random; int flags; scalar_t__ think; scalar_t__ nextthink; TYPE_5__ r; TYPE_37__ s; void* freeAfterEvent; void* unlinkAfterEvent; int /*<<< orphan*/  speed; TYPE_3__* item; TYPE_2__* client; int /*<<< orphan*/  id; } ;
typedef  TYPE_6__ gentity_t ;
struct TYPE_46__ {int /*<<< orphan*/  integer; } ;
struct TYPE_45__ {scalar_t__ time; } ;
struct TYPE_41__ {int giType; int /*<<< orphan*/  classname; } ;
struct TYPE_38__ {scalar_t__ predictItemPickup; } ;
struct TYPE_39__ {int /*<<< orphan*/  ps; TYPE_1__ pers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_CanItemBeGrabbed (int /*<<< orphan*/ ,TYPE_37__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EF_NODRAW ; 
 int /*<<< orphan*/  EV_GLOBAL_ITEM_PICKUP ; 
 int /*<<< orphan*/  EV_ITEM_PICKUP ; 
 int FL_DROPPED_ITEM ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_AddPredictableEvent (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_LogPrintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* G_TempEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_UseTargets (TYPE_6__*,TYPE_6__*) ; 
#define  IT_AMMO 137 
#define  IT_ARMOR 136 
#define  IT_GOAL 135 
#define  IT_HEALTH 134 
#define  IT_HOLDABLE 133 
#define  IT_PERSISTANT_POWERUP 132 
#define  IT_POWERUP 131 
#define  IT_REWARD 130 
#define  IT_TEAM 129 
#define  IT_WEAPON 128 
 int Pickup_Ammo (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Armor (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Goal (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Health (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Holdable (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_PersistantPowerup (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Powerup (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Reward (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Team (TYPE_6__*,TYPE_6__*) ; 
 int Pickup_Weapon (TYPE_6__*,TYPE_6__*) ; 
 scalar_t__ RespawnItem ; 
 int /*<<< orphan*/  SVF_BROADCAST ; 
 int /*<<< orphan*/  SVF_NOCLIENT ; 
 int /*<<< orphan*/  SVF_SINGLECLIENT ; 
 int crandom () ; 
 int /*<<< orphan*/  dmlab_override_pickup (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 TYPE_9__ g_gametype ; 
 TYPE_8__ level ; 
 scalar_t__ qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_6__*) ; 

void Touch_Item (gentity_t *ent, gentity_t *other, trace_t *trace) {
	int			respawn;
	qboolean	predict;

	if (!other->client)
		return;
	if (other->health < 1)
		return;		// dead people can't pickup

	// the same pickup rules are used for client side and server side
	if ( !BG_CanItemBeGrabbed( g_gametype.integer, &ent->s, &other->client->ps ) ) {
		return;
	}

	G_LogPrintf( "Item: %i %s\n", other->s.number, ent->item->classname );

	predict = other->client->pers.predictItemPickup;

	respawn = -1;
	if (!ent->id || !dmlab_override_pickup(ent->id, &respawn, &other->client->ps )) {
		// call the item-specific pickup function
		switch( ent->item->giType ) {
		case IT_WEAPON:
			respawn = Pickup_Weapon(ent, other);
//		predict = qfalse;
			break;
		case IT_AMMO:
			respawn = Pickup_Ammo(ent, other);
//		predict = qfalse;
			break;
		case IT_ARMOR:
			respawn = Pickup_Armor(ent, other);
			break;
		case IT_HEALTH:
			respawn = Pickup_Health(ent, other);
			break;
		case IT_POWERUP:
			respawn = Pickup_Powerup(ent, other);
			predict = qfalse;
			break;
#ifdef MISSIONPACK
		case IT_PERSISTANT_POWERUP:
			respawn = Pickup_PersistantPowerup(ent, other);
			break;
#endif
		case IT_TEAM:
			respawn = Pickup_Team(ent, other);
			break;
		case IT_HOLDABLE:
			respawn = Pickup_Holdable(ent, other);
			break;
		case IT_REWARD:
			respawn = Pickup_Reward(ent, other);
			break;
		case IT_GOAL:
			respawn = Pickup_Goal(ent, other);
			break;
		default:
			return;
		}
	}

	if ( !respawn ) {
		return;
	}

	// play the normal pickup sound
	if (predict) {
		G_AddPredictableEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
	} else {
		G_AddEvent( other, EV_ITEM_PICKUP, ent->s.modelindex );
	}

	// powerup pickups are global broadcasts
	if ( ent->item->giType == IT_POWERUP || ent->item->giType == IT_TEAM) {
		// if we want the global sound to play
		if (!ent->speed) {
			gentity_t	*te;

			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
			te->s.eventParm = ent->s.modelindex;
			te->r.svFlags |= SVF_BROADCAST;
		} else {
			gentity_t	*te;

			te = G_TempEntity( ent->s.pos.trBase, EV_GLOBAL_ITEM_PICKUP );
			te->s.eventParm = ent->s.modelindex;
			// only send this temp entity to a single client
			te->r.svFlags |= SVF_SINGLECLIENT;
			te->r.singleClient = other->s.number;
		}
	}

	// fire item targets
	G_UseTargets (ent, other);

	// wait of -1 will not respawn
	if ( ent->wait == -1 ) {
		ent->r.svFlags |= SVF_NOCLIENT;
		ent->s.eFlags |= EF_NODRAW;
		ent->r.contents = 0;
		ent->unlinkAfterEvent = qtrue;
		return;
	}

	// non zero wait overrides respawn time
	if ( ent->wait ) {
		respawn = ent->wait;
	}

	// random can be used to vary the respawn time
	if ( ent->random ) {
		respawn += crandom() * ent->random;
		if ( respawn < 1 ) {
			respawn = 1;
		}
	}

	// dropped items will not respawn
	if ( ent->flags & FL_DROPPED_ITEM ) {
		ent->freeAfterEvent = qtrue;
	}

	// picked up items still stay around, they just don't
	// draw anything.  This allows respawnable items
	// to be placed on movers.
	ent->r.svFlags |= SVF_NOCLIENT;
	ent->s.eFlags |= EF_NODRAW;
	ent->r.contents = 0;

	// ZOID
	// A negative respawn times means to never respawn this item (but don't 
	// delete it).  This is used by items that are respawned by third party 
	// events such as ctf flags
	if ( respawn <= 0 ) {
		ent->nextthink = 0;
		ent->think = 0;
	} else {
		ent->nextthink = level.time + respawn * 1000;
		ent->think = RespawnItem;
	}
	trap_LinkEntity( ent );
}