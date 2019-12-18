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
struct TYPE_3__ {int /*<<< orphan*/ * fileName; } ;
typedef  TYPE_1__ picoModel_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _pico_clone_alloc (char*) ; 
 int /*<<< orphan*/  _pico_free (int /*<<< orphan*/ *) ; 

void PicoSetModelFileName( picoModel_t *model, char *fileName ){
	if ( model == NULL || fileName == NULL ) {
		return;
	}
	if ( model->fileName != NULL ) {
		_pico_free( model->fileName );
	}

	model->fileName = _pico_clone_alloc( fileName );
}