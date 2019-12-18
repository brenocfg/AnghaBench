#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int parentSurfaceNum; int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/  longestCurve; int /*<<< orphan*/  sampleSize; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  entityNum; int /*<<< orphan*/  si; TYPE_3__* mds; } ;
typedef  TYPE_2__ surfaceExtra_t ;
struct TYPE_8__ {int /*<<< orphan*/  lightmapAxis; int /*<<< orphan*/  longestCurve; int /*<<< orphan*/  sampleSize; int /*<<< orphan*/  recvShadows; int /*<<< orphan*/  castShadows; int /*<<< orphan*/  entityNum; TYPE_1__* parent; int /*<<< orphan*/  shaderInfo; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_6__ {int outputNum; } ;

/* Variables and functions */
 TYPE_2__* AllocSurfaceExtra () ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SetSurfaceExtra( mapDrawSurface_t *ds, int num ){
	surfaceExtra_t  *se;


	/* dummy check */
	if ( ds == NULL || num < 0 ) {
		return;
	}

	/* get a new extra */
	se = AllocSurfaceExtra();

	/* copy out the relevant bits */
	se->mds = ds;
	se->si = ds->shaderInfo;
	se->parentSurfaceNum = ds->parent != NULL ? ds->parent->outputNum : -1;
	se->entityNum = ds->entityNum;
	se->castShadows = ds->castShadows;
	se->recvShadows = ds->recvShadows;
	se->sampleSize = ds->sampleSize;
	se->longestCurve = ds->longestCurve;
	VectorCopy( ds->lightmapAxis, se->lightmapAxis );

	/* debug code */
	//%	Sys_FPrintf( SYS_VRB, "SetSurfaceExtra(): entityNum = %d\n", ds->entityNum );
}