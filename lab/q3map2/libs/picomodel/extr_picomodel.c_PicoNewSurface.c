#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* model; } ;
typedef  TYPE_1__ picoSurface_t ;
struct TYPE_11__ {int numSurfaces; TYPE_1__** surface; } ;
typedef  TYPE_2__ picoModel_t ;

/* Variables and functions */
 int /*<<< orphan*/  PicoAdjustModel (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PicoSetSurfaceName (TYPE_1__*,char*) ; 
 TYPE_1__* _pico_alloc (int) ; 
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

picoSurface_t *PicoNewSurface( picoModel_t *model ){
	picoSurface_t   *surface;
	char surfaceName[64];

	/* allocate and clear */
	surface = _pico_alloc( sizeof( *surface ) );
	if ( surface == NULL ) {
		return NULL;
	}
	memset( surface, 0, sizeof( *surface ) );

	/* attach it to the model */
	if ( model != NULL ) {
		/* adjust model */
		if ( !PicoAdjustModel( model, 0, model->numSurfaces + 1 ) ) {
			_pico_free( surface );
			return NULL;
		}

		/* attach */
		model->surface[ model->numSurfaces - 1 ] = surface;
		surface->model = model;

		/* set default name */
		sprintf( surfaceName, "Unnamed_%d", model->numSurfaces );
		PicoSetSurfaceName( surface, surfaceName );
	}

	/* return */
	return surface;
}