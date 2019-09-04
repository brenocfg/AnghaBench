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
typedef  int /*<<< orphan*/  q3_dshader_t ;
typedef  int /*<<< orphan*/  q3_drawVerts ;
typedef  int /*<<< orphan*/  q3_drawSurfaces ;
typedef  int /*<<< orphan*/  q3_drawIndexes ;
typedef  int /*<<< orphan*/  q3_dplane_t ;
typedef  int /*<<< orphan*/  q3_dnode_t ;
typedef  int /*<<< orphan*/  q3_dmodel_t ;
typedef  int /*<<< orphan*/  q3_dleafsurfaces ;
typedef  int /*<<< orphan*/  q3_dleafbrushes ;
typedef  int /*<<< orphan*/  q3_dleaf_t ;
typedef  int /*<<< orphan*/  q3_dfog_t ;
typedef  int /*<<< orphan*/  q3_dbrushside_t ;
typedef  int /*<<< orphan*/  q3_dbrush_t ;

/* Variables and functions */
 int LIGHTMAP_HEIGHT ; 
 int LIGHTMAP_WIDTH ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  Q3_ParseEntities () ; 
 int /*<<< orphan*/  num_entities ; 
 int /*<<< orphan*/  q3_entdatasize ; 
 int q3_numDrawIndexes ; 
 int q3_numDrawSurfaces ; 
 int q3_numDrawVerts ; 
 int q3_numFogs ; 
 int q3_numLightBytes ; 
 int q3_numShaders ; 
 int /*<<< orphan*/  q3_numVisBytes ; 
 int q3_numbrushes ; 
 int q3_numbrushsides ; 
 int q3_numleafbrushes ; 
 int q3_numleafs ; 
 int q3_numleafsurfaces ; 
 int q3_nummodels ; 
 int q3_numnodes ; 
 int q3_numplanes ; 

void Q3_PrintBSPFileSizes( void )
{
	if ( !num_entities )
	{
		Q3_ParseEntities();
	}

	Log_Print ("%6i models       %7i\n"
		,q3_nummodels, (int)(q3_nummodels*sizeof(q3_dmodel_t)));
	Log_Print ("%6i shaders      %7i\n"
		,q3_numShaders, (int)(q3_numShaders*sizeof(q3_dshader_t)));
	Log_Print ("%6i brushes      %7i\n"
		,q3_numbrushes, (int)(q3_numbrushes*sizeof(q3_dbrush_t)));
	Log_Print ("%6i brushsides   %7i\n"
		,q3_numbrushsides, (int)(q3_numbrushsides*sizeof(q3_dbrushside_t)));
	Log_Print ("%6i fogs         %7i\n"
		,q3_numFogs, (int)(q3_numFogs*sizeof(q3_dfog_t)));
	Log_Print ("%6i planes       %7i\n"
		,q3_numplanes, (int)(q3_numplanes*sizeof(q3_dplane_t)));
	Log_Print ("%6i entdata      %7i\n", num_entities, q3_entdatasize);

	Log_Print ("\n");

	Log_Print ("%6i nodes        %7i\n"
		,q3_numnodes, (int)(q3_numnodes*sizeof(q3_dnode_t)));
	Log_Print ("%6i leafs        %7i\n"
		,q3_numleafs, (int)(q3_numleafs*sizeof(q3_dleaf_t)));
	Log_Print ("%6i leafsurfaces %7i\n"
		,q3_numleafsurfaces, (int)(q3_numleafsurfaces*sizeof(q3_dleafsurfaces[0])));
	Log_Print ("%6i leafbrushes  %7i\n"
		,q3_numleafbrushes, (int)(q3_numleafbrushes*sizeof(q3_dleafbrushes[0])));
	Log_Print ("%6i drawverts    %7i\n"
		,q3_numDrawVerts, (int)(q3_numDrawVerts*sizeof(q3_drawVerts[0])));
	Log_Print ("%6i drawindexes  %7i\n"
		,q3_numDrawIndexes, (int)(q3_numDrawIndexes*sizeof(q3_drawIndexes[0])));
	Log_Print ("%6i drawsurfaces %7i\n"
		,q3_numDrawSurfaces, (int)(q3_numDrawSurfaces*sizeof(q3_drawSurfaces[0])));

	Log_Print ("%6i lightmaps    %7i\n"
		,q3_numLightBytes / (LIGHTMAP_WIDTH*LIGHTMAP_HEIGHT*3), q3_numLightBytes );
	Log_Print ("       visibility   %7i\n"
		, q3_numVisBytes );
}