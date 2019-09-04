#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_4__ {int /*<<< orphan*/  eindex; int /*<<< orphan*/  val; } ;
struct TYPE_5__ {void* axis; void* negative; void* enabled; TYPE_1__ opacity; void* opac_type; void* chan; int /*<<< orphan*/  ord; } ;
typedef  TYPE_2__ lwTexture ;

/* Variables and functions */
#define  ID_AXIS 132 
#define  ID_CHAN 131 
#define  ID_ENAB 130 
#define  ID_NEGA 129 
#define  ID_OPAC 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getF4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getS0 (int /*<<< orphan*/ *) ; 
 void* getU2 (int /*<<< orphan*/ *) ; 
 void* getU4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getVX (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  set_flen (int) ; 

int lwGetTHeader( picoMemStream_t *fp, int hsz, lwTexture *tex ){
	unsigned int id;
	unsigned short sz;
	int pos, rlen;


	/* remember where we started */

	set_flen( 0 );
	pos = _pico_memstream_tell( fp );

	/* ordinal string */

	tex->ord = getS0( fp );

	/* first subchunk header */

	id = getU4( fp );
	sz = getU2( fp );
	if ( 0 > get_flen() ) {
		return 0;
	}

	/* process subchunks as they're encountered */

	while ( 1 ) {
		sz += sz & 1;
		set_flen( 0 );

		switch ( id ) {
		case ID_CHAN:
			tex->chan = getU4( fp );
			break;

		case ID_OPAC:
			tex->opac_type = getU2( fp );
			tex->opacity.val = getF4( fp );
			tex->opacity.eindex = getVX( fp );
			break;

		case ID_ENAB:
			tex->enabled = getU2( fp );
			break;

		case ID_NEGA:
			tex->negative = getU2( fp );
			break;

		case ID_AXIS:
			tex->axis = getU2( fp );
			break;

		default:
			break;
		}

		/* error while reading current subchunk? */

		rlen = get_flen();
		if ( rlen < 0 || rlen > sz ) {
			return 0;
		}

		/* skip unread parts of the current subchunk */

		if ( rlen < sz ) {
			_pico_memstream_seek( fp, sz - rlen, PICO_SEEK_CUR );
		}

		/* end of the texture header subchunk? */

		if ( hsz <= _pico_memstream_tell( fp ) - pos ) {
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