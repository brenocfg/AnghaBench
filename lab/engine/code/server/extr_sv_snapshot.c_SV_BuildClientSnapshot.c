#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
struct TYPE_17__ {scalar_t__ snapshotCounter; } ;
typedef  TYPE_2__ svEntity_t ;
struct TYPE_18__ {int numSnapshotEntities; int /*<<< orphan*/ * snapshotEntities; } ;
typedef  TYPE_3__ snapshotEntityNumbers_t ;
struct TYPE_19__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_4__ sharedEntity_t ;
struct TYPE_20__ {int clientNum; scalar_t__ viewheight; int /*<<< orphan*/  origin; } ;
typedef  TYPE_5__ playerState_t ;
typedef  int /*<<< orphan*/  entityState_t ;
struct TYPE_16__ {size_t outgoingSequence; } ;
struct TYPE_21__ {scalar_t__ state; TYPE_4__* gentity; TYPE_1__ netchan; TYPE_7__* frames; } ;
typedef  TYPE_6__ client_t ;
struct TYPE_22__ {size_t first_entity; scalar_t__ num_entities; scalar_t__ areabits; TYPE_5__ ps; } ;
typedef  TYPE_7__ clientSnapshot_t ;
struct TYPE_24__ {scalar_t__ snapshotCounter; TYPE_2__* svEntities; } ;
struct TYPE_23__ {int clients; size_t nextSnapshotEntities; size_t numSnapshotEntities; int /*<<< orphan*/ * snapshotEntities; } ;

/* Variables and functions */
 scalar_t__ CS_ZOMBIE ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Com_Memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int MAX_GENTITIES ; 
 int MAX_MAP_AREA_BYTES ; 
 size_t PACKET_MASK ; 
 int /*<<< orphan*/  SV_AddEntitiesVisibleFromPoint (int /*<<< orphan*/ *,TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* SV_GameClientNum (TYPE_6__*) ; 
 TYPE_4__* SV_GentityNum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_QsortEntityNumbers ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 TYPE_9__ sv ; 
 TYPE_8__ svs ; 

__attribute__((used)) static void SV_BuildClientSnapshot( client_t *client ) {
	vec3_t						org;
	clientSnapshot_t			*frame;
	snapshotEntityNumbers_t		entityNumbers;
	int							i;
	sharedEntity_t				*ent;
	entityState_t				*state;
	svEntity_t					*svEnt;
	sharedEntity_t				*clent;
	int							clientNum;
	playerState_t				*ps;

	// bump the counter used to prevent double adding
	sv.snapshotCounter++;

	// this is the frame we are creating
	frame = &client->frames[ client->netchan.outgoingSequence & PACKET_MASK ];

	// clear everything in this snapshot
	entityNumbers.numSnapshotEntities = 0;
	Com_Memset( frame->areabits, 0, sizeof( frame->areabits ) );

  // https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=62
	frame->num_entities = 0;
	
	clent = client->gentity;
	if ( !clent || client->state == CS_ZOMBIE ) {
		return;
	}

	// grab the current playerState_t
	ps = SV_GameClientNum( client - svs.clients );
	frame->ps = *ps;

	// never send client's own entity, because it can
	// be regenerated from the playerstate
	clientNum = frame->ps.clientNum;
	if ( clientNum < 0 || clientNum >= MAX_GENTITIES ) {
		Com_Error( ERR_DROP, "SV_SvEntityForGentity: bad gEnt" );
	}
	svEnt = &sv.svEntities[ clientNum ];

	svEnt->snapshotCounter = sv.snapshotCounter;

	// find the client's viewpoint
	VectorCopy( ps->origin, org );
	org[2] += ps->viewheight;

	// add all the entities directly visible to the eye, which
	// may include portal entities that merge other viewpoints
	SV_AddEntitiesVisibleFromPoint( org, frame, &entityNumbers, qfalse );

	// if there were portals visible, there may be out of order entities
	// in the list which will need to be resorted for the delta compression
	// to work correctly.  This also catches the error condition
	// of an entity being included twice.
	qsort( entityNumbers.snapshotEntities, entityNumbers.numSnapshotEntities, 
		sizeof( entityNumbers.snapshotEntities[0] ), SV_QsortEntityNumbers );

	// now that all viewpoint's areabits have been OR'd together, invert
	// all of them to make it a mask vector, which is what the renderer wants
	for ( i = 0 ; i < MAX_MAP_AREA_BYTES/4 ; i++ ) {
		((int *)frame->areabits)[i] = ((int *)frame->areabits)[i] ^ -1;
	}

	// copy the entity states out
	frame->num_entities = 0;
	frame->first_entity = svs.nextSnapshotEntities;
	for ( i = 0 ; i < entityNumbers.numSnapshotEntities ; i++ ) {
		ent = SV_GentityNum(entityNumbers.snapshotEntities[i]);
		state = &svs.snapshotEntities[svs.nextSnapshotEntities % svs.numSnapshotEntities];
		*state = ent->s;
		svs.nextSnapshotEntities++;
		// this should never hit, map should always be restarted first in SV_Frame
		if ( svs.nextSnapshotEntities >= 0x7FFFFFFE ) {
			Com_Error(ERR_FATAL, "svs.nextSnapshotEntities wrapped");
		}
		frame->num_entities++;
	}
}