#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ picoSurface_t ;
struct TYPE_6__ {int numSurfaces; TYPE_1__** surface; } ;
typedef  TYPE_2__ picoModel_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_stricmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ *) ; 

picoSurface_t *PicoFindSurface(
	picoModel_t *model, char *name, int caseSensitive ){
	int i;

	/* sanity check */
	if ( model == NULL || name == NULL ) {
		return NULL;
	}

	/* walk list */
	for ( i = 0; i < model->numSurfaces; i++ )
	{
		/* skip null surfaces or surfaces with null names */
		if ( model->surface[ i ] == NULL ||
			 model->surface[ i ]->name == NULL ) {
			continue;
		}

		/* compare the surface name with name we're looking for */
		if ( caseSensitive ) {
			if ( !strcmp( name,model->surface[ i ]->name ) ) {
				return model->surface[ i ];
			}
		}
		else {
			if ( !_pico_stricmp( name,model->surface[ i ]->name ) ) {
				return model->surface[ i ];
			}
		}
	}
	/* named surface not found */
	return NULL;
}