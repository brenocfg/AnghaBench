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
typedef  int /*<<< orphan*/  q1_texinfo_t ;
typedef  int /*<<< orphan*/  q1_dvertex_t ;
typedef  int /*<<< orphan*/  q1_dplane_t ;
typedef  int /*<<< orphan*/  q1_dnode_t ;
struct TYPE_2__ {int nummiptex; } ;
typedef  TYPE_1__ q1_dmiptexlump_t ;
typedef  int /*<<< orphan*/  q1_dmarksurfaces ;
typedef  int /*<<< orphan*/  q1_dleaf_t ;
typedef  int /*<<< orphan*/  q1_dface_t ;
typedef  int /*<<< orphan*/  q1_dedge_t ;
typedef  int /*<<< orphan*/  q1_dclipnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ q1_dtexdata ; 
 int q1_entdatasize ; 
 int q1_lightdatasize ; 
 int q1_numclipnodes ; 
 int q1_numedges ; 
 int q1_numfaces ; 
 int q1_numleafs ; 
 int q1_nummarksurfaces ; 
 int q1_numnodes ; 
 int q1_numplanes ; 
 int q1_numsurfedges ; 
 int q1_numtexinfo ; 
 int q1_numvertexes ; 
 int q1_texdatasize ; 
 int q1_visdatasize ; 

void Q1_PrintBSPFileSizes (void)
{
	printf ("%5i planes       %6i\n"
		,q1_numplanes, (int)(q1_numplanes*sizeof(q1_dplane_t)));
	printf ("%5i vertexes     %6i\n"
		,q1_numvertexes, (int)(q1_numvertexes*sizeof(q1_dvertex_t)));
	printf ("%5i nodes        %6i\n"
		,q1_numnodes, (int)(q1_numnodes*sizeof(q1_dnode_t)));
	printf ("%5i texinfo      %6i\n"
		,q1_numtexinfo, (int)(q1_numtexinfo*sizeof(q1_texinfo_t)));
	printf ("%5i faces        %6i\n"
		,q1_numfaces, (int)(q1_numfaces*sizeof(q1_dface_t)));
	printf ("%5i clipnodes    %6i\n"
		,q1_numclipnodes, (int)(q1_numclipnodes*sizeof(q1_dclipnode_t)));
	printf ("%5i leafs        %6i\n"
		,q1_numleafs, (int)(q1_numleafs*sizeof(q1_dleaf_t)));
	printf ("%5i marksurfaces %6i\n"
		,q1_nummarksurfaces, (int)(q1_nummarksurfaces*sizeof(q1_dmarksurfaces[0])));
	printf ("%5i surfedges    %6i\n"
		,q1_numsurfedges, (int)(q1_numsurfedges*sizeof(q1_dmarksurfaces[0])));
	printf ("%5i edges        %6i\n"
		,q1_numedges, (int)(q1_numedges*sizeof(q1_dedge_t)));
	if (!q1_texdatasize)
		printf ("    0 textures          0\n");
	else
		printf ("%5i textures     %6i\n",((q1_dmiptexlump_t*)q1_dtexdata)->nummiptex, q1_texdatasize);
	printf ("      lightdata    %6i\n", q1_lightdatasize);
	printf ("      visdata      %6i\n", q1_visdatasize);
	printf ("      entdata      %6i\n", q1_entdatasize);
}