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
typedef  int /*<<< orphan*/  shaderInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  MakeDebugPortalSurfs_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/ * ShaderInfoForShader (char*) ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 

void MakeDebugPortalSurfs( tree_t *tree ){
	shaderInfo_t    *si;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- MakeDebugPortalSurfs ---\n" );

	/* get portal debug shader */
	si = ShaderInfoForShader( "debugportals" );

	/* walk the tree */
	MakeDebugPortalSurfs_r( tree->headnode, si );
}