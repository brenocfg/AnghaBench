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
typedef  int /*<<< orphan*/  hl_dvisdata ;
typedef  int /*<<< orphan*/  hl_dtexdata ;
typedef  int /*<<< orphan*/  hl_dlightdata ;
typedef  int /*<<< orphan*/  hl_dentdata ;

/* Variables and functions */
 scalar_t__ ArrayUsage (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTRIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTRYSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ GlobUsage (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hl_dclipnodes ; 
 int /*<<< orphan*/  hl_dedges ; 
 int /*<<< orphan*/  hl_dfaces ; 
 int /*<<< orphan*/  hl_dleafs ; 
 int /*<<< orphan*/  hl_dmarksurfaces ; 
 int /*<<< orphan*/  hl_dmodels ; 
 int /*<<< orphan*/  hl_dnodes ; 
 int /*<<< orphan*/  hl_dplanes ; 
 int /*<<< orphan*/  hl_dsurfedges ; 
 int /*<<< orphan*/  hl_dvertexes ; 
 int /*<<< orphan*/  hl_entdatasize ; 
 int /*<<< orphan*/  hl_lightdatasize ; 
 int /*<<< orphan*/  hl_numclipnodes ; 
 int /*<<< orphan*/  hl_numedges ; 
 int /*<<< orphan*/  hl_numfaces ; 
 int /*<<< orphan*/  hl_numleafs ; 
 int /*<<< orphan*/  hl_nummarksurfaces ; 
 int /*<<< orphan*/  hl_nummodels ; 
 int /*<<< orphan*/  hl_numnodes ; 
 int /*<<< orphan*/  hl_numplanes ; 
 int /*<<< orphan*/  hl_numsurfedges ; 
 int /*<<< orphan*/  hl_numtexinfo ; 
 int /*<<< orphan*/  hl_numvertexes ; 
 int /*<<< orphan*/  hl_texdatasize ; 
 int /*<<< orphan*/  hl_texinfo ; 
 int /*<<< orphan*/  hl_visdatasize ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

void HL_PrintBSPFileSizes(void)
{
	int	totalmemory = 0;

	qprintf("\n");
	qprintf("Object names  Objects/Maxobjs  Memory / Maxmem  Fullness\n" );
	qprintf("------------  ---------------  ---------------  --------\n" );

	totalmemory += ArrayUsage( "models",		hl_nummodels,		ENTRIES(hl_dmodels),		ENTRYSIZE(hl_dmodels) );
	totalmemory += ArrayUsage( "planes",		hl_numplanes,		ENTRIES(hl_dplanes),		ENTRYSIZE(hl_dplanes) );
	totalmemory += ArrayUsage( "vertexes",		hl_numvertexes,	ENTRIES(hl_dvertexes),	ENTRYSIZE(hl_dvertexes) );
	totalmemory += ArrayUsage( "nodes",			hl_numnodes,		ENTRIES(hl_dnodes),		ENTRYSIZE(hl_dnodes) );
	totalmemory += ArrayUsage( "texinfos",		hl_numtexinfo,		ENTRIES(hl_texinfo),		ENTRYSIZE(hl_texinfo) );
	totalmemory += ArrayUsage( "faces",			hl_numfaces,		ENTRIES(hl_dfaces),		ENTRYSIZE(hl_dfaces) );
	totalmemory += ArrayUsage( "clipnodes",	hl_numclipnodes,	ENTRIES(hl_dclipnodes),	ENTRYSIZE(hl_dclipnodes) );
	totalmemory += ArrayUsage( "leaves",		hl_numleafs,		ENTRIES(hl_dleafs),		ENTRYSIZE(hl_dleafs) );
	totalmemory += ArrayUsage( "marksurfaces",hl_nummarksurfaces,ENTRIES(hl_dmarksurfaces),ENTRYSIZE(hl_dmarksurfaces) );
	totalmemory += ArrayUsage( "surfedges",	hl_numsurfedges,	ENTRIES(hl_dsurfedges),	ENTRYSIZE(hl_dsurfedges) );
	totalmemory += ArrayUsage( "edges",			hl_numedges,		ENTRIES(hl_dedges),		ENTRYSIZE(hl_dedges) );

	totalmemory += GlobUsage( "texdata",		hl_texdatasize,	sizeof(hl_dtexdata) );
	totalmemory += GlobUsage( "lightdata",		hl_lightdatasize,	sizeof(hl_dlightdata) );
	totalmemory += GlobUsage( "visdata",		hl_visdatasize,	sizeof(hl_dvisdata) );
	totalmemory += GlobUsage( "entdata",		hl_entdatasize,	sizeof(hl_dentdata) );

	qprintf( "=== Total BSP file data space used: %d bytes ===\n\n", totalmemory );
}