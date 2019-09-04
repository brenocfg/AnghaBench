#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* si; int /*<<< orphan*/ * lm; } ;
typedef  TYPE_1__ surfaceInfo_t ;
struct TYPE_10__ {float bounceScale; int compileFlags; float lightSubdivide; scalar_t__ autosprite; } ;
typedef  TYPE_2__ shaderInfo_t ;
typedef  int /*<<< orphan*/  rawLightmap_t ;
typedef  int /*<<< orphan*/  clipWork_t ;
struct TYPE_11__ {size_t shaderNum; scalar_t__* lightmapStyles; int surfaceType; } ;
typedef  TYPE_3__ bspDrawSurface_t ;
struct TYPE_12__ {int contentFlags; int surfaceFlags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ApplySurfaceParm (char*,int*,int*,int*) ; 
 int C_SKY ; 
 scalar_t__ LS_NONE ; 
 scalar_t__ LS_UNUSED ; 
 int MAX_LIGHTMAPS ; 
#define  MST_PATCH 130 
#define  MST_PLANAR 129 
#define  MST_TRIANGLE_SOUP 128 
 int /*<<< orphan*/  RadLightForPatch (int,int,int /*<<< orphan*/ *,TYPE_2__*,float,float,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RadLightForTriangles (int,int,int /*<<< orphan*/ *,TYPE_2__*,float,float,int /*<<< orphan*/ *) ; 
 TYPE_3__* bspDrawSurfaces ; 
 TYPE_5__* bspShaders ; 
 float diffuseSubdivide ; 
 int /*<<< orphan*/  master_mutex ; 
 int /*<<< orphan*/  numDiffuseSurfaces ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* surfaceInfos ; 

void RadLight( int num ){
	int lightmapNum;
	float scale, subdivide;
	int contentFlags, surfaceFlags, compileFlags;
	bspDrawSurface_t    *ds;
	surfaceInfo_t       *info;
	rawLightmap_t       *lm;
	shaderInfo_t        *si;
	clipWork_t cw;


	/* get drawsurface, lightmap, and shader info */
	ds = &bspDrawSurfaces[ num ];
	info = &surfaceInfos[ num ];
	lm = info->lm;
	si = info->si;
	scale = si->bounceScale;

	/* find nodraw bit */
	contentFlags = surfaceFlags = compileFlags = 0;
	ApplySurfaceParm( "nodraw", &contentFlags, &surfaceFlags, &compileFlags );

	/* early outs? */
	if ( scale <= 0.0f || ( si->compileFlags & C_SKY ) || si->autosprite ||
		 ( bspShaders[ ds->shaderNum ].contentFlags & contentFlags ) || ( bspShaders[ ds->shaderNum ].surfaceFlags & surfaceFlags ) ||
		 ( si->compileFlags & compileFlags ) ) {
		return;
	}

	/* determine how much we need to chop up the surface */
	if ( si->lightSubdivide ) {
		subdivide = si->lightSubdivide;
	}
	else{
		subdivide = diffuseSubdivide;
	}

	/* inc counts */
	pthread_mutex_lock( &master_mutex );
	numDiffuseSurfaces++;
	pthread_mutex_unlock( &master_mutex );

	/* iterate through styles (this could be more efficient, yes) */
	for ( lightmapNum = 0; lightmapNum < MAX_LIGHTMAPS; lightmapNum++ )
	{
		/* switch on type */
		if ( ds->lightmapStyles[ lightmapNum ] != LS_NONE && ds->lightmapStyles[ lightmapNum ] != LS_UNUSED ) {
			switch ( ds->surfaceType )
			{
			case MST_PLANAR:
			case MST_TRIANGLE_SOUP:
				RadLightForTriangles( num, lightmapNum, lm, si, scale, subdivide, &cw );
				break;

			case MST_PATCH:
				RadLightForPatch( num, lightmapNum, lm, si, scale, subdivide, &cw );
				break;

			default:
				break;
			}
		}
	}
}