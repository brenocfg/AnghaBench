#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ibspHeader_t ;
struct TYPE_8__ {int /*<<< orphan*/ * color; int /*<<< orphan*/  normal; int /*<<< orphan*/ * lightmap; int /*<<< orphan*/ * st; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_1__ ibspDrawVert_t ;
typedef  int /*<<< orphan*/  bspHeader_t ;
struct TYPE_9__ {int /*<<< orphan*/ ** color; int /*<<< orphan*/  normal; int /*<<< orphan*/ ** lightmap; int /*<<< orphan*/ * st; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ bspDrawVert_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AddLump (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  LUMP_DRAWVERTS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* bspDrawVerts ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int numBSPDrawVerts ; 
 TYPE_1__* safe_malloc (int) ; 

__attribute__((used)) static void AddDrawVertsLump( FILE *file, ibspHeader_t *header ){
	int i, size;
	bspDrawVert_t   *in;
	ibspDrawVert_t  *buffer, *out;


	/* allocate output buffer */
	size = numBSPDrawVerts * sizeof( *buffer );
	buffer = safe_malloc( size );
	memset( buffer, 0, size );

	/* convert */
	in = bspDrawVerts;
	out = buffer;
	for ( i = 0; i < numBSPDrawVerts; i++ )
	{
		VectorCopy( in->xyz, out->xyz );
		out->st[ 0 ] = in->st[ 0 ];
		out->st[ 1 ] = in->st[ 1 ];

		out->lightmap[ 0 ] = in->lightmap[ 0 ][ 0 ];
		out->lightmap[ 1 ] = in->lightmap[ 0 ][ 1 ];

		VectorCopy( in->normal, out->normal );

		out->color[ 0 ] = in->color[ 0 ][ 0 ];
		out->color[ 1 ] = in->color[ 0 ][ 1 ];
		out->color[ 2 ] = in->color[ 0 ][ 2 ];
		out->color[ 3 ] = in->color[ 0 ][ 3 ];

		in++;
		out++;
	}

	/* write lump */
	AddLump( file, (bspHeader_t*) header, LUMP_DRAWVERTS, buffer, size );

	/* free buffer */
	free( buffer );
}