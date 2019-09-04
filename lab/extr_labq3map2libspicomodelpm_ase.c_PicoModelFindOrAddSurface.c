#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* shader; } ;
typedef  TYPE_1__ picoSurface_t ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ picoShader_t ;
struct TYPE_15__ {int numSurfaces; TYPE_1__** surface; } ;
typedef  TYPE_3__ picoModel_t ;

/* Variables and functions */
 int /*<<< orphan*/  PICO_ERROR ; 
 int /*<<< orphan*/  PICO_TRIANGLES ; 
 TYPE_1__* PicoNewSurface (TYPE_3__*) ; 
 int /*<<< orphan*/  PicoSetSurfaceName (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PicoSetSurfaceShader (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PicoSetSurfaceType (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pico_printf (int /*<<< orphan*/ ,char*) ; 

picoSurface_t* PicoModelFindOrAddSurface( picoModel_t *model, picoShader_t* shader ){
	/* see if a surface already has the shader */
	int i = 0;
	for ( ; i < model->numSurfaces ; i++ )
	{
		picoSurface_t* workSurface = model->surface[i];
		if ( workSurface->shader == shader ) {
			return workSurface;
		}
	}

	/* no surface uses this shader yet, so create a new surface */

	{
		/* create a new surface in the model for the unique shader */
		picoSurface_t* workSurface = PicoNewSurface( model );
		if ( !workSurface ) {
			_pico_printf( PICO_ERROR, "Could not allocate a new surface!\n" );
			return 0;
		}

		/* do surface setup */
		PicoSetSurfaceType( workSurface, PICO_TRIANGLES );
		PicoSetSurfaceName( workSurface, shader->name );
		PicoSetSurfaceShader( workSurface, shader );

		return workSurface;
	}
}