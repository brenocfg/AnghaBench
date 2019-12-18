#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* VDevices; struct TYPE_6__* next; } ;
struct TYPE_5__ {scalar_t__ VDeviceType; struct TYPE_5__* pParent; } ;
typedef  TYPE_1__* PVDevice ;
typedef  TYPE_2__ IAL_ADAPTER_T ;
typedef  scalar_t__ DEVICEID ;

/* Variables and functions */
 scalar_t__ INVALID_DEVICEID ; 
 int MV_SATA_CHANNELS_NUM ; 
 scalar_t__ VDEV_TO_ID (TYPE_1__*) ; 
 scalar_t__ VD_SPARE ; 
 TYPE_2__* gIal_Adapter ; 

int hpt_get_logical_devices(DEVICEID * pIds, int nMaxCount)
{
	int count = 0;
	int	i,j;
	PVDevice pPhysical, pLogical;
	IAL_ADAPTER_T    *pAdapTemp;

	for(i = 0; i < nMaxCount; i++)
		pIds[i] = INVALID_DEVICEID;

	/* append the arrays not registered on VBus */
	for (pAdapTemp = gIal_Adapter; pAdapTemp; pAdapTemp = pAdapTemp->next) {
		for(i = 0; i < MV_SATA_CHANNELS_NUM; i++)
		{
			pPhysical = &pAdapTemp->VDevices[i];
			pLogical = pPhysical;
			
			while (pLogical->pParent) pLogical = pLogical->pParent;
			if (pLogical->VDeviceType==VD_SPARE)
				continue;
			
			for (j=0; j<count; j++)
				if (pIds[j]==VDEV_TO_ID(pLogical)) goto next;
			pIds[count++] = VDEV_TO_ID(pLogical);
			if (count>=nMaxCount) goto done;
			next:;
		}
	}

done:
	return count;
}