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
typedef  int /*<<< orphan*/  sin_texinfo_t ;
typedef  int /*<<< orphan*/  sin_lightvalue_t ;
typedef  int /*<<< orphan*/  sin_dvis_t ;
typedef  int /*<<< orphan*/  sin_dvertex_t ;
typedef  int /*<<< orphan*/  sin_dplane_t ;
typedef  int /*<<< orphan*/  sin_dnode_t ;
typedef  int /*<<< orphan*/  sin_dmodel_t ;
typedef  int /*<<< orphan*/  sin_dleaf_t ;
typedef  int /*<<< orphan*/  sin_dface_t ;
typedef  int /*<<< orphan*/  sin_dedge_t ;
typedef  int /*<<< orphan*/  sin_dbrushside_t ;
typedef  int /*<<< orphan*/  sin_dbrush_t ;
typedef  int /*<<< orphan*/  sin_dareaportal_t ;
typedef  int /*<<< orphan*/  sin_darea_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int /*<<< orphan*/  PrintMemorySize (int) ; 
 int SIN_MAX_MAP_AREAPORTALS ; 
 int SIN_MAX_MAP_AREAS ; 
 int SIN_MAX_MAP_BRUSHES ; 
 int SIN_MAX_MAP_BRUSHSIDES ; 
 int SIN_MAX_MAP_EDGES ; 
 int SIN_MAX_MAP_ENTSTRING ; 
 int SIN_MAX_MAP_FACES ; 
 int SIN_MAX_MAP_LEAFBRUSHES ; 
 int SIN_MAX_MAP_LEAFFACES ; 
 int SIN_MAX_MAP_LEAFS ; 
 int SIN_MAX_MAP_LIGHTINFO ; 
 int SIN_MAX_MAP_LIGHTING ; 
 int SIN_MAX_MAP_MODELS ; 
 int SIN_MAX_MAP_NODES ; 
 int SIN_MAX_MAP_PLANES ; 
 int SIN_MAX_MAP_SURFEDGES ; 
 int SIN_MAX_MAP_TEXINFO ; 
 int SIN_MAX_MAP_VERTS ; 
 int SIN_MAX_MAP_VISIBILITY ; 
 int sin_allocatedbspmem ; 
 int /*<<< orphan*/ * sin_dareaportals ; 
 int /*<<< orphan*/ * sin_dareas ; 
 int /*<<< orphan*/ * sin_dbrushes ; 
 int /*<<< orphan*/ * sin_dbrushsides ; 
 int /*<<< orphan*/ * sin_dedges ; 
 char* sin_dentdata ; 
 int /*<<< orphan*/ * sin_dfaces ; 
 unsigned short* sin_dleafbrushes ; 
 unsigned short* sin_dleaffaces ; 
 int /*<<< orphan*/ * sin_dleafs ; 
 int /*<<< orphan*/ * sin_dlightdata ; 
 int /*<<< orphan*/ * sin_dmodels ; 
 int /*<<< orphan*/ * sin_dnodes ; 
 int /*<<< orphan*/ * sin_dplanes ; 
 int* sin_dsurfedges ; 
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

