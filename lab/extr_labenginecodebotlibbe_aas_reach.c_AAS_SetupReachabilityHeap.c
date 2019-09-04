#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ aas_lreachability_t ;

/* Variables and functions */
 int AAS_MAX_REACHABILITYSIZE ; 
 scalar_t__ GetClearedMemory (int) ; 
 TYPE_1__* nextreachability ; 
 scalar_t__ numlreachabilities ; 
 TYPE_1__* reachabilityheap ; 

void AAS_SetupReachabilityHeap(void)
{
	int i;

	reachabilityheap = (aas_lreachability_t *) GetClearedMemory(
						AAS_MAX_REACHABILITYSIZE * sizeof(aas_lreachability_t));
	for (i = 0; i < AAS_MAX_REACHABILITYSIZE-1; i++)
	{
		reachabilityheap[i].next = &reachabilityheap[i+1];
	} //end for
	reachabilityheap[AAS_MAX_REACHABILITYSIZE-1].next = NULL;
	nextreachability = reachabilityheap;
	numlreachabilities = 0;
}