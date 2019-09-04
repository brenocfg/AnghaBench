#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {scalar_t__ type; int numVerts; TYPE_2__* verts; } ;
typedef  TYPE_1__ mapDrawSurface_t ;
struct TYPE_7__ {float* st; float** lightmap; int** color; int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ bspDrawVert_t ;
typedef  int /*<<< orphan*/  avg ;

/* Variables and functions */
 float DEGENERATE_EPSILON ; 
 int MAX_LIGHTMAPS ; 
 scalar_t__ SURFACE_FACE ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SnapWeldVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean FixBrokenSurface( mapDrawSurface_t *ds ){
	qboolean valid = qtrue;
	bspDrawVert_t   *dv1, *dv2, avg;
	int i, j, k;
	float dist;


	/* dummy check */
	if ( ds == NULL ) {
		return qfalse;
	}
	if ( ds->type != SURFACE_FACE ) {
		return qfalse;
	}

	/* check all verts */
	for ( i = 0; i < ds->numVerts; i++ )
	{
		/* don't remove points if winding is a triangle */
		if ( ds->numVerts == 3 ) {
			return valid;
		}

		/* get verts */
		dv1 = &ds->verts[ i ];
		dv2 = &ds->verts[ ( i + 1 ) % ds->numVerts ];

		/* degenerate edge? */
		VectorSubtract( dv1->xyz, dv2->xyz, avg.xyz );
		dist = VectorLength( avg.xyz );
		if ( dist < DEGENERATE_EPSILON ) {
			valid = qfalse;
			Sys_FPrintf( SYS_VRB, "WARNING: Degenerate T-junction edge found, fixing...\n" );

			/* create an average drawvert */
			/* ydnar 2002-01-26: added nearest-integer welding preference */
			SnapWeldVector( dv1->xyz, dv2->xyz, avg.xyz );
			VectorAdd( dv1->normal, dv2->normal, avg.normal );
			VectorNormalize( avg.normal, avg.normal );
			avg.st[ 0 ] = ( dv1->st[ 0 ] + dv2->st[ 0 ] ) * 0.5f;
			avg.st[ 1 ] = ( dv1->st[ 1 ] + dv2->st[ 1 ] ) * 0.5f;

			/* lightmap st/colors */
			for ( k = 0; k < MAX_LIGHTMAPS; k++ )
			{
				avg.lightmap[ k ][ 0 ] = ( dv1->lightmap[ k ][ 0 ] + dv2->lightmap[ k ][ 0 ] ) * 0.5f;
				avg.lightmap[ k ][ 1 ] = ( dv1->lightmap[ k ][ 1 ] + dv2->lightmap[ k ][ 1 ] ) * 0.5f;
				for ( j = 0; j < 4; j++ )
					avg.color[ k ][ j ] = (int) ( dv1->color[ k ][ j ] + dv2->color[ k ][ j ] ) >> 1;
			}

			/* ydnar: der... */
			memcpy( dv1, &avg, sizeof( avg ) );

			/* move the remaining verts */
			for ( k = i + 2; k < ds->numVerts; k++ )
			{
				/* get verts */
				dv1 = &ds->verts[ k ];
				dv2 = &ds->verts[ k - 1 ];

				/* copy */
				memcpy( dv2, dv1, sizeof( bspDrawVert_t ) );
			}
			ds->numVerts--;
		}
	}

	/* one last check and return */
	if ( ds->numVerts < 3 ) {
		valid = qfalse;
	}
	return valid;
}