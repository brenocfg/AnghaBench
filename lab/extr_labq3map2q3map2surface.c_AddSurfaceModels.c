#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {struct TYPE_18__* next; } ;
typedef  TYPE_2__ surfaceModel_t ;
struct TYPE_19__ {int width; TYPE_5__* verts; int /*<<< orphan*/  height; } ;
typedef  TYPE_3__ mesh_t ;
struct TYPE_20__ {int type; int numVerts; int patchWidth; int numIndexes; size_t* indexes; TYPE_5__* verts; int /*<<< orphan*/  longestCurve; int /*<<< orphan*/  patchHeight; TYPE_1__* shaderInfo; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
typedef  int /*<<< orphan*/  centroid ;
struct TYPE_21__ {int* xyz; int* normal; int* st; float** color; } ;
typedef  TYPE_5__ bspDrawVert_t ;
struct TYPE_17__ {TYPE_2__* surfaceModel; } ;

/* Variables and functions */
 int AddSurfaceModelsToTriangle_r (TYPE_4__*,TYPE_2__*,TYPE_5__**) ; 
 int /*<<< orphan*/  FreeMesh (TYPE_3__*) ; 
 int IterationsForCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_3__) ; 
 TYPE_3__* RemoveLinearMeshColumnsRows (TYPE_3__*) ; 
