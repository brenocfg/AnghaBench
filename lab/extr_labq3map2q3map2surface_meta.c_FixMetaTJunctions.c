#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
typedef  float* vec3_t ;
struct TYPE_16__ {int compileFlags; scalar_t__ notjunc; scalar_t__ autosprite; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_17__ {float* plane; size_t* indexes; TYPE_1__* si; } ;
typedef  TYPE_2__ metaTriangle_t ;
typedef  int /*<<< orphan*/  junc ;
struct TYPE_18__ {float kingpinLength; float* plane; size_t kingpin; float* origin; } ;
typedef  TYPE_3__ edge_t ;
struct TYPE_19__ {float* xyz; int** color; } ;
typedef  TYPE_4__ bspDrawVert_t ;

/* Variables and functions */
 int AddMetaTriangle () ; 
 int C_NODRAW ; 
 int /*<<< orphan*/  CreateEdge (float*,float*,float*,TYPE_3__*) ; 
 float DotProduct (float*,float*) ; 
 int FindMetaVertex (TYPE_4__*) ; 
 int I_FloatTime () ; 
 int /*<<< orphan*/  LerpDrawVertAmount (TYPE_4__*,TYPE_4__*,float,TYPE_4__*) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ TJ_EDGE_EPSILON ; 
 scalar_t__ TJ_PLANE_EPSILON ; 
 scalar_t__ TJ_POINT_EPSILON ; 
 scalar_t__ VectorCompare (float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorSet (int*,int,int,int) ; 
 scalar_t__ fabs (float) ; 
 int firstSearchMetaVert ; 
 int /*<<< orphan*/  memcmp (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_2__* metaTriangles ; 
 TYPE_4__* metaVerts ; 
 int numMetaTriangles ; 
 int numMetaVerts ; 

void FixMetaTJunctions( void ){
	int i, j, k, f, fOld, start, vertIndex, triIndex, numTJuncs;
	metaTriangle_t  *tri, *newTri;
	shaderInfo_t    *si;
	bspDrawVert_t   *a, *b, *c, junc;
	float dist, amount;
	vec3_t pt;
	vec4_t plane;
	edge_t edges[ 3 ];


	/* this code is crap; revisit later */
	return;

	/* note it */
	Sys_FPrintf( SYS_VRB, "--- FixMetaTJunctions ---\n" );

	/* init pacifier */
	fOld = -1;
	start = I_FloatTime();

	/* walk triangle list */
	numTJuncs = 0;
	for ( i = 0; i < numMetaTriangles; i++ )
	{
		/* get triangle */
		tri = &metaTriangles[ i ];

		/* print pacifier */
		f = 10 * i / numMetaTriangles;
		if ( f != fOld ) {
			fOld = f;
			Sys_FPrintf( SYS_VRB, "%d...", f );
		}

		/* attempt to early out */
		si = tri->si;
		if ( ( si->compileFlags & C_NODRAW ) || si->autosprite || si->notjunc ) {
			continue;
		}

		/* calculate planes */
		VectorCopy( tri->plane, plane );
		plane[ 3 ] = tri->plane[ 3 ];
		CreateEdge( plane, metaVerts[ tri->indexes[ 0 ] ].xyz, metaVerts[ tri->indexes[ 1 ] ].xyz, &edges[ 0 ] );
		CreateEdge( plane, metaVerts[ tri->indexes[ 1 ] ].xyz, metaVerts[ tri->indexes[ 2 ] ].xyz, &edges[ 1 ] );
		CreateEdge( plane, metaVerts[ tri->indexes[ 2 ] ].xyz, metaVerts[ tri->indexes[ 0 ] ].xyz, &edges[ 2 ] );

		/* walk meta vert list */
		for ( j = 0; j < numMetaVerts; j++ )
		{
			/* get vert */
			VectorCopy( metaVerts[ j ].xyz, pt );

			/* debug code: darken verts */
			if ( i == 0 ) {
				VectorSet( metaVerts[ j ].color[ 0 ], 8, 8, 8 );
			}

			/* determine if point lies in the triangle's plane */
			dist = DotProduct( pt, plane ) - plane[ 3 ];
			if ( fabs( dist ) > TJ_PLANE_EPSILON ) {
				continue;
			}

			/* skip this point if it already exists in the triangle */
			for ( k = 0; k < 3; k++ )
			{
				if ( fabs( pt[ 0 ] - metaVerts[ tri->indexes[ k ] ].xyz[ 0 ] ) <= TJ_POINT_EPSILON &&
					 fabs( pt[ 1 ] - metaVerts[ tri->indexes[ k ] ].xyz[ 1 ] ) <= TJ_POINT_EPSILON &&
					 fabs( pt[ 2 ] - metaVerts[ tri->indexes[ k ] ].xyz[ 2 ] ) <= TJ_POINT_EPSILON ) {
					break;
				}
			}
			if ( k < 3 ) {
				continue;
			}

			/* walk edges */
			for ( k = 0; k < 3; k++ )
			{
				/* ignore bogus edges */
				if ( fabs( edges[ k ].kingpinLength ) < TJ_EDGE_EPSILON ) {
					continue;
				}

				/* determine if point lies on the edge */
				dist = DotProduct( pt, edges[ k ].plane ) - edges[ k ].plane[ 3 ];
				if ( fabs( dist ) > TJ_EDGE_EPSILON ) {
					continue;
				}

				/* determine how far along the edge the point lies */
				amount = ( pt[ edges[ k ].kingpin ] - edges[ k ].origin[ edges[ k ].kingpin ] ) / edges[ k ].kingpinLength;
				if ( amount <= 0.0f || amount >= 1.0f ) {
					continue;
				}

				#if 0
				dist = DotProduct( pt, edges[ k ].edge ) - edges[ k ].edge[ 3 ];
				if ( dist <= -0.0f || dist >= edges[ k ].length ) {
					continue;
				}
				amount = dist / edges[ k ].length;
				#endif

				/* debug code: brighten this point */
				//%	metaVerts[ j ].color[ 0 ][ 0 ] += 5;
				//%	metaVerts[ j ].color[ 0 ][ 1 ] += 4;
				VectorSet( metaVerts[ tri->indexes[ k ] ].color[ 0 ], 255, 204, 0 );
				VectorSet( metaVerts[ tri->indexes[ ( k + 1 ) % 3 ] ].color[ 0 ], 255, 204, 0 );


				/* the edge opposite the zero-weighted vertex was hit, so use that as an amount */
				a = &metaVerts[ tri->indexes[ k % 3 ] ];
				b = &metaVerts[ tri->indexes[ ( k + 1 ) % 3 ] ];
				c = &metaVerts[ tri->indexes[ ( k + 2 ) % 3 ] ];

				/* make new vert */
				LerpDrawVertAmount( a, b, amount, &junc );
				VectorCopy( pt, junc.xyz );

				/* compare against existing verts */
				if ( VectorCompare( junc.xyz, a->xyz ) || VectorCompare( junc.xyz, b->xyz ) || VectorCompare( junc.xyz, c->xyz ) ) {
					continue;
				}

				/* see if we can just re-use the existing vert */
				if ( !memcmp( &metaVerts[ j ], &junc, sizeof( junc ) ) ) {
					vertIndex = j;
				}
				else
				{
					/* find new vertex (note: a and b are invalid pointers after this) */
					firstSearchMetaVert = numMetaVerts;
					vertIndex = FindMetaVertex( &junc );
					if ( vertIndex < 0 ) {
						continue;
					}
				}

				/* make new triangle */
				triIndex = AddMetaTriangle();
				if ( triIndex < 0 ) {
					continue;
				}

				/* get triangles */
				tri = &metaTriangles[ i ];
				newTri = &metaTriangles[ triIndex ];

				/* copy the triangle */
				memcpy( newTri, tri, sizeof( *tri ) );

				/* fix verts */
				tri->indexes[ ( k + 1 ) % 3 ] = vertIndex;
				newTri->indexes[ k ] = vertIndex;

				/* recalculate edges */
				CreateEdge( plane, metaVerts[ tri->indexes[ 0 ] ].xyz, metaVerts[ tri->indexes[ 1 ] ].xyz, &edges[ 0 ] );
				CreateEdge( plane, metaVerts[ tri->indexes[ 1 ] ].xyz, metaVerts[ tri->indexes[ 2 ] ].xyz, &edges[ 1 ] );
				CreateEdge( plane, metaVerts[ tri->indexes[ 2 ] ].xyz, metaVerts[ tri->indexes[ 0 ] ].xyz, &edges[ 2 ] );

				/* debug code */
				metaVerts[ vertIndex ].color[ 0 ][ 0 ] = 255;
				metaVerts[ vertIndex ].color[ 0 ][ 1 ] = 204;
				metaVerts[ vertIndex ].color[ 0 ][ 2 ] = 0;

				/* add to counter and end processing of this vert */
				numTJuncs++;
				break;
			}
		}
	}

	/* print time */
	Sys_FPrintf( SYS_VRB, " (%d)\n", (int) ( I_FloatTime() - start ) );

	/* emit some stats */
	Sys_FPrintf( SYS_VRB, "%9d T-junctions added\n", numTJuncs );
}