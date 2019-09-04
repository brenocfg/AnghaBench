#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_7__ {void** ikey; TYPE_1__* key; void* repeat; void* end; void* start; void* itemname; void* paramname; } ;
struct TYPE_8__ {TYPE_2__ grad; } ;
struct TYPE_9__ {TYPE_3__ param; int /*<<< orphan*/  tmap; } ;
typedef  TYPE_4__ lwTexture ;
typedef  int /*<<< orphan*/  lwGradKey ;
struct TYPE_6__ {void** rgba; void* value; } ;

/* Variables and functions */
#define  ID_FKEY 135 
#define  ID_GREN 134 
#define  ID_GRPT 133 
#define  ID_GRST 132 
#define  ID_IKEY 131 
#define  ID_INAM 130 
#define  ID_PNAM 129 
#define  ID_TMAP 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 void* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 void* getF4 (int /*<<< orphan*/ *) ; 
 void* getS0 (int /*<<< orphan*/ *) ; 
 void* getU2 (int /*<<< orphan*/ *) ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  lwGetTMap (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_flen (int) ; 

int lwGetGradient( picoMemStream_t *fp, int rsz, lwTexture *tex ){
	unsigned int id;
	unsigned short sz;
	int rlen, pos, i, j, nkeys;

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

		case ID_PNAM:
			tex->param.grad.paramname = getS0( fp );
			break;

		case ID_INAM:
			tex->param.grad.itemname = getS0( fp );
			break;

		case ID_GRST:
			tex->param.grad.start = getF4( fp );
			break;

		case ID_GREN:
			tex->param.grad.end = getF4( fp );
			break;

		case ID_GRPT:
			tex->param.grad.repeat = getU2( fp );
			break;

		case ID_FKEY:
			nkeys = sz / sizeof( lwGradKey );
			tex->param.grad.key = _pico_calloc( nkeys, sizeof( lwGradKey ) );
			if ( !tex->param.grad.key ) {
				return 0;
			}
			for ( i = 0; i < nkeys; i++ ) {
				tex->param.grad.key[ i ].value = getF4( fp );
				for ( j = 0; j < 4; j++ )
					tex->param.grad.key[ i ].rgba[ j ] = getF4( fp );
			}
			break;

		case ID_IKEY:
			nkeys = sz / 2;
			tex->param.grad.ikey = _pico_calloc( nkeys, sizeof( short ) );
			if ( !tex->param.grad.ikey ) {
				return 0;
			}
			for ( i = 0; i < nkeys; i++ )
				tex->param.grad.ikey[ i ] = getU2( fp );
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

		/* end of the gradient? */

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