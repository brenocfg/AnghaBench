#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_24__ {TYPE_4__* foliage; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_25__ {int width; int height; TYPE_5__* verts; } ;
typedef  TYPE_2__ mesh_t ;
struct TYPE_26__ {int type; int numIndexes; size_t* indexes; int patchWidth; int patchHeight; int numFoliageInstances; int numVerts; TYPE_5__* verts; int /*<<< orphan*/  fogNum; int /*<<< orphan*/  lightmapScale; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  entityNum; TYPE_1__* shaderInfo; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
typedef  int /*<<< orphan*/  m4x4_t ;
struct TYPE_27__ {int /*<<< orphan*/  model; int /*<<< orphan*/  scale; struct TYPE_27__* next; } ;
typedef  TYPE_4__ foliage_t ;
struct TYPE_28__ {int** color; int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_5__ bspDrawVert_t ;
struct TYPE_23__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMesh (TYPE_2__*) ; 
 int /*<<< orphan*/  InsertModel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_LIGHTMAPS ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_2__) ; 
 TYPE_2__* RemoveLinearMeshColumnsRows (TYPE_2__*) ; 
 int SURFACE_FOLIAGE ; 
#define  SURFACE_FORCED_META 131 
#define  SURFACE_META 130 
#define  SURFACE_PATCH 129 
#define  SURFACE_TRIANGLES 128 
 int /*<<< orphan*/  SubdivideFoliageTriangle_r (TYPE_3__*,TYPE_4__*,TYPE_5__**) ; 
 TYPE_2__* SubdivideMesh (TYPE_2__,int,int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_12__* foliageInstances ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  m4x4_scale_for_vec3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* mapDrawSurfs ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int numFoliageInstances ; 
 int numMapDrawSurfs ; 
 TYPE_5__* safe_malloc (int) ; 

void Foliage( mapDrawSurface_t *src ){
	int i, j, k, x, y, pw[ 5 ], r, oldNumMapDrawSurfs;
	mapDrawSurface_t    *ds;
	shaderInfo_t        *si;
	foliage_t           *foliage;
	mesh_t srcMesh, *subdivided, *mesh;
	bspDrawVert_t       *verts, *dv[ 3 ], *fi;
	vec3_t scale;
	m4x4_t transform;


	/* get shader */
	si = src->shaderInfo;
	if ( si == NULL || si->foliage == NULL ) {
		return;
	}

	/* do every foliage */
	for ( foliage = si->foliage; foliage != NULL; foliage = foliage->next )
	{
		/* zero out */
		numFoliageInstances = 0;

		/* map the surface onto the lightmap origin/cluster/normal buffers */
		switch ( src->type )
		{
		case SURFACE_META:
		case SURFACE_FORCED_META:
		case SURFACE_TRIANGLES:
			/* get verts */
			verts = src->verts;

			/* map the triangles */
			for ( i = 0; i < src->numIndexes; i += 3 )
			{
				dv[ 0 ] = &verts[ src->indexes[ i ] ];
				dv[ 1 ] = &verts[ src->indexes[ i + 1 ] ];
				dv[ 2 ] = &verts[ src->indexes[ i + 2 ] ];
				SubdivideFoliageTriangle_r( src, foliage, dv );
			}
			break;

		case SURFACE_PATCH:
			/* make a mesh from the drawsurf */
			srcMesh.width = src->patchWidth;
			srcMesh.height = src->patchHeight;
			srcMesh.verts = src->verts;
			subdivided = SubdivideMesh( srcMesh, 8, 512 );

			/* fit it to the curve and remove colinear verts on rows/columns */
			PutMeshOnCurve( *subdivided );
			mesh = RemoveLinearMeshColumnsRows( subdivided );
			FreeMesh( subdivided );

			/* get verts */
			verts = mesh->verts;

			/* map the mesh quads */
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

					/* get drawverts and map first triangle */
					dv[ 0 ] = &verts[ pw[ r + 0 ] ];
					dv[ 1 ] = &verts[ pw[ r + 1 ] ];
					dv[ 2 ] = &verts[ pw[ r + 2 ] ];
					SubdivideFoliageTriangle_r( src, foliage, dv );

					/* get drawverts and map second triangle */
					dv[ 0 ] = &verts[ pw[ r + 0 ] ];
					dv[ 1 ] = &verts[ pw[ r + 2 ] ];
					dv[ 2 ] = &verts[ pw[ r + 3 ] ];
					SubdivideFoliageTriangle_r( src, foliage, dv );
				}
			}

			/* free the mesh */
			FreeMesh( mesh );
			break;

		default:
			break;
		}

		/* any origins? */
		if ( numFoliageInstances < 1 ) {
			continue;
		}

		/* remember surface count */
		oldNumMapDrawSurfs = numMapDrawSurfs;

		/* set transform matrix */
		VectorSet( scale, foliage->scale, foliage->scale, foliage->scale );
		m4x4_scale_for_vec3( transform, scale );

		/* add the model to the bsp */
		InsertModel( foliage->model, 0, transform, NULL, NULL, src->entityNum, src->castShadows, src->recvShadows, 0, src->lightmapScale );

		/* walk each new surface */
		for ( i = oldNumMapDrawSurfs; i < numMapDrawSurfs; i++ )
		{
			/* get surface */
			ds = &mapDrawSurfs[ i ];

			/* set up */
			ds->type = SURFACE_FOLIAGE;
			ds->numFoliageInstances = numFoliageInstances;

			/* a wee hack */
			ds->patchWidth = ds->numFoliageInstances;
			ds->patchHeight = ds->numVerts;

			/* set fog to be same as source surface */
			ds->fogNum = src->fogNum;

			/* add a drawvert for every instance */
			verts = safe_malloc( ( ds->numVerts + ds->numFoliageInstances ) * sizeof( *verts ) );
			memset( verts, 0, ( ds->numVerts + ds->numFoliageInstances ) * sizeof( *verts ) );
			memcpy( verts, ds->verts, ds->numVerts * sizeof( *verts ) );
			free( ds->verts );
			ds->verts = verts;

			/* copy the verts */
			for ( j = 0; j < ds->numFoliageInstances; j++ )
			{
				/* get vert (foliage instance) */
				fi = &ds->verts[ ds->numVerts + j ];

				/* copy xyz and normal */
				VectorCopy( foliageInstances[ j ].xyz, fi->xyz );
				VectorCopy( foliageInstances[ j ].normal, fi->normal );

				/* ydnar: set color */
				for ( k = 0; k < MAX_LIGHTMAPS; k++ )
				{
					fi->color[ k ][ 0 ] = 255;
					fi->color[ k ][ 1 ] = 255;
					fi->color[ k ][ 2 ] = 255;
					fi->color[ k ][ 3 ] = 255;
				}
			}

			/* increment */
			ds->numVerts += ds->numFoliageInstances;
		}
	}
}