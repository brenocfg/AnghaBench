#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* client; TYPE_3__* item; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_9__ {scalar_t__ quantity; } ;
struct TYPE_7__ {int* stats; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int RESPAWN_ARMOR ; 
 size_t STAT_ARMOR ; 
 size_t STAT_MAX_HEALTH ; 

int Pickup_Armor( gentity_t *ent, gentity_t *other ) {
#ifdef MISSIONPACK
	int		upperBound;

	other->client->ps.stats[STAT_ARMOR] += ent->item->quantity;

	if( other->client && bg_itemlist[other->client->ps.stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
		upperBound = other->client->ps.stats[STAT_MAX_HEALTH];
	}
	else {
		upperBound = other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}

	if ( other->client->ps.stats[STAT_ARMOR] > upperBound ) {
		other->client->ps.stats[STAT_ARMOR] = upperBound;
	}
#else
	other->client->ps.stats[STAT_ARMOR] += ent->item->quantity;
	if ( other->client->ps.stats[STAT_ARMOR] > other->client->ps.stats[STAT_MAX_HEALTH] * 2 ) {
		other->client->ps.stats[STAT_ARMOR] = other->client->ps.stats[STAT_MAX_HEALTH] * 2;
	}
#endif

	return RESPAWN_ARMOR;
}