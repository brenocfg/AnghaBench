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
struct TYPE_5__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_6__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ bspPlane_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* bspPlanes ; 
 TYPE_1__* mapplanes ; 
 size_t numBSPPlanes ; 
 int nummapplanes ; 

void EmitPlanes( void ){
	int i;
	bspPlane_t  *bp;
	plane_t     *mp;


	/* walk plane list */
	mp = mapplanes;
	for ( i = 0; i < nummapplanes; i++, mp++ )
	{
		bp = &bspPlanes[ numBSPPlanes ];
		VectorCopy( mp->normal, bp->normal );
		bp->dist = mp->dist;
		numBSPPlanes++;
	}

	/* emit some statistics */
	Sys_FPrintf( SYS_VRB, "%9d BSP planes\n", numBSPPlanes );
}