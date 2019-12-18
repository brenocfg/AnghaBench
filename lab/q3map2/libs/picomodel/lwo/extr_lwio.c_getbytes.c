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
 void* _pico_alloc (int) ; 
 int /*<<< orphan*/  _pico_free (void*) ; 
 int _pico_memstream_read (int /*<<< orphan*/ *,void*,int) ; 
 scalar_t__ flen ; 

void *getbytes( picoMemStream_t *fp, int size ){
	void *data;

	if ( flen == FLEN_ERROR ) {
		return NULL;
	}
	if ( size < 0 ) {
		flen = FLEN_ERROR;
		return NULL;
	}
	data = _pico_alloc( size );
	if ( !data ) {
		flen = FLEN_ERROR;
		return NULL;
	}
	if ( 1 != _pico_memstream_read( fp, data, size ) ) {
		flen = FLEN_ERROR;
		_pico_free( data );
		return NULL;
	}

	flen += size;
	return data;
}