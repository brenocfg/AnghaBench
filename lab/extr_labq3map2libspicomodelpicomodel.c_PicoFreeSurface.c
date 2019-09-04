#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numSTArrays; int numColorArrays; struct TYPE_5__** color; struct TYPE_5__** st; struct TYPE_5__* name; struct TYPE_5__* faceNormal; struct TYPE_5__* index; struct TYPE_5__* smoothingGroup; struct TYPE_5__* normal; struct TYPE_5__* xyz; } ;
typedef  TYPE_1__ picoSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 

void PicoFreeSurface( picoSurface_t *surface ){
	int i;

	/* dummy check */
	if ( surface == NULL ) {
		return;
	}

	/* free bits */
	_pico_free( surface->xyz );
	_pico_free( surface->normal );
	_pico_free( surface->smoothingGroup );
	_pico_free( surface->index );
	_pico_free( surface->faceNormal );

	if ( surface->name ) {
		_pico_free( surface->name );
	}

	/* free arrays */
	for ( i = 0; i < surface->numSTArrays; i++ )
		_pico_free( surface->st[ i ] );
	free( surface->st );
	for ( i = 0; i < surface->numColorArrays; i++ )
		_pico_free( surface->color[ i ] );
	free( surface->color );

	/* free the surface */
	_pico_free( surface );
}