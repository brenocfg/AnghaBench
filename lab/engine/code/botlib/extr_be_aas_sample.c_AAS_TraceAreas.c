#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_6__ {float* start; float* end; int planenum; int nodenum; } ;
typedef  TYPE_1__ aas_tracestack_t ;
struct TYPE_7__ {int type; float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ aas_plane_t ;
struct TYPE_8__ {size_t planenum; int* children; } ;
typedef  TYPE_3__ aas_node_t ;
struct TYPE_10__ {int numareasettings; int numnodes; TYPE_2__* planes; TYPE_3__* nodes; int /*<<< orphan*/  loaded; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 float DotProduct (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 TYPE_5__ aasworld ; 
 TYPE_4__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,char*) ; 

int AAS_TraceAreas(vec3_t start, vec3_t end, int *areas, vec3_t *points, int maxareas)
{
	int side, nodenum, tmpplanenum;
	int numareas;
	float front, back, frac;
	vec3_t cur_start, cur_end, cur_mid;
	aas_tracestack_t tracestack[127];
	aas_tracestack_t *tstack_p;
	aas_node_t *aasnode;
	aas_plane_t *plane;

	numareas = 0;
	areas[0] = 0;
	if (!aasworld.loaded) return numareas;

	tstack_p = tracestack;
	//we start with the whole line on the stack
	VectorCopy(start, tstack_p->start);
	VectorCopy(end, tstack_p->end);
	tstack_p->planenum = 0;
	//start with node 1 because node zero is a dummy for a solid leaf
	tstack_p->nodenum = 1;		//starting at the root of the tree
	tstack_p++;

	while (1)
	{
		//pop up the stack
		tstack_p--;
		//if the trace stack is empty (ended up with a piece of the
		//line to be traced in an area)
		if (tstack_p < tracestack)
		{
			return numareas;
		} //end if
		//number of the current node to test the line against
		nodenum = tstack_p->nodenum;
		//if it is an area
		if (nodenum < 0)
		{
#ifdef AAS_SAMPLE_DEBUG
			if (-nodenum > aasworld.numareasettings)
			{
				botimport.Print(PRT_ERROR, "AAS_TraceAreas: -nodenum = %d out of range\n", -nodenum);
				return numareas;
			} //end if
#endif //AAS_SAMPLE_DEBUG
			//botimport.Print(PRT_MESSAGE, "areanum = %d, must be %d\n", -nodenum, AAS_PointAreaNum(start));
			areas[numareas] = -nodenum;
			if (points) VectorCopy(tstack_p->start, points[numareas]);
			numareas++;
			if (numareas >= maxareas) return numareas;
			continue;
		} //end if
		//if it is a solid leaf
		if (!nodenum)
		{
			continue;
		} //end if
#ifdef AAS_SAMPLE_DEBUG
		if (nodenum > aasworld.numnodes)
		{
			botimport.Print(PRT_ERROR, "AAS_TraceAreas: nodenum out of range\n");
			return numareas;
		} //end if
#endif //AAS_SAMPLE_DEBUG
		//the node to test against
		aasnode = &aasworld.nodes[nodenum];
		//start point of current line to test against node
		VectorCopy(tstack_p->start, cur_start);
		//end point of the current line to test against node
		VectorCopy(tstack_p->end, cur_end);
		//the current node plane
		plane = &aasworld.planes[aasnode->planenum];

		switch(plane->type)
		{/*FIXME: wtf doesn't this work? obviously the node planes aren't always facing positive!!!
			//check for axial planes
			case PLANE_X:
			{
				front = cur_start[0] - plane->dist;
				back = cur_end[0] - plane->dist;
				break;
			} //end case
			case PLANE_Y:
			{
				front = cur_start[1] - plane->dist;
				back = cur_end[1] - plane->dist;
				break;
			} //end case
			case PLANE_Z:
			{
				front = cur_start[2] - plane->dist;
				back = cur_end[2] - plane->dist;
				break;
			} //end case*/
			default: //gee it's not an axial plane
			{
				front = DotProduct(cur_start, plane->normal) - plane->dist;
				back = DotProduct(cur_end, plane->normal) - plane->dist;
				break;
			} //end default
		} //end switch

		//if the whole to be traced line is totally at the front of this node
		//only go down the tree with the front child
		if (front > 0 && back > 0)
		{
			//keep the current start and end point on the stack
			//and go down the tree with the front child
			tstack_p->nodenum = aasnode->children[0];
			tstack_p++;
			if (tstack_p >= &tracestack[127])
			{
				botimport.Print(PRT_ERROR, "AAS_TraceAreas: stack overflow\n");
				return numareas;
			} //end if
		} //end if
		//if the whole to be traced line is totally at the back of this node
		//only go down the tree with the back child
		else if (front <= 0 && back <= 0)
		{
			//keep the current start and end point on the stack
			//and go down the tree with the back child
			tstack_p->nodenum = aasnode->children[1];
			tstack_p++;
			if (tstack_p >= &tracestack[127])
			{
				botimport.Print(PRT_ERROR, "AAS_TraceAreas: stack overflow\n");
				return numareas;
			} //end if
		} //end if
		//go down the tree both at the front and back of the node
		else
		{
			tmpplanenum = tstack_p->planenum;
			//calculate the hitpoint with the node (split point of the line)
			//put the crosspoint TRACEPLANE_EPSILON pixels on the near side
			if (front < 0) frac = (front)/(front-back);
			else frac = (front)/(front-back);
			if (frac < 0) frac = 0;
			else if (frac > 1) frac = 1;
			//frac = front / (front-back);
			//
			cur_mid[0] = cur_start[0] + (cur_end[0] - cur_start[0]) * frac;
			cur_mid[1] = cur_start[1] + (cur_end[1] - cur_start[1]) * frac;
			cur_mid[2] = cur_start[2] + (cur_end[2] - cur_start[2]) * frac;

//			AAS_DrawPlaneCross(cur_mid, plane->normal, plane->dist, plane->type, LINECOLOR_RED);
			//side the front part of the line is on
			side = front < 0;
			//first put the end part of the line on the stack (back side)
			VectorCopy(cur_mid, tstack_p->start);
			//not necessary to store because still on stack
			//VectorCopy(cur_end, tstack_p->end);
			tstack_p->planenum = aasnode->planenum;
			tstack_p->nodenum = aasnode->children[!side];
			tstack_p++;
			if (tstack_p >= &tracestack[127])
			{
				botimport.Print(PRT_ERROR, "AAS_TraceAreas: stack overflow\n");
				return numareas;
			} //end if
			//now put the part near the start of the line on the stack so we will
			//continue with thats part first. This way we'll find the first
			//hit of the bbox
			VectorCopy(cur_start, tstack_p->start);
			VectorCopy(cur_mid, tstack_p->end);
			tstack_p->planenum = tmpplanenum;
			tstack_p->nodenum = aasnode->children[side];
			tstack_p++;
			if (tstack_p >= &tracestack[127])
			{
				botimport.Print(PRT_ERROR, "AAS_TraceAreas: stack overflow\n");
				return numareas;
			} //end if
		} //end else
	} //end while
//	return numareas;
}