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
struct TYPE_4__ {scalar_t__ customWidth; scalar_t__ customHeight; scalar_t__ brightness; scalar_t__* solid; float** solidColor; int w; int h; int /*<<< orphan*/ ** bspLuxels; } ;
typedef  TYPE_1__ rawLightmap_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 float* BSP_LUXEL (int,int,int) ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean MergeBSPLuxels( rawLightmap_t *a, int aNum, rawLightmap_t *b, int bNum ){
	rawLightmap_t   *lm;
	int x, y;
	float luxel[ 3 ], *aLuxel, *bLuxel;


	/* basic tests */
	if ( a->customWidth != b->customWidth || a->customHeight != b->customHeight ||
		 a->brightness != b->brightness ||
		 a->solid[ aNum ] != b->solid[ bNum ] ||
		 a->bspLuxels[ aNum ] == NULL || b->bspLuxels[ bNum ] == NULL ) {
		return qfalse;
	}

	/* compare solid lightmaps */
	if ( a->solid[ aNum ] && b->solid[ bNum ] ) {
		/* average */
		VectorAdd( a->solidColor[ aNum ], b->solidColor[ bNum ], luxel );
		VectorScale( luxel, 0.5f, luxel );

		/* copy to both */
		VectorCopy( luxel, a->solidColor[ aNum ] );
		VectorCopy( luxel, b->solidColor[ bNum ] );

		/* return to sender */
		return qtrue;
	}

	/* compare nonsolid lightmaps */
	if ( a->w != b->w || a->h != b->h ) {
		return qfalse;
	}

	/* merge luxels */
	for ( y = 0; y < a->h; y++ )
	{
		for ( x = 0; x < a->w; x++ )
		{
			/* get luxels */
			lm = a; aLuxel = BSP_LUXEL( aNum, x, y );
			lm = b; bLuxel = BSP_LUXEL( bNum, x, y );

			/* handle occlusion mismatch */
			if ( aLuxel[ 0 ] < 0.0f ) {
				VectorCopy( bLuxel, aLuxel );
			}
			else if ( bLuxel[ 0 ] < 0.0f ) {
				VectorCopy( aLuxel, bLuxel );
			}
			else
			{
				/* average */
				VectorAdd( aLuxel, bLuxel, luxel );
				VectorScale( luxel, 0.5f, luxel );

				/* debugging code */
				//%	luxel[ 2 ] += 64.0f;

				/* copy to both */
				VectorCopy( luxel, aLuxel );
				VectorCopy( luxel, bLuxel );
			}
		}
	}

	/* done */
	return qtrue;
}