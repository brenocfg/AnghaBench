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
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 scalar_t__ _pico_memstream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ flen ; 

void skipbytes( picoMemStream_t *fp, int n ){
	if ( flen == FLEN_ERROR ) {
		return;
	}
	if ( _pico_memstream_seek( fp, n, PICO_SEEK_CUR ) ) {
		flen = FLEN_ERROR;
	}
	else{
		flen += n;
	}
}