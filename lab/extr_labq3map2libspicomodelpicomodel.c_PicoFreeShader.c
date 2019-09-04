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
struct TYPE_4__ {struct TYPE_4__* mapName; struct TYPE_4__* name; } ;
typedef  TYPE_1__ picoShader_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 

void PicoFreeShader( picoShader_t *shader ){
	/* dummy check */
	if ( shader == NULL ) {
		return;
	}

	/* free bits */
	if ( shader->name ) {
		_pico_free( shader->name );
	}
	if ( shader->mapName ) {
		_pico_free( shader->mapName );
	}

	/* free the shader */
	_pico_free( shader );
}