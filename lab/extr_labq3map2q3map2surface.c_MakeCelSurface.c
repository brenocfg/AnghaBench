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
typedef  int /*<<< orphan*/  shaderInfo_t ;
struct TYPE_8__ {int planeNum; int /*<<< orphan*/  planar; TYPE_1__* shaderInfo; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_7__ {int compileFlags; } ;

/* Variables and functions */
 int C_SKY ; 
 int C_TRANSLUCENT ; 
 TYPE_2__* CloneSurface (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfalse ; 

mapDrawSurface_t *MakeCelSurface( mapDrawSurface_t *src, shaderInfo_t *si ){
	mapDrawSurface_t    *ds;


	/* dummy check */
	if ( src == NULL || si == NULL ) {
		return NULL;
	}

	/* don't create cel surfaces for certain types of shaders */
	if ( ( src->shaderInfo->compileFlags & C_TRANSLUCENT ) ||
		 ( src->shaderInfo->compileFlags & C_SKY ) ) {
		return NULL;
	}

	/* make a copy */
	ds = CloneSurface( src, si );
	if ( ds == NULL ) {
		return NULL;
	}

	/* do some fixups for celshading */
	ds->planar = qfalse;
	ds->planeNum = -1;

	/* return the surface */
	return ds;
}