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
typedef  int /*<<< orphan*/  picoVec_t ;
struct TYPE_3__ {int numSTArrays; int numVertexes; int /*<<< orphan*/ *** st; } ;
typedef  TYPE_1__ picoSurface_t ;

/* Variables and functions */

picoVec_t *PicoGetSurfaceST( picoSurface_t *surface, int array, int num ){
	if ( surface == NULL || array < 0 || array > surface->numSTArrays || num < 0 || num > surface->numVertexes ) {
		return NULL;
	}
	return surface->st[ array ][ num ];
}