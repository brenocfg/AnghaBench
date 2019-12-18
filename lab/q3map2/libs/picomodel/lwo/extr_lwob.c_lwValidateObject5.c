#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;

/* Variables and functions */
 unsigned int ID_FORM ; 
 unsigned int ID_LWOB ; 
 int PICO_PMV_ERROR_IDENT ; 
 int PICO_PMV_ERROR_MEMORY ; 
 int PICO_PMV_ERROR_SIZE ; 
 int PICO_PMV_OK ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  set_flen (int /*<<< orphan*/ ) ; 

int lwValidateObject5( char *filename, picoMemStream_t *fp, unsigned int *failID, int *failpos ){
	unsigned int id, formsize, type;


	/* open the file */

	if ( !fp ) {
		return PICO_PMV_ERROR_MEMORY;
	}

	/* read the first 12 bytes */

	set_flen( 0 );
	id       = getU4( fp );
	formsize = getU4( fp );
	type     = getU4( fp );
	if ( 12 != get_flen() ) {
		return PICO_PMV_ERROR_SIZE;
	}

	/* LWOB? */

	if ( id != ID_FORM || type != ID_LWOB ) {
		if ( failpos ) {
			*failpos = 12;
		}
		return PICO_PMV_ERROR_IDENT;
	}

	return PICO_PMV_OK;
}