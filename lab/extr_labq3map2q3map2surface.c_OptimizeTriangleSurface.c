#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numIndexes; int* indexes; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_4__ {scalar_t__ autosprite; } ;

/* Variables and functions */
 int VERTEX_CACHE_SIZE ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* safe_malloc (int) ; 

__attribute__((used)) static void OptimizeTriangleSurface( mapDrawSurface_t *ds ){
	int i, j, k, temp, first, best, bestScore, score;
	int vertexCache[ VERTEX_CACHE_SIZE + 1 ];       /* one more for optimizing insert */
	int     *indexes;


	/* certain surfaces don't get optimized */
	if ( ds->numIndexes <= VERTEX_CACHE_SIZE ||
		 ds->shaderInfo->autosprite ) {
		return;
	}

	/* create index scratch pad */
	indexes = safe_malloc( ds->numIndexes * sizeof( *indexes ) );
	memcpy( indexes, ds->indexes, ds->numIndexes * sizeof( *indexes ) );

	/* setup */
	for ( i = 0; i <= VERTEX_CACHE_SIZE && i < ds->numIndexes; i++ )
		vertexCache[ i ] = indexes[ i ];

	/* add triangles in a vertex cache-aware order */
	for ( i = 0; i < ds->numIndexes; i += 3 )
	{
		/* find best triangle given the current vertex cache */
		first = -1;
		best = -1;
		bestScore = -1;
		for ( j = 0; j < ds->numIndexes; j += 3 )
		{
			/* valid triangle? */
			if ( indexes[ j ] != -1 ) {
				/* set first if necessary */
				if ( first < 0 ) {
					first = j;
				}

				/* score the triangle */
				score = 0;
				for ( k = 0; k < VERTEX_CACHE_SIZE; k++ )
				{
					if ( indexes[ j ] == vertexCache[ k ] || indexes[ j + 1 ] == vertexCache[ k ] || indexes[ j + 2 ] == vertexCache[ k ] ) {
						score++;
					}
				}

				/* better triangle? */
				if ( score > bestScore ) {
					bestScore = score;
					best = j;
				}

				/* a perfect score of 3 means this triangle's verts are already present in the vertex cache */
				if ( score == 3 ) {
					break;
				}
			}
		}

		/* check if no decent triangle was found, and use first available */
		if ( best < 0 ) {
			best = first;
		}

		/* valid triangle? */
		if ( best >= 0 ) {
			/* add triangle to vertex cache */
			for ( j = 0; j < 3; j++ )
			{
				for ( k = 0; k < VERTEX_CACHE_SIZE; k++ )
				{
					if ( indexes[ best + j ] == vertexCache[ k ] ) {
						break;
					}
				}

				if ( k >= VERTEX_CACHE_SIZE ) {
					/* pop off top of vertex cache */
					for ( k = VERTEX_CACHE_SIZE; k > 0; k-- )
						vertexCache[ k ] = vertexCache[ k - 1 ];

					/* add vertex */
					vertexCache[ 0 ] = indexes[ best + j ];
				}
			}

			/* add triangle to surface */
			ds->indexes[ i ] = indexes[ best ];
			ds->indexes[ i + 1 ] = indexes[ best + 1 ];
			ds->indexes[ i + 2 ] = indexes[ best + 2 ];

			/* clear from input pool */
			indexes[ best ] = -1;
			indexes[ best + 1 ] = -1;
			indexes[ best + 2 ] = -1;

			/* sort triangle windings (312 -> 123) */
			while ( ds->indexes[ i ] > ds->indexes[ i + 1 ] || ds->indexes[ i ] > ds->indexes[ i + 2 ] )
			{
				temp = ds->indexes[ i ];
				ds->indexes[ i ] = ds->indexes[ i + 1 ];
				ds->indexes[ i + 1 ] = ds->indexes[ i + 2 ];
				ds->indexes[ i + 2 ] = temp;
			}
		}
	}

	/* clean up */
	free( indexes );
}