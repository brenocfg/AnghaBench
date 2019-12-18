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
 scalar_t__ FLEN_ERROR ; 
 scalar_t__ _pico_memstream_error (int /*<<< orphan*/ *) ; 
 int _pico_memstream_getc (int /*<<< orphan*/ *) ; 
 scalar_t__ flen ; 

int getVX( picoMemStream_t *fp ){
	int i, c;

	if ( flen == FLEN_ERROR ) {
		return 0;
	}

	c = _pico_memstream_getc( fp );
	if ( c != 0xFF ) {
		i = c << 8;
		c = _pico_memstream_getc( fp );
		i |= c;
		flen += 2;
	}
	else {
		c = _pico_memstream_getc( fp );
		i = c << 16;
		c = _pico_memstream_getc( fp );
		i |= c << 8;
		c = _pico_memstream_getc( fp );
		i |= c;
		flen += 4;
	}

	if ( _pico_memstream_error( fp ) ) {
		flen = FLEN_ERROR;
		return 0;
	}
	return i;
}