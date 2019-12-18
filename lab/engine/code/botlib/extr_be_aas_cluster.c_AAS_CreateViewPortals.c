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
struct TYPE_4__ {int numareas; TYPE_1__* areasettings; } ;
struct TYPE_3__ {int contents; } ;

/* Variables and functions */
 int AREACONTENTS_CLUSTERPORTAL ; 
 int AREACONTENTS_VIEWPORTAL ; 
 TYPE_2__ aasworld ; 

void AAS_CreateViewPortals(void)
{
	int i;

	for (i = 1; i < aasworld.numareas; i++)
	{
		if (aasworld.areasettings[i].contents & AREACONTENTS_CLUSTERPORTAL)
		{
			aasworld.areasettings[i].contents |= AREACONTENTS_VIEWPORTAL;
		} //end if
	} //end for
}