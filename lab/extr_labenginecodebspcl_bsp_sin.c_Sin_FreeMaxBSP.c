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
 scalar_t__ sin_allocatedbspmem ; 
 int /*<<< orphan*/ * sin_dareaportals ; 
 int /*<<< orphan*/ * sin_dareas ; 
 int /*<<< orphan*/ * sin_dbrushes ; 
 int /*<<< orphan*/ * sin_dbrushsides ; 
 int /*<<< orphan*/ * sin_dedges ; 
 int /*<<< orphan*/ * sin_dentdata ; 
 int /*<<< orphan*/ * sin_dfaces ; 
 int /*<<< orphan*/ * sin_dleafbrushes ; 
 int /*<<< orphan*/ * sin_dleaffaces ; 
 int /*<<< orphan*/ * sin_dleafs ; 
 int /*<<< orphan*/ * sin_dlightdata ; 
 int /*<<< orphan*/ * sin_dmodels ; 
 int /*<<< orphan*/ * sin_dnodes ; 
 int /*<<< orphan*/ * sin_dplanes ; 
 int /*<<< orphan*/ * sin_dsurfedges ; 
 int /*<<< orphan*/ * sin_dvertexes ; 
 int /*<<< orphan*/ * sin_dvis ; 
 int /*<<< orphan*/ * sin_dvisdata ; 
 scalar_t__ sin_entdatasize ; 
 scalar_t__ sin_lightdatasize ; 
 int /*<<< orphan*/ * sin_lightinfo ; 
 scalar_t__ sin_numareaportals ; 
 scalar_t__ sin_numareas ; 
 scalar_t__ sin_numbrushes ; 
 scalar_t__ sin_numbrushsides ; 
 scalar_t__ sin_numedges ; 
 scalar_t__ sin_numfaces ; 
 scalar_t__ sin_numleafbrushes ; 
 scalar_t__ sin_numleaffaces ; 
 scalar_t__ sin_numleafs ; 
 scalar_t__ sin_numlightinfo ; 
 scalar_t__ sin_nummodels ; 
 scalar_t__ sin_numnodes ; 
 scalar_t__ sin_numplanes ; 
 scalar_t__ sin_numsurfedges ; 
 scalar_t__ sin_numtexinfo ; 
 scalar_t__ sin_numvertexes ; 
 int /*<<< orphan*/ * sin_texinfo ; 
 scalar_t__ sin_visdatasize ; 

void Sin_FreeMaxBSP(void)
{
	//models
	sin_nummodels = 0;
	FreeMemory(sin_dmodels);
	sin_dmodels = NULL;
	//vis data
	sin_visdatasize = 0;
	FreeMemory(sin_dvisdata);
	sin_dvisdata = NULL;
	sin_dvis = NULL;
	//light data
	sin_lightdatasize = 0;
	FreeMemory(sin_dlightdata);
	sin_dlightdata = NULL;
	//entity data
	sin_entdatasize = 0;
	FreeMemory(sin_dentdata);
	sin_dentdata = NULL;
	//leafs
	sin_numleafs = 0;
	FreeMemory(sin_dleafs);
	sin_dleafs = NULL;
	//planes
	sin_numplanes = 0;
	FreeMemory(sin_dplanes);
	sin_dplanes = NULL;
	//vertexes
	sin_numvertexes = 0;
	FreeMemory(sin_dvertexes);
	sin_dvertexes = NULL;
	//nodes
	sin_numnodes = 0;
	FreeMemory(sin_dnodes);
	sin_dnodes = NULL;
	//texture info
	sin_numtexinfo = 0;
	FreeMemory(sin_texinfo);
	sin_texinfo = NULL;
	//faces
	sin_numfaces = 0;
	FreeMemory(sin_dfaces);
	sin_dfaces = NULL;
	//edges
	sin_numedges = 0;
	FreeMemory(sin_dedges);
	sin_dedges = NULL;
	//leaf faces
	sin_numleaffaces = 0;
	FreeMemory(sin_dleaffaces);
	sin_dleaffaces = NULL;
	//leaf brushes
	sin_numleafbrushes = 0;
	FreeMemory(sin_dleafbrushes);
	sin_dleafbrushes = NULL;
	//surface edges
	sin_numsurfedges = 0;
	FreeMemory(sin_dsurfedges);
	sin_dsurfedges = NULL;
	//brushes
	sin_numbrushes = 0;
	FreeMemory(sin_dbrushes);
	sin_dbrushes = NULL;
	//brushsides
	sin_numbrushsides = 0;
	FreeMemory(sin_dbrushsides);
	sin_dbrushsides = NULL;
	//areas
	sin_numareas = 0;
	FreeMemory(sin_dareas);
	sin_dareas = NULL;
	//area portals
	sin_numareaportals = 0;
	FreeMemory(sin_dareaportals);
	sin_dareaportals = NULL;
	//light info
	sin_numlightinfo = 0;
	FreeMemory(sin_lightinfo);
	sin_lightinfo = NULL;
	//
	Log_Print("freed ");
	PrintMemorySize(sin_allocatedbspmem);
	Log_Print(" of BSP memory\n");
	sin_allocatedbspmem = 0;
}