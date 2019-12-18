#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceInfo_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;
typedef  int /*<<< orphan*/  rawLightmap_t ;
struct TYPE_9__ {int numVerts; TYPE_4__* verts; } ;
typedef  TYPE_1__ radWinding_t ;
typedef  int /*<<< orphan*/  clipWork_t ;
typedef  int /*<<< orphan*/  bspDrawVert_t ;
struct TYPE_10__ {int numIndexes; int firstVert; int firstIndex; } ;
typedef  TYPE_2__ bspDrawSurface_t ;
struct TYPE_12__ {int /*<<< orphan*/ ** color; } ;
struct TYPE_11__ {int /*<<< orphan*/ ** color; } ;

/* Variables and functions */
 int MAX_LIGHTMAPS ; 
 float* RAD_VERTEX_LUXEL (int,int) ; 
 int /*<<< orphan*/  RadSubdivideDiffuseLight (int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ *) ; 
 int* bspDrawIndexes ; 
 TYPE_2__* bspDrawSurfaces ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/ * surfaceInfos ; 
 TYPE_3__* yDrawVerts ; 

void RadLightForTriangles( int num, int lightmapNum, rawLightmap_t *lm, shaderInfo_t *si, float scale, float subdivide, clipWork_t *cw ){
	int i, j, k, v;
	bspDrawSurface_t    *ds;
	surfaceInfo_t       *info;
	float               *radVertexLuxel;
	radWinding_t rw;


	/* get surface */
	ds = &bspDrawSurfaces[ num ];
	info = &surfaceInfos[ num ];

	/* each triangle is a potential emitter */
	rw.numVerts = 3;
	for ( i = 0; i < ds->numIndexes; i += 3 )
	{
		/* copy each vert */
		for ( j = 0; j < 3; j++ )
		{
			/* get vertex index and rad vertex luxel */
			v = ds->firstVert + bspDrawIndexes[ ds->firstIndex + i + j ];

			/* get most everything */
			memcpy( &rw.verts[ j ], &yDrawVerts[ v ], sizeof( bspDrawVert_t ) );

			/* fix colors */
			for ( k = 0; k < MAX_LIGHTMAPS; k++ )
			{
				radVertexLuxel = RAD_VERTEX_LUXEL( k, ds->firstVert + bspDrawIndexes[ ds->firstIndex + i + j ] );
				VectorCopy( radVertexLuxel, rw.verts[ j ].color[ k ] );
				rw.verts[ j ].color[ k ][ 3 ] = yDrawVerts[ v ].color[ k ][ 3 ];
			}
		}

		/* subdivide into area lights */
		RadSubdivideDiffuseLight( lightmapNum, ds, lm, si, scale, subdivide, qtrue, &rw, cw );
	}
}