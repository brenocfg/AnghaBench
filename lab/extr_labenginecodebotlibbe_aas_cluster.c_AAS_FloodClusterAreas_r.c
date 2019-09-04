#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int frontarea; int backarea; } ;
typedef  TYPE_4__ aas_face_t ;
struct TYPE_11__ {int numfaces; int firstface; } ;
typedef  TYPE_5__ aas_area_t ;
struct TYPE_12__ {int numareas; TYPE_3__* areasettings; TYPE_2__* reachability; TYPE_4__* faces; int /*<<< orphan*/ * faceindex; TYPE_5__* areas; TYPE_1__* clusters; } ;
struct TYPE_9__ {int cluster; int contents; int numreachableareas; int firstreachablearea; int /*<<< orphan*/  clusterareanum; } ;
struct TYPE_8__ {int areanum; } ;
struct TYPE_7__ {int /*<<< orphan*/  numareas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Error (char*,...) ; 
 int AAS_UpdatePortal (int,int) ; 
 int AREACONTENTS_CLUSTERPORTAL ; 
 TYPE_6__ aasworld ; 
 int abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nofaceflood ; 
 int qfalse ; 
 int qtrue ; 

int AAS_FloodClusterAreas_r(int areanum, int clusternum)
{
	aas_area_t *area;
	aas_face_t *face;
	int facenum, i;

	//
	if (areanum <= 0 || areanum >= aasworld.numareas)
	{
		AAS_Error("AAS_FloodClusterAreas_r: areanum out of range\n");
		return qfalse;
	} //end if
	//if the area is already part of a cluster
	if (aasworld.areasettings[areanum].cluster > 0)
	{
		if (aasworld.areasettings[areanum].cluster == clusternum) return qtrue;
		//
		//there's a reachability going from one cluster to another only in one direction
		//
		AAS_Error("cluster %d touched cluster %d at area %d\n",
				clusternum, aasworld.areasettings[areanum].cluster, areanum);
		return qfalse;
	} //end if
	//don't add the cluster portal areas to the clusters
	if (aasworld.areasettings[areanum].contents & AREACONTENTS_CLUSTERPORTAL)
	{
		return AAS_UpdatePortal(areanum, clusternum);
	} //end if
	//set the area cluster number
	aasworld.areasettings[areanum].cluster = clusternum;
	aasworld.areasettings[areanum].clusterareanum =
				aasworld.clusters[clusternum].numareas;
	//the cluster has an extra area
	aasworld.clusters[clusternum].numareas++;

	area = &aasworld.areas[areanum];
	//use area faces to flood into adjacent areas
	if (!nofaceflood)
	{
		for (i = 0; i < area->numfaces; i++)
		{
			facenum = abs(aasworld.faceindex[area->firstface + i]);
			face = &aasworld.faces[facenum];
			if (face->frontarea == areanum)
			{
				if (face->backarea) if (!AAS_FloodClusterAreas_r(face->backarea, clusternum)) return qfalse;
			} //end if
			else
			{
				if (face->frontarea) if (!AAS_FloodClusterAreas_r(face->frontarea, clusternum)) return qfalse;
			} //end else
		} //end for
	} //end if
	//use the reachabilities to flood into other areas
	for (i = 0; i < aasworld.areasettings[areanum].numreachableareas; i++)
	{
		if (!aasworld.reachability[
					aasworld.areasettings[areanum].firstreachablearea + i].areanum)
		{
			continue;
		} //end if
		if (!AAS_FloodClusterAreas_r(aasworld.reachability[
				aasworld.areasettings[areanum].firstreachablearea + i].areanum, clusternum)) return qfalse;
	} //end for
	return qtrue;
}