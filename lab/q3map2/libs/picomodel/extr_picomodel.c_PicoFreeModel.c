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
struct TYPE_4__ {int numShaders; int numSurfaces; int /*<<< orphan*/ * surface; int /*<<< orphan*/ * shader; struct TYPE_4__* fileName; struct TYPE_4__* name; } ;
typedef  TYPE_1__ picoModel_t ;

/* Variables and functions */
 int /*<<< orphan*/  PicoFreeShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoFreeSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void PicoFreeModel( picoModel_t *model ){
	int i;

	/* sanity check */
	if ( model == NULL ) {
		return;
	}

	/* free bits */
	if ( model->name ) {
		_pico_free( model->name );
	}

	if ( model->fileName ) {
		_pico_free( model->fileName );
	}

	/* free shaders */
	for ( i = 0; i < model->numShaders; i++ )
		PicoFreeShader( model->shader[ i ] );
	free( model->shader );

	/* free surfaces */
	for ( i = 0; i < model->numSurfaces; i++ )
		PicoFreeSurface( model->surface[ i ] );
	free( model->surface );

	/* free the model */
	_pico_free( model );
}