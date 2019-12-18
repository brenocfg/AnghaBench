#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_10__ {void* eindex; void** val; } ;
struct TYPE_9__ {void* eindex; void** val; } ;
struct TYPE_8__ {void* eindex; void** val; } ;
struct TYPE_7__ {void* eindex; void** val; } ;
struct TYPE_11__ {void* coord_sys; int /*<<< orphan*/  ref_object; TYPE_4__ falloff; void* fall_type; TYPE_3__ rotate; TYPE_2__ center; TYPE_1__ size; } ;
typedef  TYPE_5__ lwTMap ;

/* Variables and functions */
#define  ID_CNTR 133 
#define  ID_CSYS 132 
#define  ID_FALL 131 
#define  ID_OREF 130 
#define  ID_ROTA 129 
#define  ID_SIZE 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 void* getF4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getS0 (int /*<<< orphan*/ *) ; 
 void* getU2 (int /*<<< orphan*/ *) ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 void* getVX (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  set_flen (int) ; 

int lwGetTMap( picoMemStream_t *fp, int tmapsz, lwTMap *tmap ){
	unsigned int id;
	unsigned short sz;
	int rlen, pos, i;

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
		case ID_SIZE:
			for ( i = 0; i < 3; i++ )
				tmap->size.val[ i ] = getF4( fp );
			tmap->size.eindex = getVX( fp );
			break;

		case ID_CNTR:
			for ( i = 0; i < 3; i++ )
				tmap->center.val[ i ] = getF4( fp );
			tmap->center.eindex = getVX( fp );
			break;

		case ID_ROTA:
			for ( i = 0; i < 3; i++ )
				tmap->rotate.val[ i ] = getF4( fp );
			tmap->rotate.eindex = getVX( fp );
			break;

		case ID_FALL:
			tmap->fall_type = getU2( fp );
			for ( i = 0; i < 3; i++ )
				tmap->falloff.val[ i ] = getF4( fp );
			tmap->falloff.eindex = getVX( fp );
			break;

		case ID_OREF:
			tmap->ref_object = getS0( fp );
			break;

		case ID_CSYS:
			tmap->coord_sys = getU2( fp );
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

		/* end of the TMAP subchunk? */

		if ( tmapsz <= _pico_memstream_tell( fp ) - pos ) {
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