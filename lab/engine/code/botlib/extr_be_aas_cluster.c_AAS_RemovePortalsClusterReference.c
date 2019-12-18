#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numportals; TYPE_1__* portals; } ;
struct TYPE_3__ {int frontcluster; int backcluster; } ;

/* Variables and functions */
 TYPE_2__ aasworld ; 

void AAS_RemovePortalsClusterReference(int clusternum)
{
	int portalnum;

	for (portalnum = 1; portalnum < aasworld.numportals; portalnum++)
	{
		if (aasworld.portals[portalnum].frontcluster == clusternum)
		{
			aasworld.portals[portalnum].frontcluster = 0;
		} //end if
		if (aasworld.portals[portalnum].backcluster == clusternum)
		{
			aasworld.portals[portalnum].backcluster = 0;
		} //end if
	} //end for
}