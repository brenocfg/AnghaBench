#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {void** clusterareanum; void* backcluster; void* frontcluster; void* areanum; } ;
struct TYPE_21__ {void** children; void* planenum; } ;
struct TYPE_20__ {int /*<<< orphan*/  traveltime; void* traveltype; void** end; void** start; void* edgenum; void* facenum; void* areanum; } ;
struct TYPE_19__ {void* firstreachablearea; void* numreachableareas; void* clusterareanum; void* cluster; void* presencetype; void* areaflags; void* contents; } ;
struct TYPE_18__ {void** center; void** maxs; void** mins; void* firstface; void* numfaces; void* areanum; } ;
struct TYPE_17__ {void* backarea; void* frontarea; void* firstedge; void* numedges; void* faceflags; void* planenum; } ;
struct TYPE_16__ {void** v; } ;
struct TYPE_15__ {void* type; void* dist; void** normal; } ;
struct TYPE_14__ {void** maxs; void** mins; void* flags; void* presencetype; } ;
struct TYPE_13__ {int numbboxes; int numvertexes; int numplanes; int numedges; int edgeindexsize; int numfaces; int faceindexsize; int numareas; int numareasettings; int reachabilitysize; int numnodes; int numportals; int portalindexsize; int numclusters; TYPE_10__* clusters; void** portalindex; TYPE_9__* portals; TYPE_8__* nodes; TYPE_7__* reachability; TYPE_6__* areasettings; TYPE_5__* areas; void** faceindex; TYPE_4__* faces; void** edgeindex; TYPE_3__* edges; TYPE_2__* planes; void*** vertexes; TYPE_1__* bboxes; } ;
struct TYPE_12__ {void* firstportal; void* numportals; void* numreachabilityareas; void* numareas; } ;

/* Variables and functions */
 void* LittleFloat (void*) ; 
 void* LittleLong (void*) ; 
 int /*<<< orphan*/  LittleShort (int /*<<< orphan*/ ) ; 
 TYPE_11__ aasworld ; 

