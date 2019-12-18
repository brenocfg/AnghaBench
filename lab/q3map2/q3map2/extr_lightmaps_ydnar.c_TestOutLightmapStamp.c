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
struct TYPE_5__ {int w; int h; scalar_t__* solid; } ;
typedef  TYPE_1__ rawLightmap_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int customWidth; int customHeight; int* lightBits; } ;
typedef  TYPE_2__ outLightmap_t ;

/* Variables and functions */
 float* BSP_LUXEL (int,int,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean TestOutLightmapStamp( rawLightmap_t *lm, int lightmapNum, outLightmap_t *olm, int x, int y ){
	int sx, sy, ox, oy, offset;
	float       *luxel;


	/* bounds check */
	if ( x < 0 || y < 0 || ( x + lm->w ) > olm->customWidth || ( y + lm->h ) > olm->customHeight ) {
		return qfalse;
	}

	/* solid lightmaps test a 1x1 stamp */
	if ( lm->solid[ lightmapNum ] ) {
		offset = ( y * olm->customWidth ) + x;
		if ( olm->lightBits[ offset >> 3 ] & ( 1 << ( offset & 7 ) ) ) {
			return qfalse;
		}
		return qtrue;
	}

	/* test the stamp */
	for ( sy = 0; sy < lm->h; sy++ )
	{
		for ( sx = 0; sx < lm->w; sx++ )
		{
			/* get luxel */
			luxel = BSP_LUXEL( lightmapNum, sx, sy );
			if ( luxel[ 0 ] < 0.0f ) {
				continue;
			}

			/* get bsp lightmap coords and test */
			ox = x + sx;
			oy = y + sy;
			offset = ( oy * olm->customWidth ) + ox;
			if ( olm->lightBits[ offset >> 3 ] & ( 1 << ( offset & 7 ) ) ) {
				return qfalse;
			}
		}
	}

	/* stamp is empty */
	return qtrue;
}