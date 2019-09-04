#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int numEntities; TYPE_1__* entities; } ;
typedef  TYPE_3__ snapshot_t ;
struct TYPE_13__ {scalar_t__ eType; } ;
typedef  TYPE_4__ entityState_t ;
struct TYPE_11__ {scalar_t__ solid; } ;
struct TYPE_14__ {TYPE_2__ nextState; TYPE_4__ currentState; } ;
typedef  TYPE_5__ centity_t ;
struct TYPE_15__ {TYPE_3__* snap; TYPE_3__* nextSnap; int /*<<< orphan*/  thisFrameTeleport; int /*<<< orphan*/  nextFrameTeleport; } ;
struct TYPE_10__ {size_t number; } ;

/* Variables and functions */
 scalar_t__ ET_ITEM ; 
 scalar_t__ ET_PUSH_TRIGGER ; 
 scalar_t__ ET_TELEPORT_TRIGGER ; 
 TYPE_9__ cg ; 
 TYPE_5__* cg_entities ; 
 size_t cg_numSolidEntities ; 
 size_t cg_numTriggerEntities ; 
 TYPE_5__** cg_solidEntities ; 
 TYPE_5__** cg_triggerEntities ; 

void CG_BuildSolidList( void ) {
	int			i;
	centity_t	*cent;
	snapshot_t	*snap;
	entityState_t	*ent;

	cg_numSolidEntities = 0;
	cg_numTriggerEntities = 0;

	if ( cg.nextSnap && !cg.nextFrameTeleport && !cg.thisFrameTeleport ) {
		snap = cg.nextSnap;
	} else {
		snap = cg.snap;
	}

	for ( i = 0 ; i < snap->numEntities ; i++ ) {
		cent = &cg_entities[ snap->entities[ i ].number ];
		ent = &cent->currentState;

		if ( ent->eType == ET_ITEM || ent->eType == ET_PUSH_TRIGGER || ent->eType == ET_TELEPORT_TRIGGER ) {
			cg_triggerEntities[cg_numTriggerEntities] = cent;
			cg_numTriggerEntities++;
			continue;
		}

		if ( cent->nextState.solid ) {
			cg_solidEntities[cg_numSolidEntities] = cent;
			cg_numSolidEntities++;
			continue;
		}
	}
}