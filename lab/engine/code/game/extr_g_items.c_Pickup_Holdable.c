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
struct TYPE_10__ {TYPE_3__* client; TYPE_1__* item; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_8__ {int /*<<< orphan*/  eFlags; TYPE_1__** stats; } ;
struct TYPE_9__ {TYPE_2__ ps; } ;
struct TYPE_7__ {scalar_t__ giTag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF_KAMIKAZE ; 
 scalar_t__ HI_KAMIKAZE ; 
 int RESPAWN_HOLDABLE ; 
 size_t STAT_HOLDABLE_ITEM ; 
 int bg_itemlist ; 

int Pickup_Holdable( gentity_t *ent, gentity_t *other ) {

	other->client->ps.stats[STAT_HOLDABLE_ITEM] = ent->item - bg_itemlist;

	if( ent->item->giTag == HI_KAMIKAZE ) {
		other->client->ps.eFlags |= EF_KAMIKAZE;
	}

	return RESPAWN_HOLDABLE;
}