#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_16__ {int planeNum; float* plane; float* lightmapAxis; void** indexes; TYPE_1__* si; } ;
typedef  TYPE_2__ metaTriangle_t ;
struct TYPE_17__ {float* normal; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_3__ bspDrawVert_t ;
struct TYPE_18__ {float* normal; float dist; } ;
struct TYPE_15__ {int compileFlags; float* lightmapAxis; } ;

/* Variables and functions */
 int AddMetaTriangle () ; 
 int C_VERTEXLIT ; 
 int /*<<< orphan*/  CalcLightmapAxis (float*,float*) ; 
 void* FindMetaVertex (TYPE_3__*) ; 
 scalar_t__ PlaneFromPoints (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 float VectorLength (float*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 TYPE_9__* mapplanes ; 
 scalar_t__ memcmp (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* metaTriangles ; 
 int numMetaTriangles ; 
 scalar_t__ qfalse ; 

int FindMetaTriangle( metaTriangle_t *src, bspDrawVert_t *a, bspDrawVert_t *b, bspDrawVert_t *c, int planeNum ){
	int triIndex;
	vec3_t dir;



	/* detect degenerate triangles fixme: do something proper here */
	VectorSubtract( a->xyz, b->xyz, dir );
	if ( VectorLength( dir ) < 0.125f ) {
		return -1;
	}
	VectorSubtract( b->xyz, c->xyz, dir );
	if ( VectorLength( dir ) < 0.125f ) {
		return -1;
	}
	VectorSubtract( c->xyz, a->xyz, dir );
	if ( VectorLength( dir ) < 0.125f ) {
		return -1;
	}

	/* find plane */
	if ( planeNum >= 0 ) {
		/* because of precision issues with small triangles, try to use the specified plane */
		src->planeNum = planeNum;
		VectorCopy( mapplanes[ planeNum ].normal, src->plane );
		src->plane[ 3 ] = mapplanes[ planeNum ].dist;
	}
	else
	{
		/* calculate a plane from the triangle's points (and bail if a plane can't be constructed) */
		src->planeNum = -1;
		if ( PlaneFromPoints( src->plane, a->xyz, b->xyz, c->xyz ) == qfalse ) {
			return -1;
		}
	}

	/* ydnar 2002-10-03: repair any bogus normals (busted ase import kludge) */
	if ( VectorLength( a->normal ) <= 0.0f ) {
		VectorCopy( src->plane, a->normal );
	}
	if ( VectorLength( b->normal ) <= 0.0f ) {
		VectorCopy( src->plane, b->normal );
	}
	if ( VectorLength( c->normal ) <= 0.0f ) {
		VectorCopy( src->plane, c->normal );
	}

	/* ydnar 2002-10-04: set lightmap axis if not already set */
	if ( !( src->si->compileFlags & C_VERTEXLIT ) &&
		 src->lightmapAxis[ 0 ] == 0.0f && src->lightmapAxis[ 1 ] == 0.0f && src->lightmapAxis[ 2 ] == 0.0f ) {
		/* the shader can specify an explicit lightmap axis */
		if ( src->si->lightmapAxis[ 0 ] || src->si->lightmapAxis[ 1 ] || src->si->lightmapAxis[ 2 ] ) {
			VectorCopy( src->si->lightmapAxis, src->lightmapAxis );
		}

		/* new axis-finding code */
		else{
			CalcLightmapAxis( src->plane, src->lightmapAxis );
		}
	}

	/* fill out the src triangle */
	src->indexes[ 0 ] = FindMetaVertex( a );
	src->indexes[ 1 ] = FindMetaVertex( b );
	src->indexes[ 2 ] = FindMetaVertex( c );

	/* try to find an existing triangle */
	#ifdef USE_EXHAUSTIVE_SEARCH
	{
		int i;
		metaTriangle_t  *tri;


		for ( i = 0, tri = metaTriangles; i < numMetaTriangles; i++, tri++ )
		{
			if ( memcmp( src, tri, sizeof( metaTriangle_t ) ) == 0 ) {
				return i;
			}
		}
	}
	#endif

	/* get a new triangle */
	triIndex = AddMetaTriangle();

	/* add the triangle */
	memcpy( &metaTriangles[ triIndex ], src, sizeof( metaTriangle_t ) );

	/* return the triangle index */
	return triIndex;
}