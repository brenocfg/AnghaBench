#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  msg_t ;
struct TYPE_8__ {int number; } ;
typedef  TYPE_1__ entityState_t ;
struct TYPE_9__ {int /*<<< orphan*/  numEntities; } ;
typedef  TYPE_2__ clSnapshot_t ;
struct TYPE_10__ {int parseEntitiesNum; TYPE_1__* parseEntities; } ;

/* Variables and functions */
 int MAX_GENTITIES ; 
 int MAX_PARSE_ENTITIES ; 
 int /*<<< orphan*/  MSG_ReadDeltaEntity (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_3__ cl ; 

void CL_DeltaEntity (msg_t *msg, clSnapshot_t *frame, int newnum, entityState_t *old, 
					 qboolean unchanged) {
	entityState_t	*state;

	// save the parsed entity state into the big circular buffer so
	// it can be used as the source for a later delta
	state = &cl.parseEntities[cl.parseEntitiesNum & (MAX_PARSE_ENTITIES-1)];

	if ( unchanged ) {
		*state = *old;
	} else {
		MSG_ReadDeltaEntity( msg, old, state, newnum );
	}

	if ( state->number == (MAX_GENTITIES-1) ) {
		return;		// entity was delta removed
	}
	cl.parseEntitiesNum++;
	frame->numEntities++;
}