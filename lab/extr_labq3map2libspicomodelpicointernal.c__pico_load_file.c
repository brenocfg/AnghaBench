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
 int /*<<< orphan*/  _pico_ptr_load_file (char*,unsigned char**,int*) ; 

void _pico_load_file( char *name, unsigned char **buffer, int *bufSize ){
	/* sanity checks */
	if ( name == NULL ) {
		*bufSize = -1;
		return;
	}
	if ( _pico_ptr_load_file == NULL ) {
		*bufSize = -1;
		return;
	}
	/* do the actual call to read in the file; */
	/* BUFFER IS ALLOCATED BY THE EXTERNAL LOADFILE FUNC */
	_pico_ptr_load_file( name,buffer,bufSize );
}