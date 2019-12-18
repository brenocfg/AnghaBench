#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_7__ {int offset; } ;
typedef  TYPE_2__ lwTagList ;
typedef  int /*<<< orphan*/  lwSurface ;
struct TYPE_8__ {int offset; TYPE_1__* pol; } ;
typedef  TYPE_3__ lwPolygonList ;
struct TYPE_6__ {int part; int smoothgrp; int /*<<< orphan*/ * surf; } ;

/* Variables and functions */
#define  ID_PART 130 
#define  ID_SMGP 129 
#define  ID_SURF 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 int getVX (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  set_flen (int /*<<< orphan*/ ) ; 

int lwGetPolygonTags( picoMemStream_t *fp, int cksize, lwTagList *tlist,
					  lwPolygonList *plist ){
	unsigned int type;
	int rlen = 0, i, j;

	set_flen( 0 );
	type = getU4( fp );
	rlen = get_flen();
	if ( rlen < 0 ) {
		return 0;
	}

	if ( type != ID_SURF && type != ID_PART && type != ID_SMGP ) {
		_pico_memstream_seek( fp, cksize - 4, PICO_SEEK_CUR );
		return 1;
	}

	while ( rlen < cksize ) {
		i = getVX( fp ) + plist->offset;
		j = getVX( fp ) + tlist->offset;
		rlen = get_flen();
		if ( rlen < 0 || rlen > cksize ) {
			return 0;
		}

		switch ( type ) {
		case ID_SURF:  plist->pol[ i ].surf = ( lwSurface * ) ( (size_t)j );  break;
		case ID_PART:  plist->pol[ i ].part = j;  break;
		case ID_SMGP:  plist->pol[ i ].smoothgrp = j;  break;
		}
	}

	return 1;
}