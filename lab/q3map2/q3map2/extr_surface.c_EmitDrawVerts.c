#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float offset; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_12__ {int numVerts; int /*<<< orphan*/ * verts; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_13__ {int /*<<< orphan*/ * color; int /*<<< orphan*/  xyz; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ bspDrawVert_t ;
struct TYPE_14__ {int firstVert; int numVerts; } ;
typedef  TYPE_4__ bspDrawSurface_t ;
struct TYPE_15__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  IncDrawVerts () ; 
 int MAX_LIGHTMAPS ; 
 int MAX_MAP_DRAW_VERTS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* bspDrawVerts ; 
 TYPE_7__* bspModels ; 
 int /*<<< orphan*/ * debugColors ; 
 scalar_t__ debugSurfaces ; 
 TYPE_2__* mapDrawSurfs ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int numBSPDrawVerts ; 
 size_t numBSPModels ; 

void EmitDrawVerts( mapDrawSurface_t *ds, bspDrawSurface_t *out ){
	int i, k;
	bspDrawVert_t   *dv;
	shaderInfo_t    *si;
	float offset;


	/* get stuff */
	si = ds->shaderInfo;
	offset = si->offset;

	/* copy the verts */
	out->firstVert = numBSPDrawVerts;
	out->numVerts = ds->numVerts;
	for ( i = 0; i < ds->numVerts; i++ )
	{
		/* allocate a new vert */
		if ( numBSPDrawVerts == MAX_MAP_DRAW_VERTS ) {
			Error( "MAX_MAP_DRAW_VERTS" );
		}
		IncDrawVerts();
		dv = &bspDrawVerts[ numBSPDrawVerts - 1 ];

		/* copy it */
		memcpy( dv, &ds->verts[ i ], sizeof( *dv ) );

		/* offset? */
		if ( offset != 0.0f ) {
			VectorMA( dv->xyz, offset, dv->normal, dv->xyz );
		}

		/* expand model bounds
		   necessary because of misc_model surfaces on entities
		   note: does not happen on worldspawn as its bounds is only used for determining lightgrid bounds */
		if ( numBSPModels > 0 ) {
			AddPointToBounds( dv->xyz, bspModels[ numBSPModels ].mins, bspModels[ numBSPModels ].maxs );
		}

		/* debug color? */
		if ( debugSurfaces ) {
			for ( k = 0; k < MAX_LIGHTMAPS; k++ )
				VectorCopy( debugColors[ ( ds - mapDrawSurfs ) % 12 ], dv->color[ k ] );
		}
	}
}