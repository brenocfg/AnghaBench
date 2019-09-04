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
typedef  int /*<<< orphan*/  picoSurface_t ;
struct TYPE_3__ {int numSurfaces; int /*<<< orphan*/ ** surface; } ;
typedef  TYPE_1__ picoModel_t ;

/* Variables and functions */

picoSurface_t *PicoGetModelSurface( picoModel_t *model, int num ){
	/* a few sanity checks */
	if ( model == NULL ) {
		return NULL;
	}
	if ( model->surface == NULL ) {
		return NULL;
	}
	if ( num < 0 || num >= model->numSurfaces ) {
		return NULL;
	}

	/* return the surface */
	return model->surface[ num ];
}