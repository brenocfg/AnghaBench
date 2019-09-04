#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_8__ {size_t firstSurfaceCluster; int /*<<< orphan*/  numSurfaceClusters; } ;
typedef  TYPE_1__ surfaceInfo_t ;
struct TYPE_9__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ bspDrawVert_t ;
struct TYPE_10__ {size_t firstVert; int numVerts; } ;
typedef  TYPE_3__ bspDrawSurface_t ;
struct TYPE_11__ {int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTraceLightsForBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIGHT_SURFACES ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* bspDrawSurfaces ; 
 TYPE_6__* bspDrawVerts ; 
 int /*<<< orphan*/ * surfaceClusters ; 
 TYPE_1__* surfaceInfos ; 
 TYPE_2__* yDrawVerts ; 

void CreateTraceLightsForSurface( int num, trace_t *trace ){
	int i;
	vec3_t mins, maxs, normal;
	bspDrawVert_t       *dv;
	bspDrawSurface_t    *ds;
	surfaceInfo_t       *info;


	/* dummy check */
	if ( num < 0 ) {
		return;
	}

	/* get drawsurface and info */
	ds = &bspDrawSurfaces[ num ];
	info = &surfaceInfos[ num ];

	/* get the mins/maxs for the dsurf */
	ClearBounds( mins, maxs );
	VectorCopy( bspDrawVerts[ ds->firstVert ].normal, normal );
	for ( i = 0; i < ds->numVerts; i++ )
	{
		dv = &yDrawVerts[ ds->firstVert + i ];
		AddPointToBounds( dv->xyz, mins, maxs );
		if ( !VectorCompare( dv->normal, normal ) ) {
			VectorClear( normal );
		}
	}

	/* create the lights for the bounding box */
	CreateTraceLightsForBounds( mins, maxs, normal, info->numSurfaceClusters, &surfaceClusters[ info->firstSurfaceCluster ], LIGHT_SURFACES, trace );
}