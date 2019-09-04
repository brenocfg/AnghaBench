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
struct TYPE_4__ {scalar_t__ longestCurve; scalar_t__ maxIterations; } ;
typedef  TYPE_1__ parseMesh_t ;
typedef  int byte ;

/* Variables and functions */

__attribute__((used)) static void GrowGroup_r( parseMesh_t *pm, int patchNum, int patchCount, parseMesh_t **meshes, byte *bordering, byte *group ){
	int i;
	const byte  *row;


	/* early out check */
	if ( group[ patchNum ] ) {
		return;
	}


	/* set it */
	group[ patchNum ] = 1;
	row = bordering + patchNum * patchCount;

	/* check maximums */
	if ( meshes[ patchNum ]->longestCurve > pm->longestCurve ) {
		pm->longestCurve = meshes[ patchNum ]->longestCurve;
	}
	if ( meshes[ patchNum ]->maxIterations > pm->maxIterations ) {
		pm->maxIterations = meshes[ patchNum ]->maxIterations;
	}

	/* walk other patches */
	for ( i = 0; i < patchCount; i++ )
	{
		if ( row[ i ] ) {
			GrowGroup_r( pm, i, patchCount, meshes, bordering, group );
		}
	}
}