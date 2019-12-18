#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_12__ {void* eindex; void* val; } ;
struct TYPE_11__ {void* eindex; void* val; } ;
struct TYPE_10__ {void* eindex; void* val; } ;
struct TYPE_9__ {void* eindex; void* val; } ;
struct TYPE_13__ {TYPE_4__ amplitude; TYPE_3__ stck; void* pblend; void* aa_strength; void* aas_flags; TYPE_2__ wraph; TYPE_1__ wrapw; void* wraph_type; void* wrapw_type; void* cindex; void* axis; int /*<<< orphan*/  vmap_name; void* projection; } ;
struct TYPE_14__ {TYPE_5__ imap; } ;
struct TYPE_15__ {TYPE_6__ param; int /*<<< orphan*/  tmap; } ;
typedef  TYPE_7__ lwTexture ;

/* Variables and functions */
#define  ID_AAST 139 
#define  ID_AXIS 138 
#define  ID_IMAG 137 
#define  ID_PIXB 136 
#define  ID_PROJ 135 
#define  ID_STCK 134 
#define  ID_TAMP 133 
#define  ID_TMAP 132 
#define  ID_VMAP 131 
#define  ID_WRAP 130 
#define  ID_WRPH 129 
#define  ID_WRPW 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 void* getF4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getS0 (int /*<<< orphan*/ *) ; 
 void* getU2 (int /*<<< orphan*/ *) ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 void* getVX (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  lwGetTMap (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_flen (int) ; 

int lwGetImageMap( picoMemStream_t *fp, int rsz, lwTexture *tex ){
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

		case ID_PROJ:
			tex->param.imap.projection = getU2( fp );
			break;

		case ID_VMAP:
			tex->param.imap.vmap_name = getS0( fp );
			break;

		case ID_AXIS:
			tex->param.imap.axis = getU2( fp );
			break;

		case ID_IMAG:
			tex->param.imap.cindex = getVX( fp );
			break;

		case ID_WRAP:
			tex->param.imap.wrapw_type = getU2( fp );
			tex->param.imap.wraph_type = getU2( fp );
			break;

		case ID_WRPW:
			tex->param.imap.wrapw.val = getF4( fp );
			tex->param.imap.wrapw.eindex = getVX( fp );
			break;

		case ID_WRPH:
			tex->param.imap.wraph.val = getF4( fp );
			tex->param.imap.wraph.eindex = getVX( fp );
			break;

		case ID_AAST:
			tex->param.imap.aas_flags = getU2( fp );
			tex->param.imap.aa_strength = getF4( fp );
			break;

		case ID_PIXB:
			tex->param.imap.pblend = getU2( fp );
			break;

		case ID_STCK:
			tex->param.imap.stck.val = getF4( fp );
			tex->param.imap.stck.eindex = getVX( fp );
			break;

		case ID_TAMP:
			tex->param.imap.amplitude.val = getF4( fp );
			tex->param.imap.amplitude.eindex = getVX( fp );
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

		/* end of the image map? */

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