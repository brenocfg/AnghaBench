#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  PrintMemorySize (scalar_t__) ; 
 scalar_t__ allocatedbspmem ; 
 int /*<<< orphan*/ * dareaportals ; 
 int /*<<< orphan*/ * dareas ; 
 int /*<<< orphan*/ * dbrushes ; 
 int /*<<< orphan*/ * dbrushsides ; 
 int /*<<< orphan*/ * dedges ; 
 int /*<<< orphan*/ * dentdata ; 
 int /*<<< orphan*/ * dfaces ; 
 int /*<<< orphan*/ * dleafbrushes ; 
 int /*<<< orphan*/ * dleaffaces ; 
 int /*<<< orphan*/ * dleafs ; 
 int /*<<< orphan*/ * dlightdata ; 
 int /*<<< orphan*/ * dmodels ; 
 int /*<<< orphan*/ * dnodes ; 
 int /*<<< orphan*/ * dplanes ; 
 int /*<<< orphan*/ * dsurfedges ; 
 int /*<<< orphan*/ * dvertexes ; 
 int /*<<< orphan*/ * dvis ; 
 int /*<<< orphan*/ * dvisdata ; 
 scalar_t__ entdatasize ; 
 scalar_t__ lightdatasize ; 
 scalar_t__ numareaportals ; 
 scalar_t__ numareas ; 
 scalar_t__ numbrushes ; 
 scalar_t__ numbrushsides ; 
 scalar_t__ numedges ; 
 scalar_t__ numfaces ; 
 scalar_t__ numleafbrushes ; 
 scalar_t__ numleaffaces ; 
 scalar_t__ numleafs ; 
 scalar_t__ nummodels ; 
 scalar_t__ numnodes ; 
 scalar_t__ numplanes ; 
 scalar_t__ numsurfedges ; 
 scalar_t__ numvertexes ; 
 scalar_t__ visdatasize ; 

void Q2_FreeMaxBSP(void)
{
	//models
	nummodels = 0;
	FreeMemory(dmodels);
	dmodels = NULL;
	//vis data
	visdatasize = 0;
	FreeMemory(dvisdata);
	dvisdata = NULL;
	dvis = NULL;
	//light data
	lightdatasize = 0;
	FreeMemory(dlightdata);
	dlightdata = NULL;
	//entity data
	entdatasize = 0;
	FreeMemory(dentdata);
	dentdata = NULL;
	//leafs
	numleafs = 0;
	FreeMemory(dleafs);
	dleafs = NULL;
	//planes
	numplanes = 0;
	FreeMemory(dplanes);
	dplanes = NULL;
	//vertexes
	numvertexes = 0;
	FreeMemory(dvertexes);
	dvertexes = NULL;
	//nodes
	numnodes = 0;
	FreeMemory(dnodes);
	dnodes = NULL;
	/*
	//texture info
	numtexinfo = 0;
	FreeMemory(texinfo);
	texinfo = NULL;
	//*/
	//faces
	numfaces = 0;
	FreeMemory(dfaces);
	dfaces = NULL;
	//edges
	numedges = 0;
	FreeMemory(dedges);
	dedges = NULL;
	//leaf faces
	numleaffaces = 0;
	FreeMemory(dleaffaces);
	dleaffaces = NULL;
	//leaf brushes
	numleafbrushes = 0;
	FreeMemory(dleafbrushes);
	dleafbrushes = NULL;
	//surface edges
	numsurfedges = 0;
	FreeMemory(dsurfedges);
	dsurfedges = NULL;
	//brushes
	numbrushes = 0;
	FreeMemory(dbrushes);
	dbrushes = NULL;
	//brushsides
	numbrushsides = 0;
	FreeMemory(dbrushsides);
	dbrushsides = NULL;
	//areas
	numareas = 0;
	FreeMemory(dareas);
	dareas = NULL;
	//area portals
	numareaportals = 0;
	FreeMemory(dareaportals);
	dareaportals = NULL;
	//
	Log_Print("freed ");
	PrintMemorySize(allocatedbspmem);
	Log_Print(" of BSP memory\n");
	allocatedbspmem = 0;
}