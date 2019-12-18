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
struct TYPE_3__ {int numSurfaces; int /*<<< orphan*/ * surface; } ;
typedef  TYPE_1__ picoModel_t ;

/* Variables and functions */
 scalar_t__ PicoGetSurfaceNumVertexes (int /*<<< orphan*/ ) ; 

int PicoGetModelTotalVertexes( picoModel_t *model ){
	int i, count;


	if ( model == NULL ) {
		return 0;
	}
	if ( model->surface == NULL ) {
		return 0;
	}

	count = 0;
	for ( i = 0; i < model->numSurfaces; i++ )
		count += PicoGetSurfaceNumVertexes( model->surface[ i ] );

	return count;
}