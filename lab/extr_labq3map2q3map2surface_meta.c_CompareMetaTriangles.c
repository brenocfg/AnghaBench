#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_3__ {scalar_t__ si; scalar_t__ fogNum; int* indexes; } ;
typedef  TYPE_1__ metaTriangle_t ;
struct TYPE_4__ {scalar_t__* xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorSet (scalar_t__*,int,int,int) ; 
 TYPE_2__* metaVerts ; 

__attribute__((used)) static int CompareMetaTriangles( const void *a, const void *b ){
	int i, j, av, bv;
	vec3_t aMins, bMins;


	/* shader first */
	if ( ( (metaTriangle_t*) a )->si < ( (metaTriangle_t*) b )->si ) {
		return 1;
	}
	else if ( ( (metaTriangle_t*) a )->si > ( (metaTriangle_t*) b )->si ) {
		return -1;
	}

	/* then fog */
	else if ( ( (metaTriangle_t*) a )->fogNum < ( (metaTriangle_t*) b )->fogNum ) {
		return 1;
	}
	else if ( ( (metaTriangle_t*) a )->fogNum > ( (metaTriangle_t*) b )->fogNum ) {
		return -1;
	}

	/* then plane */
	#if 0
	else if ( npDegrees == 0.0f && ( (metaTriangle_t*) a )->si->nonplanar == qfalse &&
			  ( (metaTriangle_t*) a )->planeNum >= 0 && ( (metaTriangle_t*) a )->planeNum >= 0 ) {
		if ( ( (metaTriangle_t*) a )->plane[ 3 ] < ( (metaTriangle_t*) b )->plane[ 3 ] ) {
			return 1;
		}
		else if ( ( (metaTriangle_t*) a )->plane[ 3 ] > ( (metaTriangle_t*) b )->plane[ 3 ] ) {
			return -1;
		}
		else if ( ( (metaTriangle_t*) a )->plane[ 0 ] < ( (metaTriangle_t*) b )->plane[ 0 ] ) {
			return 1;
		}
		else if ( ( (metaTriangle_t*) a )->plane[ 0 ] > ( (metaTriangle_t*) b )->plane[ 0 ] ) {
			return -1;
		}
		else if ( ( (metaTriangle_t*) a )->plane[ 1 ] < ( (metaTriangle_t*) b )->plane[ 1 ] ) {
			return 1;
		}
		else if ( ( (metaTriangle_t*) a )->plane[ 1 ] > ( (metaTriangle_t*) b )->plane[ 1 ] ) {
			return -1;
		}
		else if ( ( (metaTriangle_t*) a )->plane[ 2 ] < ( (metaTriangle_t*) b )->plane[ 2 ] ) {
			return 1;
		}
		else if ( ( (metaTriangle_t*) a )->plane[ 2 ] > ( (metaTriangle_t*) b )->plane[ 2 ] ) {
			return -1;
		}
	}
	#endif

	/* then position in world */

	/* find mins */
	VectorSet( aMins, 999999, 999999, 999999 );
	VectorSet( bMins, 999999, 999999, 999999 );
	for ( i = 0; i < 3; i++ )
	{
		av = ( (metaTriangle_t*) a )->indexes[ i ];
		bv = ( (metaTriangle_t*) b )->indexes[ i ];
		for ( j = 0; j < 3; j++ )
		{
			if ( metaVerts[ av ].xyz[ j ] < aMins[ j ] ) {
				aMins[ j ] = metaVerts[ av ].xyz[ j ];
			}
			if ( metaVerts[ bv ].xyz[ j ] < bMins[ j ] ) {
				bMins[ j ] = metaVerts[ bv ].xyz[ j ];
			}
		}
	}

	/* test it */
	for ( i = 0; i < 3; i++ )
	{
		if ( aMins[ i ] < bMins[ i ] ) {
			return 1;
		}
		else if ( aMins[ i ] > bMins[ i ] ) {
			return -1;
		}
	}

	/* functionally equivalent */
	return 0;
}