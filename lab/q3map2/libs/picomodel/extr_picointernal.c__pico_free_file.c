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

/* Variables and functions */
 int /*<<< orphan*/  _pico_ptr_free_file (void*) ; 
 int /*<<< orphan*/  free (void*) ; 

void _pico_free_file( void *buffer ){
	/* sanity checks */
	if ( buffer == NULL ) {
		return;
	}

	/* use default free */
	if ( _pico_ptr_free_file == NULL ) {
		free( buffer );
		return;
	}
	/* free the allocated file */
	_pico_ptr_free_file( buffer );
}