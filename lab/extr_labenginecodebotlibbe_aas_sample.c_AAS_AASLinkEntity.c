#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  aas_plane_t ;
struct TYPE_8__ {size_t planenum; int* children; } ;
typedef  TYPE_1__ aas_node_t ;
struct TYPE_9__ {int nodenum; } ;
typedef  TYPE_2__ aas_linkstack_t ;
struct TYPE_10__ {int entnum; int areanum; struct TYPE_10__* prev_ent; struct TYPE_10__* next_ent; struct TYPE_10__* prev_area; struct TYPE_10__* next_area; } ;
typedef  TYPE_3__ aas_link_t ;
struct TYPE_12__ {int /*<<< orphan*/ * planes; TYPE_1__* nodes; TYPE_3__** arealinkedentities; int /*<<< orphan*/  loaded; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 TYPE_3__* AAS_AllocAASLink () ; 
 int AAS_BoxOnPlaneSide2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_5__ aasworld ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 

aas_link_t *AAS_AASLinkEntity(vec3_t absmins, vec3_t absmaxs, int entnum)
{
	int side, nodenum;
	aas_linkstack_t linkstack[128];
	aas_linkstack_t *lstack_p;
	aas_node_t *aasnode;
	aas_plane_t *plane;
	aas_link_t *link, *areas;

	if (!aasworld.loaded)
	{
		botimport.Print(PRT_ERROR, "AAS_LinkEntity: aas not loaded\n");
		return NULL;
	} //end if

	areas = NULL;
	//
	lstack_p = linkstack;
	//we start with the whole line on the stack
	//start with node 1 because node zero is a dummy used for solid leafs
	lstack_p->nodenum = 1;		//starting at the root of the tree
	lstack_p++;
	
	while (1)
	{
		//pop up the stack
		lstack_p--;
		//if the trace stack is empty (ended up with a piece of the
		//line to be traced in an area)
		if (lstack_p < linkstack) break;
		//number of the current node to test the line against
		nodenum = lstack_p->nodenum;
		//if it is an area
		if (nodenum < 0)
		{
			//NOTE: the entity might have already been linked into this area
			// because several node children can point to the same area
			for (link = aasworld.arealinkedentities[-nodenum]; link; link = link->next_ent)
			{
				if (link->entnum == entnum) break;
			} //end for
			if (link) continue;
			//
			link = AAS_AllocAASLink();
			if (!link) return areas;
			link->entnum = entnum;
			link->areanum = -nodenum;
			//put the link into the double linked area list of the entity
			link->prev_area = NULL;
			link->next_area = areas;
			if (areas) areas->prev_area = link;
			areas = link;
			//put the link into the double linked entity list of the area
			link->prev_ent = NULL;
			link->next_ent = aasworld.arealinkedentities[-nodenum];
			if (aasworld.arealinkedentities[-nodenum])
					aasworld.arealinkedentities[-nodenum]->prev_ent = link;
			aasworld.arealinkedentities[-nodenum] = link;
			//
			continue;
		} //end if
		//if solid leaf
		if (!nodenum) continue;
		//the node to test against
		aasnode = &aasworld.nodes[nodenum];
		//the current node plane
		plane = &aasworld.planes[aasnode->planenum];
		//get the side(s) the box is situated relative to the plane
		side = AAS_BoxOnPlaneSide2(absmins, absmaxs, plane);
		//if on the front side of the node
		if (side & 1)
		{
			lstack_p->nodenum = aasnode->children[0];
			lstack_p++;
		} //end if
		if (lstack_p >= &linkstack[127])
		{
			botimport.Print(PRT_ERROR, "AAS_LinkEntity: stack overflow\n");
			break;
		} //end if
		//if on the back side of the node
		if (side & 2)
		{
			lstack_p->nodenum = aasnode->children[1];
			lstack_p++;
		} //end if
		if (lstack_p >= &linkstack[127])
		{
			botimport.Print(PRT_ERROR, "AAS_LinkEntity: stack overflow\n");
			break;
		} //end if
	} //end while
	return areas;
}