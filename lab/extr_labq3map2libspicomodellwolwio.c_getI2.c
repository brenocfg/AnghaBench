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
 int _pico_memstream_read (int /*<<< orphan*/ *,short*,int) ; 
 scalar_t__ flen ; 
 int /*<<< orphan*/  revbytes (short*,int,int) ; 

short getI2( picoMemStream_t *fp ){
	short i;

	if ( flen == FLEN_ERROR ) {
		return 0;
	}
	if ( 1 != _pico_memstream_read( fp, &i, 2 ) ) {
		flen = FLEN_ERROR;
		return 0;
	}
	revbytes( &i, 2, 1 );
	flen += 2;
	return i;
}