void Sin_AllocMaxBSP(void)
{
	//models
	sin_nummodels = 0;
	sin_dmodels = (sin_dmodel_t *) GetClearedMemory(SIN_MAX_MAP_MODELS * sizeof(sin_dmodel_t));
	sin_allocatedbspmem += SIN_MAX_MAP_MODELS * sizeof(sin_dmodel_t);
	//vis data
	sin_visdatasize = 0;
	sin_dvisdata = (byte *) GetClearedMemory(SIN_MAX_MAP_VISIBILITY * sizeof(byte));
	sin_dvis = (sin_dvis_t *) sin_dvisdata;
	sin_allocatedbspmem += SIN_MAX_MAP_VISIBILITY * sizeof(byte);
	//light data
	sin_lightdatasize = 0;
	sin_dlightdata = (byte *) GetClearedMemory(SIN_MAX_MAP_LIGHTING * sizeof(byte));
	sin_allocatedbspmem += SIN_MAX_MAP_LIGHTING * sizeof(byte);
	//entity data
	sin_entdatasize = 0;
	sin_dentdata = (char *) GetClearedMemory(SIN_MAX_MAP_ENTSTRING * sizeof(char));
	sin_allocatedbspmem += SIN_MAX_MAP_ENTSTRING * sizeof(char);
	//leafs
	sin_numleafs = 0;
	sin_dleafs = (sin_dleaf_t *) GetClearedMemory(SIN_MAX_MAP_LEAFS * sizeof(sin_dleaf_t));
	sin_allocatedbspmem += SIN_MAX_MAP_LEAFS * sizeof(sin_dleaf_t);
	//planes
	sin_numplanes = 0;
	sin_dplanes = (sin_dplane_t *) GetClearedMemory(SIN_MAX_MAP_PLANES * sizeof(sin_dplane_t));
	sin_allocatedbspmem += SIN_MAX_MAP_PLANES * sizeof(sin_dplane_t);
	//vertexes
	sin_numvertexes = 0;
	sin_dvertexes = (sin_dvertex_t *) GetClearedMemory(SIN_MAX_MAP_VERTS * sizeof(sin_dvertex_t));
	sin_allocatedbspmem += SIN_MAX_MAP_VERTS * sizeof(sin_dvertex_t);
	//nodes
	sin_numnodes = 0;
	sin_dnodes = (sin_dnode_t *) GetClearedMemory(SIN_MAX_MAP_NODES * sizeof(sin_dnode_t));
	sin_allocatedbspmem += SIN_MAX_MAP_NODES * sizeof(sin_dnode_t);
	//texture info
	sin_numtexinfo = 0;
	sin_texinfo = (sin_texinfo_t *) GetClearedMemory(SIN_MAX_MAP_TEXINFO * sizeof(sin_texinfo_t));
	sin_allocatedbspmem += SIN_MAX_MAP_TEXINFO * sizeof(sin_texinfo_t);
	//faces
	sin_numfaces = 0;
	sin_dfaces = (sin_dface_t *) GetClearedMemory(SIN_MAX_MAP_FACES * sizeof(sin_dface_t));
	sin_allocatedbspmem += SIN_MAX_MAP_FACES * sizeof(sin_dface_t);
	//edges
	sin_numedges = 0;
	sin_dedges = (sin_dedge_t *) GetClearedMemory(SIN_MAX_MAP_EDGES * sizeof(sin_dedge_t));
	sin_allocatedbspmem += SIN_MAX_MAP_EDGES * sizeof(sin_dedge_t);
	//leaf faces
	sin_numleaffaces = 0;
	sin_dleaffaces = (unsigned short *) GetClearedMemory(SIN_MAX_MAP_LEAFFACES * sizeof(unsigned short));
	sin_allocatedbspmem += SIN_MAX_MAP_LEAFFACES * sizeof(unsigned short);
	//leaf brushes
	sin_numleafbrushes = 0;
	sin_dleafbrushes = (unsigned short *) GetClearedMemory(SIN_MAX_MAP_LEAFBRUSHES * sizeof(unsigned short));
	sin_allocatedbspmem += SIN_MAX_MAP_LEAFBRUSHES * sizeof(unsigned short);
	//surface edges
	sin_numsurfedges = 0;
	sin_dsurfedges = (int *) GetClearedMemory(SIN_MAX_MAP_SURFEDGES * sizeof(int));
	sin_allocatedbspmem += SIN_MAX_MAP_SURFEDGES * sizeof(int);
	//brushes
	sin_numbrushes = 0;
	sin_dbrushes = (sin_dbrush_t *) GetClearedMemory(SIN_MAX_MAP_BRUSHES * sizeof(sin_dbrush_t));
	sin_allocatedbspmem += SIN_MAX_MAP_BRUSHES * sizeof(sin_dbrush_t);
	//brushsides
	sin_numbrushsides = 0;
	sin_dbrushsides = (sin_dbrushside_t *) GetClearedMemory(SIN_MAX_MAP_BRUSHSIDES * sizeof(sin_dbrushside_t));
	sin_allocatedbspmem += SIN_MAX_MAP_BRUSHSIDES * sizeof(sin_dbrushside_t);
	//areas
	sin_numareas = 0;
	sin_dareas = (sin_darea_t *) GetClearedMemory(SIN_MAX_MAP_AREAS * sizeof(sin_darea_t));
	sin_allocatedbspmem += SIN_MAX_MAP_AREAS * sizeof(sin_darea_t);
	//area portals
	sin_numareaportals = 0;
	sin_dareaportals = (sin_dareaportal_t *) GetClearedMemory(SIN_MAX_MAP_AREAPORTALS * sizeof(sin_dareaportal_t));
	sin_allocatedbspmem += SIN_MAX_MAP_AREAPORTALS * sizeof(sin_dareaportal_t);
	//light info
	sin_numlightinfo = 0;
	sin_lightinfo = (sin_lightvalue_t *) GetClearedMemory(SIN_MAX_MAP_LIGHTINFO * sizeof(sin_lightvalue_t));
	sin_allocatedbspmem += SIN_MAX_MAP_LIGHTINFO * sizeof(sin_lightvalue_t);
	//print allocated memory
	Log_Print("allocated ");
	PrintMemorySize(sin_allocatedbspmem);
	Log_Print(" of BSP memory\n");
}