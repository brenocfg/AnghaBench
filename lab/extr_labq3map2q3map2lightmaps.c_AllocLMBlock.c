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
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int LIGHTMAP_HEIGHT ; 
 int LIGHTMAP_WIDTH ; 
 int* allocated ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean AllocLMBlock( int w, int h, int *x, int *y ){
	int i, j;
	int best, best2;

	best = LIGHTMAP_HEIGHT;

	for ( i = 0 ; i <= LIGHTMAP_WIDTH - w ; i++ ) {
		best2 = 0;

		for ( j = 0 ; j < w ; j++ ) {
			if ( allocated[i + j] >= best ) {
				break;
			}
			if ( allocated[i + j] > best2 ) {
				best2 = allocated[i + j];
			}
		}
		if ( j == w ) {   // this is a valid spot
			*x = i;
			*y = best = best2;
		}
	}

	if ( best + h > LIGHTMAP_HEIGHT ) {
		return qfalse;
	}

	for ( i = 0 ; i < w ; i++ ) {
		allocated[*x + i] = best + h;
	}

	return qtrue;
}