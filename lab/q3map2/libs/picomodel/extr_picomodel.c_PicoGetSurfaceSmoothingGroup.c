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
struct TYPE_3__ {int numVertexes; int* smoothingGroup; } ;
typedef  TYPE_1__ picoSurface_t ;
typedef  int picoIndex_t ;

/* Variables and functions */

picoIndex_t PicoGetSurfaceSmoothingGroup( picoSurface_t *surface, int num ){
	if ( surface == NULL || num < 0 || num > surface->numVertexes ) {
		return -1;
	}
	return surface->smoothingGroup[ num ];
}