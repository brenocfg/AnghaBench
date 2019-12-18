#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoMemStream_t ;
struct TYPE_11__ {int nlayers; int /*<<< orphan*/  nsurfs; int /*<<< orphan*/  surf; int /*<<< orphan*/  taglist; TYPE_2__* layer; } ;
typedef  TYPE_1__ lwObject ;
typedef  int /*<<< orphan*/  lwNode ;
struct TYPE_13__ {int /*<<< orphan*/  offset; } ;
struct TYPE_12__ {int /*<<< orphan*/  polygon; TYPE_3__ point; int /*<<< orphan*/  bbox; } ;
typedef  TYPE_2__ lwLayer ;

/* Variables and functions */
 unsigned int ID_FORM ; 
 unsigned int ID_LWOB ; 
#define  ID_PNTS 131 
#define  ID_POLS 130 
#define  ID_SRFS 129 
#define  ID_SURF 128 
 int /*<<< orphan*/  PICO_SEEK_CUR ; 
 void* _pico_calloc (int,int) ; 
 int /*<<< orphan*/  _pico_memstream_seek (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int _pico_memstream_tell (int /*<<< orphan*/ *) ; 
 unsigned int getU4 (int /*<<< orphan*/ *) ; 
 int get_flen () ; 
 int /*<<< orphan*/  lwFreeObject (TYPE_1__*) ; 
 int /*<<< orphan*/  lwGetBoundingBox (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwGetPointPolygons (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwGetPoints (int /*<<< orphan*/ *,unsigned int,TYPE_3__*) ; 
 int /*<<< orphan*/  lwGetPolyNormals (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwGetPolygons5 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lwGetSurface5 (int /*<<< orphan*/ *,unsigned int,TYPE_1__*) ; 
 int /*<<< orphan*/  lwGetTags (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwGetVertNormals (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwListAdd (void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwResolvePolySurfaces (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_flen (int /*<<< orphan*/ ) ; 

lwObject *lwGetObject5( char *filename, picoMemStream_t *fp, unsigned int *failID, int *failpos ){
	lwObject *object;
	lwLayer *layer;
	lwNode *node;
	unsigned int id, formsize, type, cksize;


	/* open the file */

	if ( !fp ) {
		return NULL;
	}

	/* read the first 12 bytes */

	set_flen( 0 );
	id       = getU4( fp );
	formsize = getU4( fp );
	type     = getU4( fp );
	if ( 12 != get_flen() ) {
		return NULL;
	}

	/* LWOB? */

	if ( id != ID_FORM || type != ID_LWOB ) {
		if ( failpos ) {
			*failpos = 12;
		}
		return NULL;
	}

	/* allocate an object and a default layer */

	object = _pico_calloc( 1, sizeof( lwObject ) );
	if ( !object ) {
		goto Fail;
	}

	layer = _pico_calloc( 1, sizeof( lwLayer ) );
	if ( !layer ) {
		goto Fail;
	}
	object->layer = layer;
	object->nlayers = 1;

	/* get the first chunk header */

	id = getU4( fp );
	cksize = getU4( fp );
	if ( 0 > get_flen() ) {
		goto Fail;
	}

	/* process chunks as they're encountered */

	while ( 1 ) {
		cksize += cksize & 1;

		switch ( id )
		{
		case ID_PNTS:
			if ( !lwGetPoints( fp, cksize, &layer->point ) ) {
				goto Fail;
			}
			break;

		case ID_POLS:
			if ( !lwGetPolygons5( fp, cksize, &layer->polygon,
								  layer->point.offset ) ) {
				goto Fail;
			}
			break;

		case ID_SRFS:
			if ( !lwGetTags( fp, cksize, &object->taglist ) ) {
				goto Fail;
			}
			break;

		case ID_SURF:
			node = ( lwNode * ) lwGetSurface5( fp, cksize, object );
			if ( !node ) {
				goto Fail;
			}
			lwListAdd( (void **) &object->surf, node );
			object->nsurfs++;
			break;

		default:
			_pico_memstream_seek( fp, cksize, PICO_SEEK_CUR );
			break;
		}

		/* end of the file? */

		if ( formsize <= _pico_memstream_tell( fp ) - 8 ) {
			break;
		}

		/* get the next chunk header */

		set_flen( 0 );
		id = getU4( fp );
		cksize = getU4( fp );
		if ( 8 != get_flen() ) {
			goto Fail;
		}
	}

	lwGetBoundingBox( &layer->point, layer->bbox );
	lwGetPolyNormals( &layer->point, &layer->polygon );
	if ( !lwGetPointPolygons( &layer->point, &layer->polygon ) ) {
		goto Fail;
	}
	if ( !lwResolvePolySurfaces( &layer->polygon, &object->taglist,
								 &object->surf, &object->nsurfs ) ) {
		goto Fail;
	}
	lwGetVertNormals( &layer->point, &layer->polygon );

	return object;

Fail:
	if ( failID ) {
		*failID = id;
	}
	if ( fp ) {
		if ( failpos ) {
			*failpos = _pico_memstream_tell( fp );
		}
	}
	lwFreeObject( object );
	return NULL;
}