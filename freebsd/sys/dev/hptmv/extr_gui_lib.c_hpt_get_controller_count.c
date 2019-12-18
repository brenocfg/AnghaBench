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
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ IAL_ADAPTER_T ;

/* Variables and functions */
 TYPE_1__* gIal_Adapter ; 

int hpt_get_controller_count(void)
{
	IAL_ADAPTER_T    *pAdapTemp = gIal_Adapter;
	int iControllerCount = 0;
	
	while(pAdapTemp != NULL)
	{		 
		iControllerCount++;
		pAdapTemp = pAdapTemp->next;
	}
	
	return iControllerCount;
}