#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shaderInfo_t ;
struct TYPE_5__ {int /*<<< orphan*/ * shaderInfo; scalar_t__ entityNum; } ;
typedef  TYPE_1__ mapDrawSurface_t ;

/* Variables and functions */
 TYPE_1__* AllocDrawSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SURFACE_SHADER ; 
 void* ShaderInfoForShader (char*) ; 
 TYPE_1__* mapDrawSurfs ; 
 int numMapDrawSurfs ; 

mapDrawSurface_t *DrawSurfaceForShader( char *shader ){
	int i;
	shaderInfo_t        *si;
	mapDrawSurface_t    *ds;


	/* get shader */
	si = ShaderInfoForShader( shader );

	/* find existing surface */
	for ( i = 0; i < numMapDrawSurfs; i++ )
	{
		/* get surface */
		ds = &mapDrawSurfs[ i ];

		/* check it */
		if ( ds->shaderInfo == si ) {
			return ds;
		}
	}

	/* create a new surface */
	ds = AllocDrawSurface( SURFACE_SHADER );
	ds->entityNum = 0;
	ds->shaderInfo = ShaderInfoForShader( shader );

	/* return to sender */
	return ds;
}