#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
typedef  int /*<<< orphan*/  lwSurface ;
struct TYPE_7__ {int offset; int voffset; TYPE_2__* pol; } ;
typedef  TYPE_1__ lwPolygonList ;
struct TYPE_8__ {int nverts; int /*<<< orphan*/ * surf; TYPE_3__* v; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ lwPolygon ;
struct TYPE_9__ {int index; } ;
typedef  TYPE_3__ lwPolVert ;

/* Variables and functions */
 int /*<<< orphan*/  ID_FACE ; 
 int /*<<< orphan*/  _pico_free (unsigned char*) ; 
 unsigned char* getbytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lwAllocPolygons (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  lwFreePolygons (TYPE_1__*) ; 
 int /*<<< orphan*/  set_flen (int /*<<< orphan*/ ) ; 
 int sgetI2 (unsigned char**) ; 
 int sgetU2 (unsigned char**) ; 

int lwGetPolygons5( picoMemStream_t *fp, int cksize, lwPolygonList *plist, int ptoffset ){
	lwPolygon *pp;
	lwPolVert *pv;
	unsigned char *buf, *bp;
	int i, j, nv, nverts, npols;


	if ( cksize == 0 ) {
		return 1;
	}

	/* read the whole chunk */

	set_flen( 0 );
	buf = getbytes( fp, cksize );
	if ( !buf ) {
		goto Fail;
	}

	/* count the polygons and vertices */

	nverts = 0;
	npols = 0;
	bp = buf;

	while ( bp < buf + cksize ) {
		nv = sgetU2( &bp );
		nverts += nv;
		npols++;
		bp += 2 * nv;
		i = sgetI2( &bp );
		if ( i < 0 ) {
			bp += 2;             /* detail polygons */
		}
	}

	if ( !lwAllocPolygons( plist, npols, nverts ) ) {
		goto Fail;
	}

	/* fill in the new polygons */

	bp = buf;
	pp = plist->pol + plist->offset;
	pv = plist->pol[ 0 ].v + plist->voffset;

	for ( i = 0; i < npols; i++ ) {
		nv = sgetU2( &bp );

		pp->nverts = nv;
		pp->type = ID_FACE;
		if ( !pp->v ) {
			pp->v = pv;
		}
		for ( j = 0; j < nv; j++ )
			pv[ j ].index = sgetU2( &bp ) + ptoffset;
		j = sgetI2( &bp );
		if ( j < 0 ) {
			j = -j;
			bp += 2;
		}
		j -= 1;
		pp->surf = ( lwSurface * ) ( (size_t)j );

		pp++;
		pv += nv;
	}

	_pico_free( buf );
	return 1;

Fail:
	if ( buf ) {
		_pico_free( buf );
	}
	lwFreePolygons( plist );
	return 0;
}