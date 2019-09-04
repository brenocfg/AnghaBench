#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  FindAreas_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FloodSkyboxArea_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  c_areas ; 

void FloodAreas( tree_t *tree ){
	Sys_FPrintf( SYS_VRB,"--- FloodAreas ---\n" );
	FindAreas_r( tree->headnode );

	/* ydnar: flood all skybox nodes */
	FloodSkyboxArea_r( tree->headnode );

	/* check for areaportal brushes that don't touch two areas */
	/* ydnar: fix this rather than just silence the warnings */
	//%	CheckAreas_r( tree->headnode );

	Sys_FPrintf( SYS_VRB, "%9d areas\n", c_areas );
}