#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * nodebuffer; int /*<<< orphan*/ * nodes; scalar_t__ numnodes; int /*<<< orphan*/ * areas; scalar_t__ areanum; scalar_t__ numareas; int /*<<< orphan*/ * faces; scalar_t__ facenum; scalar_t__ numfaces; } ;

/* Variables and functions */
 TYPE_1__ tmpaasworld ; 

void AAS_InitTmpAAS(void)
{
	//tmp faces
	tmpaasworld.numfaces = 0;
	tmpaasworld.facenum = 0;
	tmpaasworld.faces = NULL;
	//tmp convex areas
	tmpaasworld.numareas = 0;
	tmpaasworld.areanum = 0;
	tmpaasworld.areas = NULL;
	//tmp nodes
	tmpaasworld.numnodes = 0;
	tmpaasworld.nodes = NULL;
	//
	tmpaasworld.nodebuffer = NULL;
}