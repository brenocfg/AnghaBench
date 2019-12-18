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
 double LUXEL_COLOR_FRAC ; 
 double LUXEL_TOLERANCE ; 
 double SOLID_EPSILON ; 
 double fabs (float) ; 
 scalar_t__* minLight ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean CompareBSPLuxels( rawLightmap_t *a, int aNum, rawLightmap_t *b, int bNum ){
	rawLightmap_t   *lm;
	int x, y;
	double delta, total, rd, gd, bd;
	float           *aLuxel, *bLuxel;


	/* styled lightmaps will never be collapsed to non-styled lightmaps when there is _minlight */
	if ( ( minLight[ 0 ] || minLight[ 1 ] || minLight[ 2 ] ) &&
		 ( ( aNum == 0 && bNum != 0 ) || ( aNum != 0 && bNum == 0 ) ) ) {
		return qfalse;
	}

	/* basic tests */
	if ( a->customWidth != b->customWidth || a->customHeight != b->customHeight ||
		 a->brightness != b->brightness ||
		 a->solid[ aNum ] != b->solid[ bNum ] ||
		 a->bspLuxels[ aNum ] == NULL || b->bspLuxels[ bNum ] == NULL ) {
		return qfalse;
	}

	/* compare solid color lightmaps */
	if ( a->solid[ aNum ] && b->solid[ bNum ] ) {
		/* get deltas */
		rd = fabs( a->solidColor[ aNum ][ 0 ] - b->solidColor[ bNum ][ 0 ] );
		gd = fabs( a->solidColor[ aNum ][ 1 ] - b->solidColor[ bNum ][ 1 ] );
		bd = fabs( a->solidColor[ aNum ][ 2 ] - b->solidColor[ bNum ][ 2 ] );

		/* compare color */
		if ( rd > SOLID_EPSILON || gd > SOLID_EPSILON || bd > SOLID_EPSILON ) {
			return qfalse;
		}

		/* okay */
		return qtrue;
	}

	/* compare nonsolid lightmaps */
	if ( a->w != b->w || a->h != b->h ) {
		return qfalse;
	}

	/* compare luxels */
	delta = 0.0;
	total = 0.0;
	for ( y = 0; y < a->h; y++ )
	{
		for ( x = 0; x < a->w; x++ )
		{
			/* increment total */
			total += 1.0;

			/* get luxels */
			lm = a; aLuxel = BSP_LUXEL( aNum, x, y );
			lm = b; bLuxel = BSP_LUXEL( bNum, x, y );

			/* ignore unused luxels */
			if ( aLuxel[ 0 ] < 0 || bLuxel[ 0 ] < 0 ) {
				continue;
			}

			/* get deltas */
			rd = fabs( aLuxel[ 0 ] - bLuxel[ 0 ] );
			gd = fabs( aLuxel[ 1 ] - bLuxel[ 1 ] );
			bd = fabs( aLuxel[ 2 ] - bLuxel[ 2 ] );

			/* 2003-09-27: compare individual luxels */
			if ( rd > 3.0 || gd > 3.0 || bd > 3.0 ) {
				return qfalse;
			}

			/* compare (fixme: take into account perceptual differences) */
			delta += rd * LUXEL_COLOR_FRAC;
			delta += gd * LUXEL_COLOR_FRAC;
			delta += bd * LUXEL_COLOR_FRAC;

			/* is the change too high? */
			if ( total > 0.0 && ( ( delta / total ) > LUXEL_TOLERANCE ) ) {
				return qfalse;
			}
		}
	}

	/* made it this far, they must be identical (or close enough) */
	return qtrue;
}