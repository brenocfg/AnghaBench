#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_13__ {int numFoliageInstances; int patchHeight; int numIndexes; size_t* indexes; size_t numVerts; TYPE_4__* verts; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_14__ {int /*<<< orphan*/  xyz; } ;
typedef  TYPE_4__ bspDrawVert_t ;

/* Variables and functions */
 TYPE_1__* AllocWinding (int) ; 
 int /*<<< orphan*/  Error (char*,size_t,size_t) ; 
 scalar_t__ FilterPointIntoTree_r (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FilterWindingIntoTree_r (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FilterFoliageIntoTree( mapDrawSurface_t *ds, tree_t *tree ){
	int f, i, refs;
	bspDrawVert_t   *instance;
	vec3_t xyz;
	winding_t       *w;


	/* walk origin list */
	refs = 0;
	for ( f = 0; f < ds->numFoliageInstances; f++ )
	{
		/* get instance */
		instance = ds->verts + ds->patchHeight + f;

		/* walk triangle list */
		for ( i = 0; i < ds->numIndexes; i += 3 )
		{
			/* error check */
			if ( ds->indexes[ i ] >= ds->numVerts ||
				 ds->indexes[ i + 1 ] >= ds->numVerts ||
				 ds->indexes[ i + 2 ] >= ds->numVerts ) {
				Error( "Index %d greater than vertex count %d", ds->indexes[ i ], ds->numVerts );
			}

			/* make a triangle winding and filter it into the tree */
			w = AllocWinding( 3 );
			w->numpoints = 3;
			VectorAdd( instance->xyz, ds->verts[ ds->indexes[ i ] ].xyz, w->p[ 0 ] );
			VectorAdd( instance->xyz, ds->verts[ ds->indexes[ i + 1 ] ].xyz, w->p[ 1 ] );
			VectorAdd( instance->xyz, ds->verts[ ds->indexes[ i + 2 ] ].xyz, w->p[ 2 ] );
			refs += FilterWindingIntoTree_r( w, ds, tree->headnode );
		}

		/* use point filtering as well */
		for ( i = 0; i < ( ds->numVerts - ds->numFoliageInstances ); i++ )
		{
			VectorAdd( instance->xyz, ds->verts[ i ].xyz, xyz );
			refs += FilterPointIntoTree_r( xyz, ds, tree->headnode );
		}
	}

	return refs;
}