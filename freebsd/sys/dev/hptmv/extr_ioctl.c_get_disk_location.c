#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* VDevices; struct TYPE_7__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  disk; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/ * PDevice ;
typedef  TYPE_3__ IAL_ADAPTER_T ;

/* Variables and functions */
 int MV_SATA_CHANNELS_NUM ; 
 TYPE_3__* gIal_Adapter ; 

__attribute__((used)) static void
get_disk_location(PDevice pDev, int *controller, int *channel)
{
	IAL_ADAPTER_T *pAdapTemp;
	int i, j;

	*controller = *channel = 0;

	for (i=1, pAdapTemp = gIal_Adapter; pAdapTemp; pAdapTemp = pAdapTemp->next, i++) {
		for (j=0; j<MV_SATA_CHANNELS_NUM; j++) {
			if (pDev == &pAdapTemp->VDevices[j].u.disk) {
				*controller = i;
				*channel = j;
				return;
			}
		}
	}
}