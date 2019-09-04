#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ibspHeader_t ;
struct TYPE_5__ {int /*<<< orphan*/ * color; int /*<<< orphan*/  normal; int /*<<< orphan*/ * lightmap; int /*<<< orphan*/ * st; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_1__ ibspDrawVert_t ;
typedef  int /*<<< orphan*/  bspHeader_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** color; int /*<<< orphan*/  normal; int /*<<< orphan*/ ** lightmap; int /*<<< orphan*/ * st; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_2__ bspDrawVert_t ;

/* Variables and functions */
 TYPE_1__* GetLump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLumpElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LUMP_DRAWVERTS ; 
 int /*<<< orphan*/  SetDrawVerts (int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* bspDrawVerts ; 
 int numBSPDrawVerts ; 

__attribute__((used)) static void CopyDrawVertsLump( ibspHeader_t *header ){
	int i;
	ibspDrawVert_t  *in;
	bspDrawVert_t   *out;


	/* get count */
	numBSPDrawVerts = GetLumpElements( (bspHeader_t*) header, LUMP_DRAWVERTS, sizeof( *in ) );
	SetDrawVerts( numBSPDrawVerts );

	/* copy */
	in = GetLump( (bspHeader_t*) header, LUMP_DRAWVERTS );
	out = bspDrawVerts;
	for ( i = 0; i < numBSPDrawVerts; i++ )
	{
		VectorCopy( in->xyz, out->xyz );
		out->st[ 0 ] = in->st[ 0 ];
		out->st[ 1 ] = in->st[ 1 ];

		out->lightmap[ 0 ][ 0 ] = in->lightmap[ 0 ];
		out->lightmap[ 0 ][ 1 ] = in->lightmap[ 1 ];

		VectorCopy( in->normal, out->normal );

		out->color[ 0 ][ 0 ] = in->color[ 0 ];
		out->color[ 0 ][ 1 ] = in->color[ 1 ];
		out->color[ 0 ][ 2 ] = in->color[ 2 ];
		out->color[ 0 ][ 3 ] = in->color[ 3 ];

		in++;
		out++;
	}
}