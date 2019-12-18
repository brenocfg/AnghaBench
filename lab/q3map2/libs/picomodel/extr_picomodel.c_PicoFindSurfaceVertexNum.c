#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* picoVec3_t ;
typedef  scalar_t__* picoVec2_t ;
struct TYPE_3__ {int numVertexes; scalar_t__** xyz; scalar_t__** normal; scalar_t__* smoothingGroup; scalar_t__*** st; scalar_t__* color; } ;
typedef  TYPE_1__ picoSurface_t ;
typedef  scalar_t__ picoIndex_t ;
typedef  scalar_t__ picoColor_t ;

/* Variables and functions */

int PicoFindSurfaceVertexNum( picoSurface_t *surface, picoVec3_t xyz, picoVec3_t normal, int numSTs, picoVec2_t *st, int numColors, picoColor_t *color, picoIndex_t smoothingGroup ){
	int i, j;


	/* dummy check */
	if ( surface == NULL || surface->numVertexes <= 0 ) {
		return -1;
	}

	/* walk vertex list */
	for ( i = 0; i < surface->numVertexes; i++ )
	{
		/* check xyz */
		if ( xyz != NULL && ( surface->xyz[ i ][ 0 ] != xyz[ 0 ] || surface->xyz[ i ][ 1 ] != xyz[ 1 ] || surface->xyz[ i ][ 2 ] != xyz[ 2 ] ) ) {
			continue;
		}

		/* check normal */
		if ( normal != NULL && ( surface->normal[ i ][ 0 ] != normal[ 0 ] || surface->normal[ i ][ 1 ] != normal[ 1 ] || surface->normal[ i ][ 2 ] != normal[ 2 ] ) ) {
			continue;
		}

		/* check normal */
		if ( surface->smoothingGroup[ i ] != smoothingGroup ) {
			continue;
		}

		/* check st */
		if ( numSTs > 0 && st != NULL ) {
			for ( j = 0; j < numSTs; j++ )
			{
				if ( surface->st[ j ][ i ][ 0 ] != st[ j ][ 0 ] || surface->st[ j ][ i ][ 1 ] != st[ j ][ 1 ] ) {
					break;
				}
			}
			if ( j != numSTs ) {
				continue;
			}
		}

		/* check color */
		if ( numColors > 0 && color != NULL ) {
			for ( j = 0; j < numSTs; j++ )
			{
				if ( *( (int*) surface->color[ j ] ) != *( (int*) color[ j ] ) ) {
					break;
				}
			}
			if ( j != numColors ) {
				continue;
			}
		}

		/* vertex matches */
		return i;
	}

	/* nada */
	return -1;
}