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
 int _pico_memstream_getc (int /*<<< orphan*/ *) ; 
 scalar_t__ flen ; 

unsigned char getU1( picoMemStream_t *fp ){
	int i;

	if ( flen == FLEN_ERROR ) {
		return 0;
	}
	i = _pico_memstream_getc( fp );
	if ( i < 0 ) {
		flen = FLEN_ERROR;
		return 0;
	}
	flen += 1;
	return i;
}