#define  SURFACE_DECAL 133 
#define  SURFACE_FACE 132 
#define  SURFACE_FORCED_META 131 
#define  SURFACE_META 130 
#define  SURFACE_PATCH 129 
#define  SURFACE_TRIANGLES 128 
 TYPE_3__* SubdivideMesh2 (TYPE_3__,int) ; 
 int /*<<< orphan*/  VectorAdd (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 float VectorNormalize (int*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patchSubdivisions ; 

int AddSurfaceModels( mapDrawSurface_t *ds ){
	surfaceModel_t  *model;
	int i, x, y, n, pw[ 5 ], r, localNumSurfaceModels, iterations;
	mesh_t src, *mesh, *subdivided;
	bspDrawVert_t centroid, *tri[ 3 ];
	float alpha;


	/* dummy check */
	if ( ds == NULL || ds->shaderInfo == NULL || ds->shaderInfo->surfaceModel == NULL ) {
		return 0;
	}

	/* init */
	localNumSurfaceModels = 0;

	/* walk the model list */
	for ( model = ds->shaderInfo->surfaceModel; model != NULL; model = model->next )
	{
		/* switch on type */
		switch ( ds->type )
		{
		/* handle brush faces and decals */
		case SURFACE_FACE:
		case SURFACE_DECAL:
			/* calculate centroid */
			memset( &centroid, 0, sizeof( centroid ) );
			alpha = 0.0f;

			/* walk verts */
			for ( i = 0; i < ds->numVerts; i++ )
			{
				VectorAdd( centroid.xyz, ds->verts[ i ].xyz, centroid.xyz );
				VectorAdd( centroid.normal, ds->verts[ i ].normal, centroid.normal );
				centroid.st[ 0 ] += ds->verts[ i ].st[ 0 ];
				centroid.st[ 1 ] += ds->verts[ i ].st[ 1 ];
				alpha += ds->verts[ i ].color[ 0 ][ 3 ];
			}

			/* average */
			centroid.xyz[ 0 ] /= ds->numVerts;
			centroid.xyz[ 1 ] /= ds->numVerts;
			centroid.xyz[ 2 ] /= ds->numVerts;
			if ( VectorNormalize( centroid.normal, centroid.normal ) == 0.0f ) {
				VectorCopy( ds->verts[ 0 ].normal, centroid.normal );
			}
			centroid.st[ 0 ]  /= ds->numVerts;
			centroid.st[ 1 ]  /= ds->numVerts;
			alpha /= ds->numVerts;
			centroid.color[ 0 ][ 0 ] = 0xFF;
			centroid.color[ 0 ][ 1 ] = 0xFF;
			centroid.color[ 0 ][ 2 ] = 0xFF;
			centroid.color[ 0 ][ 2 ] = ( alpha > 255.0f ? 0xFF : alpha );

			/* head vert is centroid */
			tri[ 0 ] = &centroid;

			/* walk fanned triangles */
			for ( i = 0; i < ds->numVerts; i++ )
			{
				/* set triangle */
				tri[ 1 ] = &ds->verts[ i ];
				tri[ 2 ] = &ds->verts[ ( i + 1 ) % ds->numVerts ];

				/* create models */
				n = AddSurfaceModelsToTriangle_r( ds, model, tri );
				if ( n < 0 ) {
					return n;
				}
				localNumSurfaceModels += n;
			}
			break;

		/* handle patches */
		case SURFACE_PATCH:
			/* subdivide the surface */
			src.width = ds->patchWidth;
			src.height = ds->patchHeight;
			src.verts = ds->verts;
			//%	subdivided = SubdivideMesh( src, 8.0f, 512 );
			iterations = IterationsForCurve( ds->longestCurve, patchSubdivisions );
			subdivided = SubdivideMesh2( src, iterations );

			/* fit it to the curve and remove colinear verts on rows/columns */
			PutMeshOnCurve( *subdivided );
			mesh = RemoveLinearMeshColumnsRows( subdivided );
			FreeMesh( subdivided );

			/* subdivide each quad to place the models */
			for ( y = 0; y < ( mesh->height - 1 ); y++ )
			{
				for ( x = 0; x < ( mesh->width - 1 ); x++ )
				{
					/* set indexes */
					pw[ 0 ] = x + ( y * mesh->width );
					pw[ 1 ] = x + ( ( y + 1 ) * mesh->width );
					pw[ 2 ] = x + 1 + ( ( y + 1 ) * mesh->width );
					pw[ 3 ] = x + 1 + ( y * mesh->width );
					pw[ 4 ] = x + ( y * mesh->width );      /* same as pw[ 0 ] */

					/* set radix */
					r = ( x + y ) & 1;

					/* triangle 1 */
					tri[ 0 ] = &mesh->verts[ pw[ r + 0 ] ];
					tri[ 1 ] = &mesh->verts[ pw[ r + 1 ] ];
					tri[ 2 ] = &mesh->verts[ pw[ r + 2 ] ];
					n = AddSurfaceModelsToTriangle_r( ds, model, tri );
					if ( n < 0 ) {
						return n;
					}
					localNumSurfaceModels += n;

					/* triangle 2 */
					tri[ 0 ] = &mesh->verts[ pw[ r + 0 ] ];
					tri[ 1 ] = &mesh->verts[ pw[ r + 2 ] ];
					tri[ 2 ] = &mesh->verts[ pw[ r + 3 ] ];
					n = AddSurfaceModelsToTriangle_r( ds, model, tri );
					if ( n < 0 ) {
						return n;
					}
					localNumSurfaceModels += n;
				}
			}

			/* free the subdivided mesh */
			FreeMesh( mesh );
			break;

		/* handle triangle surfaces */
		case SURFACE_TRIANGLES:
		case SURFACE_FORCED_META:
		case SURFACE_META:
			/* walk the triangle list */
			for ( i = 0; i < ds->numIndexes; i += 3 )
			{
				tri[ 0 ] = &ds->verts[ ds->indexes[ i ] ];
				tri[ 1 ] = &ds->verts[ ds->indexes[ i + 1 ] ];
				tri[ 2 ] = &ds->verts[ ds->indexes[ i + 2 ] ];
				n = AddSurfaceModelsToTriangle_r( ds, model, tri );
				if ( n < 0 ) {
					return n;
				}
				localNumSurfaceModels += n;
			}
			break;

		/* no support for flares, foghull, etc */
		default:
			break;
		}
	}

	/* return count */
	return localNumSurfaceModels;
}