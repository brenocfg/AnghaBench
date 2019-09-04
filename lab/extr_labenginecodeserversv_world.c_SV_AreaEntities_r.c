#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int axis; scalar_t__ dist; struct TYPE_12__** children; TYPE_3__* entities; } ;
typedef  TYPE_2__ worldSector_t ;
struct TYPE_13__ {struct TYPE_13__* nextEntityInWorldSector; } ;
typedef  TYPE_3__ svEntity_t ;
struct TYPE_11__ {scalar_t__* absmin; scalar_t__* absmax; } ;
struct TYPE_14__ {TYPE_1__ r; } ;
typedef  TYPE_4__ sharedEntity_t ;
struct TYPE_15__ {scalar_t__* maxs; scalar_t__* mins; size_t count; size_t maxcount; TYPE_3__** list; } ;
typedef  TYPE_5__ areaParms_t ;
struct TYPE_16__ {int svEntities; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 TYPE_4__* SV_GEntityForSvEntity (TYPE_3__*) ; 
 TYPE_6__ sv ; 

__attribute__((used)) static void SV_AreaEntities_r( worldSector_t *node, areaParms_t *ap ) {
	svEntity_t	*check, *next;
	sharedEntity_t *gcheck;

	for ( check = node->entities  ; check ; check = next ) {
		next = check->nextEntityInWorldSector;

		gcheck = SV_GEntityForSvEntity( check );

		if ( gcheck->r.absmin[0] > ap->maxs[0]
		|| gcheck->r.absmin[1] > ap->maxs[1]
		|| gcheck->r.absmin[2] > ap->maxs[2]
		|| gcheck->r.absmax[0] < ap->mins[0]
		|| gcheck->r.absmax[1] < ap->mins[1]
		|| gcheck->r.absmax[2] < ap->mins[2]) {
			continue;
		}

		if ( ap->count == ap->maxcount ) {
			Com_Printf ("SV_AreaEntities: MAXCOUNT\n");
			return;
		}

		ap->list[ap->count] = check - sv.svEntities;
		ap->count++;
	}
	
	if (node->axis == -1) {
		return;		// terminal node
	}

	// recurse down both sides
	if ( ap->maxs[node->axis] > node->dist ) {
		SV_AreaEntities_r ( node->children[0], ap );
	}
	if ( ap->mins[node->axis] < node->dist ) {
		SV_AreaEntities_r ( node->children[1], ap );
	}
}