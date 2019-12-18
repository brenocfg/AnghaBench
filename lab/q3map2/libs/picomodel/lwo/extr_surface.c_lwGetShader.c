#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; void* name; void* flags; void* ord; } ;
typedef  TYPE_1__ lwPlugin ;

/* Variables and functions */
 unsigned int ID_ENAB ; 
#define  ID_FUNC 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 TYPE_1__* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 void* getS0 (int /*<<< orphan*/ *) ; 
 void* getU2 (int /*<<< orphan*/ *) ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  getbytes (int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  lwFreePlugin (TYPE_1__*) ; 
 int /*<<< orphan*/  set_flen (int) ; 

lwPlugin *lwGetShader( picoMemStream_t *fp, int bloksz ){
	lwPlugin *shdr;
	unsigned int id;
	unsigned short sz;
	int hsz, rlen, pos;

	shdr = _pico_calloc( 1, sizeof( lwPlugin ) );
	if ( !shdr ) {
		return NULL;
	}

	pos = _pico_memstream_tell( fp );
	set_flen( 0 );
	hsz = getU2( fp );
	shdr->ord = getS0( fp );
	id = getU4( fp );
	sz = getU2( fp );
	if ( 0 > get_flen() ) {
		goto Fail;
	}

	while ( hsz > 0 ) {
		sz += sz & 1;
		hsz -= sz;
		if ( id == ID_ENAB ) {
			shdr->flags = getU2( fp );
			break;
		}
		else {
			_pico_memstream_seek( fp, sz, PICO_SEEK_CUR );
			id = getU4( fp );
			sz = getU2( fp );
		}
	}

	id = getU4( fp );
	sz = getU2( fp );
	if ( 0 > get_flen() ) {
		goto Fail;
	}

	while ( 1 ) {
		sz += sz & 1;
		set_flen( 0 );

		switch ( id ) {
		case ID_FUNC:
			shdr->name = getS0( fp );
			rlen = get_flen();
			shdr->data = getbytes( fp, sz - rlen );
			break;

		default:
			break;
		}

		/* error while reading the current subchunk? */

		rlen = get_flen();
		if ( rlen < 0 || rlen > sz ) {
			goto Fail;
		}

		/* skip unread parts of the current subchunk */

		if ( rlen < sz ) {
			_pico_memstream_seek( fp, sz - rlen, PICO_SEEK_CUR );
		}

		/* end of the shader block? */

		if ( bloksz <= _pico_memstream_tell( fp ) - pos ) {
			break;
		}

		/* get the next subchunk header */

		set_flen( 0 );
		id = getU4( fp );
		sz = getU2( fp );
		if ( 6 != get_flen() ) {
			goto Fail;
		}
	}

	set_flen( _pico_memstream_tell( fp ) - pos );
	return shdr;

Fail:
	lwFreePlugin( shdr );
	return NULL;
}