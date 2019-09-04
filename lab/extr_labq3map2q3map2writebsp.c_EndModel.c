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
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_5__ {int /*<<< orphan*/  numBrushes; int /*<<< orphan*/  firstBrush; } ;
typedef  TYPE_1__ entity_t ;
struct TYPE_6__ {int /*<<< orphan*/  numBSPBrushes; int /*<<< orphan*/  firstBSPBrush; scalar_t__ firstBSPSurface; scalar_t__ numBSPSurfaces; } ;
typedef  TYPE_2__ bspModel_t ;

/* Variables and functions */
 int /*<<< orphan*/  EmitDrawNode_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* bspModels ; 
 scalar_t__ numBSPDrawSurfaces ; 
 size_t numBSPModels ; 

void EndModel( entity_t *e, node_t *headnode ){
	bspModel_t  *mod;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- EndModel ---\n" );

	/* emit the bsp */
	mod = &bspModels[ numBSPModels ];
	EmitDrawNode_r( headnode );

	/* set surfaces and brushes */
	mod->numBSPSurfaces = numBSPDrawSurfaces - mod->firstBSPSurface;
	mod->firstBSPBrush = e->firstBrush;
	mod->numBSPBrushes = e->numBrushes;

	/* increment model count */
	numBSPModels++;
}