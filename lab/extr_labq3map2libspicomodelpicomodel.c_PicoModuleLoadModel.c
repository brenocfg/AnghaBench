#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ (* canload ) (char*,int /*<<< orphan*/ *,int) ;TYPE_2__* (* load ) (char*,int,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ picoModule_t ;
struct TYPE_9__ {TYPE_1__ const* module; } ;
typedef  TYPE_2__ picoModel_t ;
typedef  int /*<<< orphan*/  picoByte_t ;

/* Variables and functions */
 scalar_t__ PICO_PMV_OK ; 
 char* PicoGetModelFileName (TYPE_2__*) ; 
 int /*<<< orphan*/  PicoRemapModel (TYPE_2__*,char*) ; 
 char* _pico_alloc (scalar_t__) ; 
 int /*<<< orphan*/  _pico_free (char*) ; 
 int /*<<< orphan*/  _pico_setfext (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ stub1 (char*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* stub2 (char*,int,int /*<<< orphan*/ *,int) ; 

picoModel_t *PicoModuleLoadModel( const picoModule_t* pm, char* fileName, picoByte_t* buffer, int bufSize, int frameNum ){
	char    *modelFileName, *remapFileName;

	/* see whether this module can load the model file or not */
	if ( pm->canload( fileName, buffer, bufSize ) == PICO_PMV_OK ) {
		/* use loader provided by module to read the model data */
		picoModel_t* model = pm->load( fileName, frameNum, buffer, bufSize );
		if ( model == NULL ) {
			return NULL;
		}

		/* assign pointer to file format module */
		model->module = pm;

		/* get model file name */
		modelFileName = PicoGetModelFileName( model );

		/* apply model remappings from <model>.remap */
		if ( strlen( modelFileName ) ) {
			/* alloc copy of model file name */
			remapFileName = _pico_alloc( strlen( modelFileName ) + 20 );
			if ( remapFileName != NULL ) {
				/* copy model file name and change extension */
				strcpy( remapFileName, modelFileName );
				_pico_setfext( remapFileName, "remap" );

				/* try to remap model; we don't handle the result */
				PicoRemapModel( model, remapFileName );

				/* free the remap file name string */
				_pico_free( remapFileName );
			}
		}

		return model;
	}

	return NULL;
}