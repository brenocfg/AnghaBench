#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numVerts; TYPE_3__* verts; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_8__ {scalar_t__* st; scalar_t__** color; int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_3__ bspDrawVert_t ;
struct TYPE_6__ {int compileFlags; } ;

/* Variables and functions */
 int C_VERTEXLIT ; 
 int VERTS_EXCEEDED ; 
 scalar_t__ VectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxLMSurfaceVerts ; 
 int maxSurfaceVerts ; 
 int /*<<< orphan*/  numMergedVerts ; 
 scalar_t__ qfalse ; 

int AddMetaVertToSurface( mapDrawSurface_t *ds, bspDrawVert_t *dv1, int *coincident ){
	int i;
	bspDrawVert_t   *dv2;


	/* go through the verts and find a suitable candidate */
	for ( i = 0; i < ds->numVerts; i++ )
	{
		/* get test vert */
		dv2 = &ds->verts[ i ];

		/* compare xyz and normal */
		if ( VectorCompare( dv1->xyz, dv2->xyz ) == qfalse ) {
			continue;
		}
		if ( VectorCompare( dv1->normal, dv2->normal ) == qfalse ) {
			continue;
		}

		/* good enough at this point */
		( *coincident )++;

		/* compare texture coordinates and color */
		if ( dv1->st[ 0 ] != dv2->st[ 0 ] || dv1->st[ 1 ] != dv2->st[ 1 ] ) {
			continue;
		}
		if ( dv1->color[ 0 ][ 3 ] != dv2->color[ 0 ][ 3 ] ) {
			continue;
		}

		/* found a winner */
		numMergedVerts++;
		return i;
	}

	/* overflow check */
	if ( ds->numVerts >= ( ( ds->shaderInfo->compileFlags & C_VERTEXLIT ) ? maxSurfaceVerts : maxLMSurfaceVerts ) ) {
		return VERTS_EXCEEDED;
	}

	/* made it this far, add the vert and return */
	dv2 = &ds->verts[ ds->numVerts++ ];
	*dv2 = *dv1;
	return ( ds->numVerts - 1 );
}