#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ibspHeader_t ;
struct TYPE_7__ {int /*<<< orphan*/ * latLong; int /*<<< orphan*/  directed; int /*<<< orphan*/  ambient; } ;
typedef  TYPE_1__ ibspGridPoint_t ;
typedef  int /*<<< orphan*/  bspHeader_t ;
struct TYPE_8__ {int /*<<< orphan*/ * latLong; int /*<<< orphan*/ * styles; int /*<<< orphan*/ * directed; int /*<<< orphan*/ * ambient; } ;
typedef  TYPE_2__ bspGridPoint_t ;

/* Variables and functions */
 TYPE_1__* GetLump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLumpElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LS_NONE ; 
 int /*<<< orphan*/  LS_NORMAL ; 
 int /*<<< orphan*/  LUMP_LIGHTGRID ; 
 int MAX_LIGHTMAPS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* bspGridPoints ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int numBSPGridPoints ; 
 TYPE_2__* safe_malloc (int) ; 

__attribute__((used)) static void CopyLightGridLumps( ibspHeader_t *header ){
	int i, j;
	ibspGridPoint_t *in;
	bspGridPoint_t  *out;


	/* get count */
	numBSPGridPoints = GetLumpElements( (bspHeader_t*) header, LUMP_LIGHTGRID, sizeof( *in ) );

	/* allocate buffer */
	bspGridPoints = safe_malloc( numBSPGridPoints * sizeof( *bspGridPoints ) );
	memset( bspGridPoints, 0, numBSPGridPoints * sizeof( *bspGridPoints ) );

	/* copy */
	in = GetLump( (bspHeader_t*) header, LUMP_LIGHTGRID );
	out = bspGridPoints;
	for ( i = 0; i < numBSPGridPoints; i++ )
	{
		for ( j = 0; j < MAX_LIGHTMAPS; j++ )
		{
			VectorCopy( in->ambient, out->ambient[ j ] );
			VectorCopy( in->directed, out->directed[ j ] );
			out->styles[ j ] = LS_NONE;
		}

		out->styles[ 0 ] = LS_NORMAL;

		out->latLong[ 0 ] = in->latLong[ 0 ];
		out->latLong[ 1 ] = in->latLong[ 1 ];

		in++;
		out++;
	}
}