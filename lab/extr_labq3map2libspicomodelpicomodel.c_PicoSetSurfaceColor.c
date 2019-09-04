#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void**** color; } ;
typedef  TYPE_1__ picoSurface_t ;
typedef  void** picoColor_t ;

/* Variables and functions */
 int /*<<< orphan*/  PicoAdjustSurface (TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PicoSetSurfaceColor( picoSurface_t *surface, int array, int num, picoColor_t color ){
	if ( surface == NULL || num < 0 || color == NULL ) {
		return;
	}
	if ( !PicoAdjustSurface( surface, num + 1, 0, array + 1, 0, 0 ) ) {
		return;
	}
	surface->color[ array ][ num ][ 0 ] = color[ 0 ];
	surface->color[ array ][ num ][ 1 ] = color[ 1 ];
	surface->color[ array ][ num ][ 2 ] = color[ 2 ];
	surface->color[ array ][ num ][ 3 ] = color[ 3 ];
}