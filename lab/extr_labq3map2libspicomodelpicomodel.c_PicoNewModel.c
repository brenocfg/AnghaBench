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
struct TYPE_5__ {int numFrames; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;
typedef  TYPE_1__ picoModel_t ;

/* Variables and functions */
 TYPE_1__* _pico_alloc (int) ; 
 int /*<<< orphan*/  _pico_zero_bounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

picoModel_t *PicoNewModel( void ){
	picoModel_t *model;

	/* allocate */
	model = _pico_alloc( sizeof( picoModel_t ) );
	if ( model == NULL ) {
		return NULL;
	}

	/* clear */
	memset( model, 0, sizeof( picoModel_t ) );

	/* model set up */
	_pico_zero_bounds( model->mins, model->maxs );

	/* set initial frame count to 1 -sea */
	model->numFrames = 1;

	/* return ptr to new model */
	return model;
}