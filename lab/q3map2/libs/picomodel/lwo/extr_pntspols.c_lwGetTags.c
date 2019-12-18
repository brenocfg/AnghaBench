#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_3__ {int offset; int count; int /*<<< orphan*/ * tag; } ;
typedef  TYPE_1__ lwTagList ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (char*) ; 
 int /*<<< orphan*/  _pico_realloc (void*,int,int) ; 
 char* getbytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgetS0 (char**) ; 
 int strlen (char*) ; 

int lwGetTags( picoMemStream_t *fp, int cksize, lwTagList *tlist ){
	char *buf, *bp;
	int i, len, ntags;

	if ( cksize == 0 ) {
		return 1;
	}

	/* read the whole chunk */

	set_flen( 0 );
	buf = getbytes( fp, cksize );
	if ( !buf ) {
		return 0;
	}

	/* count the strings */

	ntags = 0;
	bp = buf;
	while ( bp < buf + cksize ) {
		len = strlen( bp ) + 1;
		len += len & 1;
		bp += len;
		++ntags;
	}

	/* expand the string array to hold the new tags */

	tlist->offset = tlist->count;
	tlist->count += ntags;
	if ( !_pico_realloc( (void *) &tlist->tag, ( tlist->count - ntags ) * sizeof( char * ), tlist->count * sizeof( char * ) ) ) {
		goto Fail;
	}
	memset( &tlist->tag[ tlist->offset ], 0, ntags * sizeof( char * ) );

	/* copy the new tags to the tag array */

	bp = buf;
	for ( i = 0; i < ntags; i++ )
		tlist->tag[ i + tlist->offset ] = sgetS0( &bp );

	_pico_free( buf );
	return 1;

Fail:
	if ( buf ) {
		_pico_free( buf );
	}
	return 0;
}