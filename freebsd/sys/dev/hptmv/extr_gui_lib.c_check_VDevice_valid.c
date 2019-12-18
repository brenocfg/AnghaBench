#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* next; int /*<<< orphan*/  VBus; TYPE_3__* VDevices; } ;
struct TYPE_8__ {scalar_t__ dArStamp; } ;
struct TYPE_9__ {TYPE_1__ array; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
typedef  TYPE_3__* PVDevice ;
typedef  int /*<<< orphan*/ * PVBus ;
typedef  TYPE_4__ IAL_ADAPTER_T ;

/* Variables and functions */
 TYPE_3__* ArrayTables (int) ; 
 int MAX_ARRAY_PER_VBUS ; 
 int MV_SATA_CHANNELS_NUM ; 
 TYPE_4__* gIal_Adapter ; 

int
check_VDevice_valid(PVDevice p)
{
	int i;
	PVDevice pVDevice;
	PVBus    _vbus_p;
	IAL_ADAPTER_T *pAdapter = gIal_Adapter;
	
	while(pAdapter != NULL)
	{
		for (i = 0; i < MV_SATA_CHANNELS_NUM; i++)
			if(&(pAdapter->VDevices[i]) == p)  return 0;
		pAdapter = pAdapter->next;
	}

#ifdef SUPPORT_ARRAY
	pAdapter = gIal_Adapter;
	while(pAdapter != NULL)
	{
		_vbus_p = &pAdapter->VBus;
		for (i=0;i<MAX_ARRAY_PER_VBUS;i++) 
		{
			pVDevice=ArrayTables(i);
			if ((pVDevice->u.array.dArStamp != 0) && (pVDevice == p))
				return 0;
		}
		pAdapter = pAdapter->next;
	}
#endif

	return -1;
}