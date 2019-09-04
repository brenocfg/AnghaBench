#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int areanum; struct TYPE_3__* next_area; } ;
typedef  TYPE_1__ aas_link_t ;

/* Variables and functions */
 scalar_t__ AAS_AreaGrounded (int) ; 
 scalar_t__ AAS_AreaReachability (int) ; 
 scalar_t__ AAS_AreaSwim (int) ; 

int AAS_BestReachableLinkArea(aas_link_t *areas)
{
	aas_link_t *link;

	for (link = areas; link; link = link->next_area)
	{
		if (AAS_AreaGrounded(link->areanum) || AAS_AreaSwim(link->areanum))
		{
			return link->areanum;
		} //end if
	} //end for
	//
	for (link = areas; link; link = link->next_area)
	{
		if (link->areanum) return link->areanum;
		//FIXME: this is a bad idea when the reachability is not yet
		// calculated when the level items are loaded
		if (AAS_AreaReachability(link->areanum))
			return link->areanum;
	} //end for
	return 0;
}