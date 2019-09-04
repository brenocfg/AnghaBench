#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  rbspHeader_t ;
typedef  int /*<<< orphan*/  bspHeader_t ;
typedef  int /*<<< orphan*/  bspGridPoint_t ;

/* Variables and functions */
 void* GetLump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetLumpElements (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LUMP_LIGHTARRAY ; 
 int /*<<< orphan*/  LUMP_LIGHTGRID ; 
 int /*<<< orphan*/ * bspGridPoints ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int numBSPGridPoints ; 
 int /*<<< orphan*/ * safe_malloc (int) ; 

__attribute__((used)) static void CopyLightGridLumps( rbspHeader_t *header ){
	int i;
	unsigned short  *inArray;
	bspGridPoint_t  *in, *out;


	/* get count */
	numBSPGridPoints = GetLumpElements( (bspHeader_t*) header, LUMP_LIGHTARRAY, sizeof( *inArray ) );

	/* allocate buffer */
	bspGridPoints = safe_malloc( numBSPGridPoints * sizeof( *bspGridPoints ) );
	memset( bspGridPoints, 0, numBSPGridPoints * sizeof( *bspGridPoints ) );

	/* copy */
	inArray = GetLump( (bspHeader_t*) header, LUMP_LIGHTARRAY );
	in = GetLump( (bspHeader_t*) header, LUMP_LIGHTGRID );
	out = bspGridPoints;
	for ( i = 0; i < numBSPGridPoints; i++ )
	{
		memcpy( out, &in[ *inArray ], sizeof( *in ) );
		inArray++;
		out++;
	}
}