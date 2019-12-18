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
 int _pico_memstream_read (int /*<<< orphan*/ *,float*,int) ; 
 scalar_t__ flen ; 
 int /*<<< orphan*/  revbytes (float*,int,int) ; 

float getF4( picoMemStream_t *fp ){
	float f;

	if ( flen == FLEN_ERROR ) {
		return 0.0f;
	}
	if ( 1 != _pico_memstream_read( fp, &f, 4 ) ) {
		flen = FLEN_ERROR;
		return 0.0f;
	}
	revbytes( &f, 4, 1 );
	flen += 4;
	return f;
}