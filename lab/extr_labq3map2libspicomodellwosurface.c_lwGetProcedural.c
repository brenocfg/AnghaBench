#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  name; void** value; void* axis; } ;
struct TYPE_6__ {TYPE_1__ proc; } ;
struct TYPE_7__ {TYPE_2__ param; int /*<<< orphan*/  tmap; } ;
typedef  TYPE_3__ lwTexture ;

/* Variables and functions */
#define  ID_AXIS 131 
#define  ID_FUNC 130 
#define  ID_TMAP 129 
#define  ID_VALU 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 void* getF4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getS0 (int /*<<< orphan*/ *) ; 
 void* getU2 (int /*<<< orphan*/ *) ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  getbytes (int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  lwGetTMap (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_flen (int) ; 

int lwGetProcedural( picoMemStream_t *fp, int rsz, lwTexture *tex ){
	unsigned int id;
	unsigned short sz;
	int rlen, pos;

	pos = _pico_memstream_tell( fp );
	id = getU4( fp );
	sz = getU2( fp );
	if ( 0 > get_flen() ) {
		return 0;
	}

	while ( 1 ) {
		sz += sz & 1;
		set_flen( 0 );

		switch ( id ) {
		case ID_TMAP:
			if ( !lwGetTMap( fp, sz, &tex->tmap ) ) {
				return 0;
			}
			break;

		case ID_AXIS:
			tex->param.proc.axis = getU2( fp );
			break;

		case ID_VALU:
			tex->param.proc.value[ 0 ] = getF4( fp );
			if ( sz >= 8 ) {
				tex->param.proc.value[ 1 ] = getF4( fp );
			}
			if ( sz >= 12 ) {
				tex->param.proc.value[ 2 ] = getF4( fp );
			}
			break;

		case ID_FUNC:
			tex->param.proc.name = getS0( fp );
			rlen = get_flen();
			tex->param.proc.data = getbytes( fp, sz - rlen );
			break;

		default:
			break;
		}

		/* error while reading the current subchunk? */

		rlen = get_flen();
		if ( rlen < 0 || rlen > sz ) {
			return 0;
		}

		/* skip unread parts of the current subchunk */

		if ( rlen < sz ) {
			_pico_memstream_seek( fp, sz - rlen, PICO_SEEK_CUR );
		}

		/* end of the procedural block? */

		if ( rsz <= _pico_memstream_tell( fp ) - pos ) {
			break;
		}

		/* get the next subchunk header */

		set_flen( 0 );
		id = getU4( fp );
		sz = getU2( fp );
		if ( 6 != get_flen() ) {
			return 0;
		}
	}

	set_flen( _pico_memstream_tell( fp ) - pos );
	return 1;
}