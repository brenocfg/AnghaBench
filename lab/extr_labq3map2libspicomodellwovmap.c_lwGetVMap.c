#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_4__ {int perpoly; int dim; int nverts; float** val; void** pindex; void** vindex; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ lwVMap ;

/* Variables and functions */
 float* _pico_alloc (int) ; 
 void* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  _pico_free (unsigned char*) ; 
 int get_flen () ; 
 unsigned char* getbytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lwFreeVMap (TYPE_1__*) ; 
 int /*<<< orphan*/  set_flen (int /*<<< orphan*/ ) ; 
 float sgetF4 (unsigned char**) ; 
 int /*<<< orphan*/  sgetS0 (unsigned char**) ; 
 int sgetU2 (unsigned char**) ; 
 int /*<<< orphan*/  sgetU4 (unsigned char**) ; 
 void* sgetVX (unsigned char**) ; 

lwVMap *lwGetVMap( picoMemStream_t *fp, int cksize, int ptoffset, int poloffset,
				   int perpoly ){
	unsigned char *buf, *bp;
	lwVMap *vmap;
	float *f;
	int i, j, npts, rlen;


	/* read the whole chunk */

	set_flen( 0 );
	buf = getbytes( fp, cksize );
	if ( !buf ) {
		return NULL;
	}

	vmap = _pico_calloc( 1, sizeof( lwVMap ) );
	if ( !vmap ) {
		_pico_free( buf );
		return NULL;
	}

	/* initialize the vmap */

	vmap->perpoly = perpoly;

	bp = buf;
	set_flen( 0 );
	vmap->type = sgetU4( &bp );
	vmap->dim  = sgetU2( &bp );
	vmap->name = sgetS0( &bp );
	rlen = get_flen();

	/* count the vmap records */

	npts = 0;
	while ( bp < buf + cksize ) {
		i = sgetVX( &bp );
		if ( perpoly ) {
			i = sgetVX( &bp );
		}
		bp += vmap->dim * sizeof( float );
		++npts;
	}

	/* allocate the vmap */

	vmap->nverts = npts;
	vmap->vindex = _pico_calloc( npts, sizeof( int ) );
	if ( !vmap->vindex ) {
		goto Fail;
	}
	if ( perpoly ) {
		vmap->pindex = _pico_calloc( npts, sizeof( int ) );
		if ( !vmap->pindex ) {
			goto Fail;
		}
	}

	if ( vmap->dim > 0 ) {
		vmap->val = _pico_calloc( npts, sizeof( float * ) );
		if ( !vmap->val ) {
			goto Fail;
		}
		f = _pico_alloc( npts * vmap->dim * sizeof( float ) );
		if ( !f ) {
			goto Fail;
		}
		for ( i = 0; i < npts; i++ )
			vmap->val[ i ] = f + i * vmap->dim;
	}

	/* fill in the vmap values */

	bp = buf + rlen;
	for ( i = 0; i < npts; i++ ) {
		vmap->vindex[ i ] = sgetVX( &bp );
		if ( perpoly ) {
			vmap->pindex[ i ] = sgetVX( &bp );
		}
		for ( j = 0; j < vmap->dim; j++ )
			vmap->val[ i ][ j ] = sgetF4( &bp );
	}

	_pico_free( buf );
	return vmap;

Fail:
	if ( buf ) {
		_pico_free( buf );
	}
	lwFreeVMap( vmap );
	return NULL;
}