void AAS_SwapAASData(void)
{
	int i, j;
	//bounding boxes
	for (i = 0; i < aasworld.numbboxes; i++)
	{
		aasworld.bboxes[i].presencetype = LittleLong(aasworld.bboxes[i].presencetype);
		aasworld.bboxes[i].flags = LittleLong(aasworld.bboxes[i].flags);
		for (j = 0; j < 3; j++)
		{
			aasworld.bboxes[i].mins[j] = LittleFloat(aasworld.bboxes[i].mins[j]);
			aasworld.bboxes[i].maxs[j] = LittleFloat(aasworld.bboxes[i].maxs[j]);
		} //end for
	} //end for
	//vertexes
	for (i = 0; i < aasworld.numvertexes; i++)
	{
		for (j = 0; j < 3; j++)
			aasworld.vertexes[i][j] = LittleFloat(aasworld.vertexes[i][j]);
	} //end for
	//planes
	for (i = 0; i < aasworld.numplanes; i++)
	{
		for (j = 0; j < 3; j++)
			aasworld.planes[i].normal[j] = LittleFloat(aasworld.planes[i].normal[j]);
		aasworld.planes[i].dist = LittleFloat(aasworld.planes[i].dist);
		aasworld.planes[i].type = LittleLong(aasworld.planes[i].type);
	} //end for
	//edges
	for (i = 0; i < aasworld.numedges; i++)
	{
		aasworld.edges[i].v[0] = LittleLong(aasworld.edges[i].v[0]);
		aasworld.edges[i].v[1] = LittleLong(aasworld.edges[i].v[1]);
	} //end for
	//edgeindex
	for (i = 0; i < aasworld.edgeindexsize; i++)
	{
		aasworld.edgeindex[i] = LittleLong(aasworld.edgeindex[i]);
	} //end for
	//faces
	for (i = 0; i < aasworld.numfaces; i++)
	{
		aasworld.faces[i].planenum = LittleLong(aasworld.faces[i].planenum);
		aasworld.faces[i].faceflags = LittleLong(aasworld.faces[i].faceflags);
		aasworld.faces[i].numedges = LittleLong(aasworld.faces[i].numedges);
		aasworld.faces[i].firstedge = LittleLong(aasworld.faces[i].firstedge);
		aasworld.faces[i].frontarea = LittleLong(aasworld.faces[i].frontarea);
		aasworld.faces[i].backarea = LittleLong(aasworld.faces[i].backarea);
	} //end for
	//face index
	for (i = 0; i < aasworld.faceindexsize; i++)
	{
		aasworld.faceindex[i] = LittleLong(aasworld.faceindex[i]);
	} //end for
	//convex areas
	for (i = 0; i < aasworld.numareas; i++)
	{
		aasworld.areas[i].areanum = LittleLong(aasworld.areas[i].areanum);
		aasworld.areas[i].numfaces = LittleLong(aasworld.areas[i].numfaces);
		aasworld.areas[i].firstface = LittleLong(aasworld.areas[i].firstface);
		for (j = 0; j < 3; j++)
		{
			aasworld.areas[i].mins[j] = LittleFloat(aasworld.areas[i].mins[j]);
			aasworld.areas[i].maxs[j] = LittleFloat(aasworld.areas[i].maxs[j]);
			aasworld.areas[i].center[j] = LittleFloat(aasworld.areas[i].center[j]);
		} //end for
	} //end for
	//area settings
	for (i = 0; i < aasworld.numareasettings; i++)
	{
		aasworld.areasettings[i].contents = LittleLong(aasworld.areasettings[i].contents);
		aasworld.areasettings[i].areaflags = LittleLong(aasworld.areasettings[i].areaflags);
		aasworld.areasettings[i].presencetype = LittleLong(aasworld.areasettings[i].presencetype);
		aasworld.areasettings[i].cluster = LittleLong(aasworld.areasettings[i].cluster);
		aasworld.areasettings[i].clusterareanum = LittleLong(aasworld.areasettings[i].clusterareanum);
		aasworld.areasettings[i].numreachableareas = LittleLong(aasworld.areasettings[i].numreachableareas);
		aasworld.areasettings[i].firstreachablearea = LittleLong(aasworld.areasettings[i].firstreachablearea);
	} //end for
	//area reachability
	for (i = 0; i < aasworld.reachabilitysize; i++)
	{
		aasworld.reachability[i].areanum = LittleLong(aasworld.reachability[i].areanum);
		aasworld.reachability[i].facenum = LittleLong(aasworld.reachability[i].facenum);
		aasworld.reachability[i].edgenum = LittleLong(aasworld.reachability[i].edgenum);
		for (j = 0; j < 3; j++)
		{
			aasworld.reachability[i].start[j] = LittleFloat(aasworld.reachability[i].start[j]);
			aasworld.reachability[i].end[j] = LittleFloat(aasworld.reachability[i].end[j]);
		} //end for
		aasworld.reachability[i].traveltype = LittleLong(aasworld.reachability[i].traveltype);
		aasworld.reachability[i].traveltime = LittleShort(aasworld.reachability[i].traveltime);
	} //end for
	//nodes
	for (i = 0; i < aasworld.numnodes; i++)
	{
		aasworld.nodes[i].planenum = LittleLong(aasworld.nodes[i].planenum);
		aasworld.nodes[i].children[0] = LittleLong(aasworld.nodes[i].children[0]);
		aasworld.nodes[i].children[1] = LittleLong(aasworld.nodes[i].children[1]);
	} //end for
	//cluster portals
	for (i = 0; i < aasworld.numportals; i++)
	{
		aasworld.portals[i].areanum = LittleLong(aasworld.portals[i].areanum);
		aasworld.portals[i].frontcluster = LittleLong(aasworld.portals[i].frontcluster);
		aasworld.portals[i].backcluster = LittleLong(aasworld.portals[i].backcluster);
		aasworld.portals[i].clusterareanum[0] = LittleLong(aasworld.portals[i].clusterareanum[0]);
		aasworld.portals[i].clusterareanum[1] = LittleLong(aasworld.portals[i].clusterareanum[1]);
	} //end for
	//cluster portal index
	for (i = 0; i < aasworld.portalindexsize; i++)
	{
		aasworld.portalindex[i] = LittleLong(aasworld.portalindex[i]);
	} //end for
	//cluster
	for (i = 0; i < aasworld.numclusters; i++)
	{
		aasworld.clusters[i].numareas = LittleLong(aasworld.clusters[i].numareas);
		aasworld.clusters[i].numreachabilityareas = LittleLong(aasworld.clusters[i].numreachabilityareas);
		aasworld.clusters[i].numportals = LittleLong(aasworld.clusters[i].numportals);
		aasworld.clusters[i].firstportal = LittleLong(aasworld.clusters[i].firstportal);
	} //end for
}