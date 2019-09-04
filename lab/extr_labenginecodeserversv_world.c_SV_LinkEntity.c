#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int axis; scalar_t__ dist; TYPE_4__* entities; struct TYPE_14__** children; } ;
typedef  TYPE_3__ worldSector_t ;
struct TYPE_15__ {scalar_t__ numClusters; int areanum; int areanum2; int* clusternums; struct TYPE_15__* nextEntityInWorldSector; TYPE_3__* worldSector; void* lastCluster; } ;
typedef  TYPE_4__ svEntity_t ;
struct TYPE_13__ {int contents; int* maxs; int* mins; float* currentOrigin; float* currentAngles; float* absmin; float* absmax; int /*<<< orphan*/  linked; int /*<<< orphan*/  linkcount; scalar_t__ bmodel; } ;
struct TYPE_12__ {int solid; int /*<<< orphan*/  number; } ;
struct TYPE_16__ {TYPE_2__ r; TYPE_1__ s; } ;
typedef  TYPE_5__ sharedEntity_t ;
struct TYPE_17__ {scalar_t__ state; } ;

/* Variables and functions */
 int CM_BoxLeafnums (float*,float*,int*,int,int*) ; 
 int CM_LeafArea (int) ; 
 void* CM_LeafCluster (int) ; 
 int CONTENTS_BODY ; 
 int CONTENTS_SOLID ; 
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ MAX_ENT_CLUSTERS ; 
 int MAX_TOTAL_ENT_LEAFS ; 
 float RadiusFromBounds (int*,int*) ; 
 int SOLID_BMODEL ; 
 scalar_t__ SS_LOADING ; 
 TYPE_4__* SV_SvEntityForGentity (TYPE_5__*) ; 
 int /*<<< orphan*/  SV_UnlinkEntity (TYPE_5__*) ; 
 int /*<<< orphan*/  VectorAdd (float*,int*,float*) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_7__ sv ; 
 TYPE_3__* sv_worldSectors ; 

void SV_LinkEntity( sharedEntity_t *gEnt ) {
	worldSector_t	*node;
	int			leafs[MAX_TOTAL_ENT_LEAFS];
	int			cluster;
	int			num_leafs;
	int			i, j, k;
	int			area;
	int			lastLeaf;
	float		*origin, *angles;
	svEntity_t	*ent;

	ent = SV_SvEntityForGentity( gEnt );

	if ( ent->worldSector ) {
		SV_UnlinkEntity( gEnt );	// unlink from old position
	}

	// encode the size into the entityState_t for client prediction
	if ( gEnt->r.bmodel ) {
		gEnt->s.solid = SOLID_BMODEL;		// a solid_box will never create this value
	} else if ( gEnt->r.contents & ( CONTENTS_SOLID | CONTENTS_BODY ) ) {
		// assume that x/y are equal and symetric
		i = gEnt->r.maxs[0];
		if (i<1)
			i = 1;
		if (i>255)
			i = 255;

		// z is not symetric
		j = (-gEnt->r.mins[2]);
		if (j<1)
			j = 1;
		if (j>255)
			j = 255;

		// and z maxs can be negative...
		k = (gEnt->r.maxs[2]+32);
		if (k<1)
			k = 1;
		if (k>255)
			k = 255;

		gEnt->s.solid = (k<<16) | (j<<8) | i;
	} else {
		gEnt->s.solid = 0;
	}

	// get the position
	origin = gEnt->r.currentOrigin;
	angles = gEnt->r.currentAngles;

	// set the abs box
	if ( gEnt->r.bmodel && (angles[0] || angles[1] || angles[2]) ) {
		// expand for rotation
		float		max;

		max = RadiusFromBounds( gEnt->r.mins, gEnt->r.maxs );
		for (i=0 ; i<3 ; i++) {
			gEnt->r.absmin[i] = origin[i] - max;
			gEnt->r.absmax[i] = origin[i] + max;
		}
	} else {
		// normal
		VectorAdd (origin, gEnt->r.mins, gEnt->r.absmin);	
		VectorAdd (origin, gEnt->r.maxs, gEnt->r.absmax);
	}

	// because movement is clipped an epsilon away from an actual edge,
	// we must fully check even when bounding boxes don't quite touch
	gEnt->r.absmin[0] -= 1;
	gEnt->r.absmin[1] -= 1;
	gEnt->r.absmin[2] -= 1;
	gEnt->r.absmax[0] += 1;
	gEnt->r.absmax[1] += 1;
	gEnt->r.absmax[2] += 1;

	// link to PVS leafs
	ent->numClusters = 0;
	ent->lastCluster = 0;
	ent->areanum = -1;
	ent->areanum2 = -1;

	//get all leafs, including solids
	num_leafs = CM_BoxLeafnums( gEnt->r.absmin, gEnt->r.absmax,
		leafs, MAX_TOTAL_ENT_LEAFS, &lastLeaf );

	// if none of the leafs were inside the map, the
	// entity is outside the world and can be considered unlinked
	if ( !num_leafs ) {
		return;
	}

	// set areas, even from clusters that don't fit in the entity array
	for (i=0 ; i<num_leafs ; i++) {
		area = CM_LeafArea (leafs[i]);
		if (area != -1) {
			// doors may legally straggle two areas,
			// but nothing should evern need more than that
			if (ent->areanum != -1 && ent->areanum != area) {
				if (ent->areanum2 != -1 && ent->areanum2 != area && sv.state == SS_LOADING) {
					Com_DPrintf ("Object %i touching 3 areas at %f %f %f\n",
					gEnt->s.number,
					gEnt->r.absmin[0], gEnt->r.absmin[1], gEnt->r.absmin[2]);
				}
				ent->areanum2 = area;
			} else {
				ent->areanum = area;
			}
		}
	}

	// store as many explicit clusters as we can
	ent->numClusters = 0;
	for (i=0 ; i < num_leafs ; i++) {
		cluster = CM_LeafCluster( leafs[i] );
		if ( cluster != -1 ) {
			ent->clusternums[ent->numClusters++] = cluster;
			if ( ent->numClusters == MAX_ENT_CLUSTERS ) {
				break;
			}
		}
	}

	// store off a last cluster if we need to
	if ( i != num_leafs ) {
		ent->lastCluster = CM_LeafCluster( lastLeaf );
	}

	gEnt->r.linkcount++;

	// find the first world sector node that the ent's box crosses
	node = sv_worldSectors;
	while (1)
	{
		if (node->axis == -1)
			break;
		if ( gEnt->r.absmin[node->axis] > node->dist)
			node = node->children[0];
		else if ( gEnt->r.absmax[node->axis] < node->dist)
			node = node->children[1];
		else
			break;		// crosses the node
	}
	
	// link it in
	ent->worldSector = node;
	ent->nextEntityInWorldSector = node->entities;
	node->entities = ent;

	gEnt->r.linked = qtrue;
}