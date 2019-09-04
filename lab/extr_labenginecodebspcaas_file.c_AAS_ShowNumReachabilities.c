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
struct TYPE_4__ {int reachabilitysize; TYPE_1__* reachability; } ;
struct TYPE_3__ {int traveltype; } ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*,int,char*) ; 
 int TRAVELTYPE_MASK ; 
 TYPE_2__ aasworld ; 

void AAS_ShowNumReachabilities(int tt, char *name)
{
	int i, num;

	num = 0;
	for (i = 0; i < aasworld.reachabilitysize; i++)
	{
		if ((aasworld.reachability[i].traveltype & TRAVELTYPE_MASK) == tt)
			num++;
	} //end for
	Log_Print("%6d %s\n", num, name);
}