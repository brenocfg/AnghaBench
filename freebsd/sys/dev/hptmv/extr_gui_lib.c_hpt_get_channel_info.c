#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * VDevices; TYPE_1__* mvChannel; struct TYPE_8__* next; } ;
struct TYPE_7__ {void** Devices; scalar_t__ ControlPort; scalar_t__ IoPort; } ;
struct TYPE_6__ {scalar_t__ online; } ;
typedef  TYPE_2__* PCHANNEL_INFO ;
typedef  TYPE_3__ IAL_ADAPTER_T ;
typedef  void* DEVICEID ;

/* Variables and functions */
 scalar_t__ INVALID_DEVICEID ; 
 scalar_t__ MV_TRUE ; 
 void* VDEV_TO_ID (int /*<<< orphan*/ *) ; 
 TYPE_3__* gIal_Adapter ; 

int hpt_get_channel_info(int id, int bus, PCHANNEL_INFO pInfo)
{
	IAL_ADAPTER_T    *pAdapTemp = gIal_Adapter;
	int i,iControllerCount = 0;

	while(pAdapTemp != NULL)
	{
		if (iControllerCount++==id) 
			goto found;
		pAdapTemp = pAdapTemp->next;
	}
	return -1;

found:
	
	pInfo->IoPort = 0;
	pInfo->ControlPort = 0;
	
	for (i=0; i<2 ;i++)
	{
		pInfo->Devices[i] = (DEVICEID)INVALID_DEVICEID;
	}

	if (pAdapTemp->mvChannel[bus].online == MV_TRUE)
		pInfo->Devices[0] = VDEV_TO_ID(&pAdapTemp->VDevices[bus]);
	else
		pInfo->Devices[0] = (DEVICEID)INVALID_DEVICEID;

	return 0;
	

}