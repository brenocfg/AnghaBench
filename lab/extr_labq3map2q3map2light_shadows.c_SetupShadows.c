#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* si; } ;
typedef  TYPE_1__ surfaceInfo_t ;
struct TYPE_9__ {int contents; } ;
typedef  TYPE_2__ shaderInfo_t ;
struct TYPE_10__ {scalar_t__ cluster; struct TYPE_10__* next; } ;
typedef  TYPE_3__ light_t ;
typedef  int /*<<< orphan*/  dsurface_t ;
struct TYPE_11__ {int numLeafSurfaces; int firstLeafSurface; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_4__ dleaf_t ;
typedef  int byte ;

/* Variables and functions */
 int CONTENTS_TRANSLUCENT ; 
 scalar_t__ ClusterVisible (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* dleafs ; 
 int* dleafsurfaces ; 
 int /*<<< orphan*/ * drawSurfaces ; 
 TYPE_3__* lights ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int numDrawSurfaces ; 
 int numleafs ; 
 scalar_t__ qfalse ; 
 int* safe_malloc (int) ; 
 TYPE_1__* surfaceInfos ; 

void SetupShadows( void ){
	int i, j, s;
	light_t         *light;
	dleaf_t         *leaf;
	dsurface_t      *ds;
	surfaceInfo_t   *info;
	shaderInfo_t    *si;
	byte            *tested;


	/* early out for weird cases where there are no lights */
	if ( lights == NULL ) {
		return;
	}

	/* note it */
	Sys_FPrintf( SYS_VRB, "--- SetupShadows ---\n" );

	/* allocate a surface test list */
	tested = safe_malloc( numDrawSurfaces / 8 + 1 );

	/* walk the list of lights */
	for ( light = lights; light != NULL; light = light->next )
	{
		/* do some early out testing */
		if ( light->cluster < 0 ) {
			continue;
		}

		/* clear surfacetest list */
		memset( tested, 0, numDrawSurfaces / 8 + 1 );

		/* walk the bsp leaves */
		for ( i = 0, leaf = dleafs; i < numleafs; i++, leaf++ )
		{
			/* in pvs? */
			if ( ClusterVisible( light->cluster, leaf->cluster ) == qfalse ) {
				continue;
			}

			/* walk the surface list for this leaf */
			for ( j = 0; j < leaf->numLeafSurfaces; j++ )
			{
				/* don't filter a surface more than once */
				s = dleafsurfaces[ leaf->firstLeafSurface + j ];
				if ( tested[ s >> 3 ] & ( 1 << ( s & 7 ) ) ) {
					continue;
				}
				tested[ s >> 3 ] |= ( 1 << ( s & 7 ) );

				/* get surface and info */
				ds = &drawSurfaces[ s ];
				info = &surfaceInfos[ s ];
				si = info->si;

				/* don't create shadow volumes from translucent surfaces */
				if ( si->contents & CONTENTS_TRANSLUCENT ) {
					continue;
				}
			}
		}
	}
}