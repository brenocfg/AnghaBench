#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int* bspDrawIndexes ; 
 int numBSPDrawIndexes ; 
 int numRedundantIndexes ; 

int FindDrawIndexes( int numIndexes, int *indexes ){
	int i, j, numTestIndexes;


	/* dummy check */
	if ( numIndexes < 3 || numBSPDrawIndexes < numIndexes || indexes == NULL ) {
		return numBSPDrawIndexes;
	}

	/* set limit */
	numTestIndexes = 1 + numBSPDrawIndexes - numIndexes;

	/* handle 3 indexes as a special case for performance */
	if ( numIndexes == 3 ) {
		/* run through all indexes */
		for ( i = 0; i < numTestIndexes; i++ )
		{
			/* test 3 indexes */
			if ( indexes[ 0 ] == bspDrawIndexes[ i ] &&
				 indexes[ 1 ] == bspDrawIndexes[ i + 1 ] &&
				 indexes[ 2 ] == bspDrawIndexes[ i + 2 ] ) {
				numRedundantIndexes += numIndexes;
				return i;
			}
		}

		/* failed */
		return numBSPDrawIndexes;
	}

	/* handle 4 or more indexes */
	for ( i = 0; i < numTestIndexes; i++ )
	{
		/* test first 4 indexes */
		if ( indexes[ 0 ] == bspDrawIndexes[ i ] &&
			 indexes[ 1 ] == bspDrawIndexes[ i + 1 ] &&
			 indexes[ 2 ] == bspDrawIndexes[ i + 2 ] &&
			 indexes[ 3 ] == bspDrawIndexes[ i + 3 ] ) {
			/* handle 4 indexes */
			if ( numIndexes == 4 ) {
				return i;
			}

			/* test the remainder */
			for ( j = 4; j < numIndexes; j++ )
			{
				if ( indexes[ j ] != bspDrawIndexes[ i + j ] ) {
					break;
				}
				else if ( j == ( numIndexes - 1 ) ) {
					numRedundantIndexes += numIndexes;
					return i;
				}
			}
		}
	}

	/* failed */
	return numBSPDrawIndexes;
}