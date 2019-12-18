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
struct TYPE_6__ {int areanum; int frontcluster; scalar_t__* clusterareanum; } ;
typedef  TYPE_2__ aas_portal_t ;
struct TYPE_7__ {int numportals; int firstportal; scalar_t__ numareas; scalar_t__ numreachabilityareas; } ;
typedef  TYPE_3__ aas_cluster_t ;
struct TYPE_8__ {int numareas; int* portalindex; TYPE_2__* portals; TYPE_3__* clusters; TYPE_1__* areasettings; } ;
struct TYPE_5__ {int cluster; scalar_t__ clusterareanum; } ;

/* Variables and functions */
 scalar_t__ AAS_AreaReachability (int) ; 
 TYPE_4__ aasworld ; 

void AAS_NumberClusterAreas(int clusternum)
{
	int i, portalnum;
	aas_cluster_t *cluster;
	aas_portal_t *portal;

	aasworld.clusters[clusternum].numareas = 0;
	aasworld.clusters[clusternum].numreachabilityareas = 0;
	//number all areas in this cluster WITH reachabilities
	for (i = 1; i < aasworld.numareas; i++)
	{
		//
		if (aasworld.areasettings[i].cluster != clusternum) continue;
		//
		if (!AAS_AreaReachability(i)) continue;
		//
		aasworld.areasettings[i].clusterareanum = aasworld.clusters[clusternum].numareas;
		//the cluster has an extra area
		aasworld.clusters[clusternum].numareas++;
		aasworld.clusters[clusternum].numreachabilityareas++;
	} //end for
	//number all portals in this cluster WITH reachabilities
	cluster = &aasworld.clusters[clusternum];
	for (i = 0; i < cluster->numportals; i++)
	{
		portalnum = aasworld.portalindex[cluster->firstportal + i];
		portal = &aasworld.portals[portalnum];
		if (!AAS_AreaReachability(portal->areanum)) continue;
		if (portal->frontcluster == clusternum)
		{
			portal->clusterareanum[0] = cluster->numareas++;
			aasworld.clusters[clusternum].numreachabilityareas++;
		} //end if
		else
		{
			portal->clusterareanum[1] = cluster->numareas++;
			aasworld.clusters[clusternum].numreachabilityareas++;
		} //end else
	} //end for
	//number all areas in this cluster WITHOUT reachabilities
	for (i = 1; i < aasworld.numareas; i++)
	{
		//
		if (aasworld.areasettings[i].cluster != clusternum) continue;
		//
		if (AAS_AreaReachability(i)) continue;
		//
		aasworld.areasettings[i].clusterareanum = aasworld.clusters[clusternum].numareas;
		//the cluster has an extra area
		aasworld.clusters[clusternum].numareas++;
	} //end for
	//number all portals in this cluster WITHOUT reachabilities
	cluster = &aasworld.clusters[clusternum];
	for (i = 0; i < cluster->numportals; i++)
	{
		portalnum = aasworld.portalindex[cluster->firstportal + i];
		portal = &aasworld.portals[portalnum];
		if (AAS_AreaReachability(portal->areanum)) continue;
		if (portal->frontcluster == clusternum)
		{
			portal->clusterareanum[0] = cluster->numareas++;
		} //end if
		else
		{
			portal->clusterareanum[1] = cluster->numareas++;
		} //end else
	} //end for
}