#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_15__ {float val; } ;
struct TYPE_13__ {float* val; } ;
struct TYPE_14__ {TYPE_1__ size; } ;
struct TYPE_16__ {unsigned int type; int enabled; TYPE_3__ opacity; TYPE_2__ tmap; } ;
typedef  TYPE_4__ lwTexture ;

/* Variables and functions */
#define  ID_GRAD 130 
#define  ID_IMAP 129 
#define  ID_PROC 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 TYPE_4__* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  _pico_free (TYPE_4__*) ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 unsigned short getU2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwFreeTexture (TYPE_4__*) ; 
 int lwGetGradient (int /*<<< orphan*/ *,unsigned short,TYPE_4__*) ; 
 int lwGetImageMap (int /*<<< orphan*/ *,unsigned short,TYPE_4__*) ; 
 int lwGetProcedural (int /*<<< orphan*/ *,unsigned short,TYPE_4__*) ; 
 int /*<<< orphan*/  lwGetTHeader (int /*<<< orphan*/ *,unsigned short,TYPE_4__*) ; 
 int /*<<< orphan*/  set_flen (int) ; 

lwTexture *lwGetTexture( picoMemStream_t *fp, int bloksz, unsigned int type ){
	lwTexture *tex;
	unsigned short sz;
	int ok;

	tex = _pico_calloc( 1, sizeof( lwTexture ) );
	if ( !tex ) {
		return NULL;
	}

	tex->type = type;
	tex->tmap.size.val[ 0 ] =
		tex->tmap.size.val[ 1 ] =
			tex->tmap.size.val[ 2 ] = 1.0f;
	tex->opacity.val = 1.0f;
	tex->enabled = 1;

	sz = getU2( fp );
	if ( !lwGetTHeader( fp, sz, tex ) ) {
		_pico_free( tex );
		return NULL;
	}

	sz = bloksz - sz - 6;
	switch ( type ) {
	case ID_IMAP:  ok = lwGetImageMap( fp, sz, tex );  break;
	case ID_PROC:  ok = lwGetProcedural( fp, sz, tex );  break;
	case ID_GRAD:  ok = lwGetGradient( fp, sz, tex );  break;
	default:
		ok = !_pico_memstream_seek( fp, sz, PICO_SEEK_CUR );
	}

	if ( !ok ) {
		lwFreeTexture( tex );
		return NULL;
	}

	set_flen( bloksz );
	return tex;
}