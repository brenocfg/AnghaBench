#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_t ;
struct TYPE_11__ {scalar_t__ culled; int planenum; int compileFlags; TYPE_1__* shaderInfo; TYPE_2__* winding; } ;
typedef  TYPE_3__ side_t ;
struct TYPE_12__ {TYPE_5__* brushes; } ;
typedef  TYPE_4__ entity_t ;
struct TYPE_13__ {int numsides; scalar_t__* mins; scalar_t__* maxs; TYPE_3__* sides; int /*<<< orphan*/ * original; struct TYPE_13__* next; } ;
typedef  TYPE_5__ brush_t ;
struct TYPE_9__ {scalar_t__ polygonOffset; scalar_t__ autosprite; } ;

/* Variables and functions */
 int C_NODRAW ; 
 int C_TRANSLUCENT ; 
 scalar_t__ CullVectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  SideInBrush (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ VectorCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_numCoinFaces ; 
 scalar_t__ g_numHiddenFaces ; 
 scalar_t__ qtrue ; 

void CullSides( entity_t *e ){
	int numPoints;
	int i, j, k, l, first, second, dir;
	winding_t   *w1, *w2;
	brush_t *b1, *b2;
	side_t      *side1, *side2;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- CullSides ---\n" );

	g_numHiddenFaces = 0;
	g_numCoinFaces = 0;

	/* brush interator 1 */
	for ( b1 = e->brushes; b1; b1 = b1->next )
	{
		/* sides check */
		if ( b1->numsides < 1 ) {
			continue;
		}

		/* brush iterator 2 */
		for ( b2 = b1->next; b2; b2 = b2->next )
		{
			/* sides check */
			if ( b2->numsides < 1 ) {
				continue;
			}

			/* original check */
			if ( b1->original == b2->original && b1->original != NULL ) {
				continue;
			}

			/* bbox check */
			j = 0;
			for ( i = 0; i < 3; i++ )
				if ( b1->mins[ i ] > b2->maxs[ i ] || b1->maxs[ i ] < b2->mins[ i ] ) {
					j++;
				}
			if ( j ) {
				continue;
			}

			/* cull inside sides */
			for ( i = 0; i < b1->numsides; i++ )
				SideInBrush( &b1->sides[ i ], b2 );
			for ( i = 0; i < b2->numsides; i++ )
				SideInBrush( &b2->sides[ i ], b1 );

			/* side iterator 1 */
			for ( i = 0; i < b1->numsides; i++ )
			{
				/* winding check */
				side1 = &b1->sides[ i ];
				w1 = side1->winding;
				if ( w1 == NULL ) {
					continue;
				}
				numPoints = w1->numpoints;
				if ( side1->shaderInfo == NULL ) {
					continue;
				}

				/* side iterator 2 */
				for ( j = 0; j < b2->numsides; j++ )
				{
					/* winding check */
					side2 = &b2->sides[ j ];
					w2 = side2->winding;
					if ( w2 == NULL ) {
						continue;
					}
					if ( side2->shaderInfo == NULL ) {
						continue;
					}
					if ( w1->numpoints != w2->numpoints ) {
						continue;
					}
					if ( side1->culled == qtrue && side2->culled == qtrue ) {
						continue;
					}

					/* compare planes */
					if ( ( side1->planenum & ~0x00000001 ) != ( side2->planenum & ~0x00000001 ) ) {
						continue;
					}

					/* get autosprite and polygonoffset status */
					if ( side1->shaderInfo &&
						 ( side1->shaderInfo->autosprite || side1->shaderInfo->polygonOffset ) ) {
						continue;
					}
					if ( side2->shaderInfo &&
						 ( side2->shaderInfo->autosprite || side2->shaderInfo->polygonOffset ) ) {
						continue;
					}

					/* find first common point */
					first = -1;
					for ( k = 0; k < numPoints; k++ )
					{
						if ( VectorCompare( w1->p[ 0 ], w2->p[ k ] ) ) {
							first = k;
							k = numPoints;
						}
					}
					if ( first == -1 ) {
						continue;
					}

					/* find second common point (regardless of winding order) */
					second = -1;
					dir = 0;
					if ( ( first + 1 ) < numPoints ) {
						second = first + 1;
					}
					else{
						second = 0;
					}
					if ( CullVectorCompare( w1->p[ 1 ], w2->p[ second ] ) ) {
						dir = 1;
					}
					else
					{
						if ( first > 0 ) {
							second = first - 1;
						}
						else{
							second = numPoints - 1;
						}
						if ( CullVectorCompare( w1->p[ 1 ], w2->p[ second ] ) ) {
							dir = -1;
						}
					}
					if ( dir == 0 ) {
						continue;
					}

					/* compare the rest of the points */
					l = first;
					for ( k = 0; k < numPoints; k++ )
					{
						if ( !CullVectorCompare( w1->p[ k ], w2->p[ l ] ) ) {
							k = 100000;
						}

						l += dir;
						if ( l < 0 ) {
							l = numPoints - 1;
						}
						else if ( l >= numPoints ) {
							l = 0;
						}
					}
					if ( k >= 100000 ) {
						continue;
					}

					/* cull face 1 */
					if ( !side2->culled && !( side2->compileFlags & C_TRANSLUCENT ) && !( side2->compileFlags & C_NODRAW ) ) {
						side1->culled = qtrue;
						g_numCoinFaces++;
					}

					if ( side1->planenum == side2->planenum && side1->culled == qtrue ) {
						continue;
					}

					/* cull face 2 */
					if ( !side1->culled && !( side1->compileFlags & C_TRANSLUCENT ) && !( side1->compileFlags & C_NODRAW ) ) {
						side2->culled = qtrue;
						g_numCoinFaces++;
					}
				}
			}
		}
	}

	/* emit some stats */
	Sys_FPrintf( SYS_VRB, "%9d hidden faces culled\n", g_numHiddenFaces );
	Sys_FPrintf( SYS_VRB, "%9d coincident faces culled\n", g_numCoinFaces );
}