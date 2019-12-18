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
struct TYPE_6__ {TYPE_2__* first; } ;
typedef  TYPE_1__ aas_reversedreachability_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ aas_reversedlink_t ;
struct TYPE_8__ {size_t areanum; } ;
typedef  TYPE_3__ aas_portal_t ;
struct TYPE_9__ {int numreachableareas; } ;
typedef  TYPE_4__ aas_areasettings_t ;
struct TYPE_10__ {int*** areatraveltimes; TYPE_4__* areasettings; TYPE_1__* reversedreachability; TYPE_3__* portals; } ;

/* Variables and functions */
 TYPE_5__ aasworld ; 

int AAS_PortalMaxTravelTime(int portalnum)
{
	int l, n, t, maxt;
	aas_portal_t *portal;
	aas_reversedreachability_t *revreach;
	aas_reversedlink_t *revlink;
	aas_areasettings_t *settings;

	portal = &aasworld.portals[portalnum];
	//reversed reachabilities of this portal area
	revreach = &aasworld.reversedreachability[portal->areanum];
	//settings of the portal area
	settings = &aasworld.areasettings[portal->areanum];
	//
	maxt = 0;
	for (l = 0; l < settings->numreachableareas; l++)
	{
		for (n = 0, revlink = revreach->first; revlink; revlink = revlink->next, n++)
		{
			t = aasworld.areatraveltimes[portal->areanum][l][n];
			if (t > maxt)
			{
				maxt = t;
			} //end if
		} //end for
	} //end for
	return maxt;
}