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
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_9__ {scalar_t__ moverState; scalar_t__ nextthink; TYPE_2__* client; } ;
typedef  TYPE_3__ gentity_t ;
struct TYPE_10__ {scalar_t__ time; } ;
struct TYPE_7__ {scalar_t__* stats; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;

/* Variables and functions */
 scalar_t__ MOVER_POS2 ; 
 size_t STAT_HEALTH ; 
 TYPE_4__ level ; 

void Touch_Plat( gentity_t *ent, gentity_t *other, trace_t *trace ) {
	if ( !other->client || other->client->ps.stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	// delay return-to-pos1 by one second
	if ( ent->moverState == MOVER_POS2 ) {
		ent->nextthink = level.time + 1000;
	}
}