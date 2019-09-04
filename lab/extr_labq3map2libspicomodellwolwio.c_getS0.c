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
 int /*<<< orphan*/  PICO_SEEK_SET ; 
 char* _pico_alloc (int) ; 
 int _pico_memstream_getc (int /*<<< orphan*/ *) ; 
 int _pico_memstream_read (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ _pico_memstream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ flen ; 

char *getS0( picoMemStream_t *fp ){
	char *s;
	int i, c, len, pos;

	if ( flen == FLEN_ERROR ) {
		return NULL;
	}

	pos = _pico_memstream_tell( fp );
	for ( i = 1; ; i++ ) {
		c = _pico_memstream_getc( fp );
		if ( c <= 0 ) {
			break;
		}
	}
	if ( c < 0 ) {
		flen = FLEN_ERROR;
		return NULL;
	}

	if ( i == 1 ) {
		if ( _pico_memstream_seek( fp, pos + 2, PICO_SEEK_SET ) ) {
			flen = FLEN_ERROR;
		}
		else{
			flen += 2;
		}
		return NULL;
	}

	len = i + ( i & 1 );
	s = _pico_alloc( len );
	if ( !s ) {
		flen = FLEN_ERROR;
		return NULL;
	}

	if ( _pico_memstream_seek( fp, pos, PICO_SEEK_SET ) ) {
		flen = FLEN_ERROR;
		return NULL;
	}
	if ( 1 != _pico_memstream_read( fp, s, len ) ) {
		flen = FLEN_ERROR;
		return NULL;
	}

	flen += len;
	return s;
}