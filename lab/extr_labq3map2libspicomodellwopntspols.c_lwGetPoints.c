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
struct TYPE_4__ {int offset; int count; TYPE_2__* pt; } ;
typedef  TYPE_1__ lwPointList ;
typedef  int /*<<< orphan*/  lwPoint ;
struct TYPE_5__ {float* pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (float*) ; 
 int /*<<< orphan*/  _pico_realloc (void*,int,int) ; 
 scalar_t__ getbytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  revbytes (float*,int,int) ; 

int lwGetPoints( picoMemStream_t *fp, int cksize, lwPointList *point ){
	float *f;
	int np, i, j;

	if ( cksize == 1 ) {
		return 1;
	}

	/* extend the point array to hold the new points */

	np = cksize / 12;
	point->offset = point->count;
	point->count += np;
	if ( !_pico_realloc( (void *) &point->pt, ( point->count - np ) * sizeof( lwPoint ), point->count * sizeof( lwPoint ) ) ) {
		return 0;
	}
	memset( &point->pt[ point->offset ], 0, np * sizeof( lwPoint ) );

	/* read the whole chunk */

	f = ( float * ) getbytes( fp, cksize );
	if ( !f ) {
		return 0;
	}
	revbytes( f, 4, np * 3 );

	/* assign position values */

	for ( i = 0, j = 0; i < np; i++, j += 3 ) {
		point->pt[ i ].pos[ 0 ] = f[ j ];
		point->pt[ i ].pos[ 1 ] = f[ j + 1 ];
		point->pt[ i ].pos[ 2 ] = f[ j + 2 ];
	}

	_pico_free( f );
	return 1;
}