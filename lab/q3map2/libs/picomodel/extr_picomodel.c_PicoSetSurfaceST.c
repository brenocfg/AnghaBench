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
typedef  void** picoVec2_t ;
struct TYPE_4__ {void**** st; } ;
typedef  TYPE_1__ picoSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  PicoAdjustSurface (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PicoSetSurfaceST( picoSurface_t *surface, int array, int num, picoVec2_t st ){
	if ( surface == NULL || num < 0 || st == NULL ) {
		return;
	}
	if ( !PicoAdjustSurface( surface, num + 1, array + 1, 0, 0, 0 ) ) {
		return;
	}
	surface->st[ array ][ num ][ 0 ] = st[ 0 ];
	surface->st[ array ][ num ][ 1 ] = st[ 1 ];
}