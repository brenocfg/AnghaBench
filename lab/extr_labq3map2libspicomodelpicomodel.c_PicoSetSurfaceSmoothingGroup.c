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
struct TYPE_4__ {int /*<<< orphan*/ * smoothingGroup; } ;
typedef  TYPE_1__ picoSurface_t ;
typedef  int /*<<< orphan*/  picoIndex_t ;

/* Variables and functions */
 int /*<<< orphan*/  PicoAdjustSurface (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PicoSetSurfaceSmoothingGroup( picoSurface_t *surface, int num, picoIndex_t smoothingGroup ){
	if ( num < 0 ) {
		return;
	}
	if ( !PicoAdjustSurface( surface, num + 1, 0, 0, 0, 0 ) ) {
		return;
	}
	surface->smoothingGroup[ num ] = smoothingGroup;
}