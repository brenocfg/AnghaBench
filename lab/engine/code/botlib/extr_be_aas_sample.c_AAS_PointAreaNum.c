#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ aas_plane_t ;
struct TYPE_6__ {size_t planenum; int* children; } ;
typedef  TYPE_2__ aas_node_t ;
struct TYPE_8__ {int numnodes; size_t numplanes; TYPE_1__* planes; TYPE_2__* nodes; int /*<<< orphan*/  loaded; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_4__ aasworld ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 

int AAS_PointAreaNum(vec3_t point)
{
	int nodenum;
	vec_t	dist;
	aas_node_t *node;
	aas_plane_t *plane;

	if (!aasworld.loaded)
	{
		botimport.Print(PRT_ERROR, "AAS_PointAreaNum: aas not loaded\n");
		return 0;
	} //end if

	//start with node 1 because node zero is a dummy used for solid leafs
	nodenum = 1;
	while (nodenum > 0)
	{
//		botimport.Print(PRT_MESSAGE, "[%d]", nodenum);
#ifdef AAS_SAMPLE_DEBUG
		if (nodenum >= aasworld.numnodes)
		{
			botimport.Print(PRT_ERROR, "nodenum = %d >= aasworld.numnodes = %d\n", nodenum, aasworld.numnodes);
			return 0;
		} //end if
#endif //AAS_SAMPLE_DEBUG
		node = &aasworld.nodes[nodenum];
#ifdef AAS_SAMPLE_DEBUG
		if (node->planenum < 0 || node->planenum >= aasworld.numplanes)
		{
			botimport.Print(PRT_ERROR, "node->planenum = %d >= aasworld.numplanes = %d\n", node->planenum, aasworld.numplanes);
			return 0;
		} //end if
#endif //AAS_SAMPLE_DEBUG
		plane = &aasworld.planes[node->planenum];
		dist = DotProduct(point, plane->normal) - plane->dist;
		if (dist > 0) nodenum = node->children[0];
		else nodenum = node->children[1];
	} //end while
	if (!nodenum)
	{
#ifdef AAS_SAMPLE_DEBUG
		botimport.Print(PRT_MESSAGE, "in solid\n");
#endif //AAS_SAMPLE_DEBUG
		return 0;
	} //end if
	return -nodenum;
}