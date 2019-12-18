#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ shininess; scalar_t__ transparency; int /*<<< orphan*/  specularColor; int /*<<< orphan*/  diffuseColor; int /*<<< orphan*/  ambientColor; TYPE_2__* model; } ;
typedef  TYPE_1__ picoShader_t ;
struct TYPE_10__ {int numShaders; TYPE_1__** shader; } ;
typedef  TYPE_2__ picoModel_t ;

/* Variables and functions */
 int /*<<< orphan*/  PicoAdjustModel (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* _pico_alloc (int) ; 
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 
 int /*<<< orphan*/  _pico_set_color (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

picoShader_t *PicoNewShader( picoModel_t *model ){
	picoShader_t    *shader;

	/* allocate and clear */
	shader = _pico_alloc( sizeof( picoShader_t ) );
	if ( shader == NULL ) {
		return NULL;
	}
	memset( shader, 0, sizeof( picoShader_t ) );

	/* attach it to the model */
	if ( model != NULL ) {
		/* adjust model */
		if ( !PicoAdjustModel( model, model->numShaders + 1, 0 ) ) {
			_pico_free( shader );
			return NULL;
		}
		/* attach */
		model->shader[ model->numShaders - 1 ] = shader;
		shader->model = model;
	}
	/* setup default shader colors */
	_pico_set_color( shader->ambientColor, 0, 0, 0, 0 );
	_pico_set_color( shader->diffuseColor, 255, 255, 255, 1 );
	_pico_set_color( shader->specularColor, 0, 0, 0, 0 );

	/* no need to do this, but i do it anyway */
	shader->transparency = 0;
	shader->shininess = 0;

	/* return the newly created shader */
	return shader;
}