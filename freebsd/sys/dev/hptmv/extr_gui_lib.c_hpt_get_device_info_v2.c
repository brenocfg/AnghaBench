#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  device; int /*<<< orphan*/  array; } ;
struct TYPE_15__ {int lo32; int hi32; } ;
struct TYPE_18__ {TYPE_4__ u; TYPE_3__ Capacity; void* ParentArray; int /*<<< orphan*/  Type; } ;
struct TYPE_13__ {int dDeRealCapacity; } ;
struct TYPE_14__ {TYPE_1__ disk; } ;
struct TYPE_17__ {int VDeviceCapacity; TYPE_2__ u; scalar_t__ pParent; } ;
typedef  TYPE_5__* PVDevice ;
typedef  TYPE_6__* PLOGICAL_DEVICE_INFO_V2 ;
typedef  int /*<<< orphan*/  LBA_T ;
typedef  scalar_t__ DEVICEID ;

/* Variables and functions */
 TYPE_5__* ID_TO_VDEV (scalar_t__) ; 
 void* INVALID_DEVICEID ; 
 int /*<<< orphan*/  LDT_ARRAY ; 
 int /*<<< orphan*/  LDT_DEVICE ; 
 void* VDEV_TO_ID (scalar_t__) ; 
 scalar_t__ check_VDevice_valid (TYPE_5__*) ; 
 int /*<<< orphan*/  get_array_info_v2 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int get_disk_info (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mIsArray (TYPE_5__*) ; 

int hpt_get_device_info_v2(DEVICEID id, PLOGICAL_DEVICE_INFO_V2 pInfo)
{
	PVDevice pVDevice = ID_TO_VDEV(id);

	if((id == 0) || check_VDevice_valid(pVDevice))
		return -1;

#ifdef SUPPORT_ARRAY
	if (mIsArray(pVDevice)) {
		pInfo->Type = LDT_ARRAY;
		pInfo->Capacity.lo32 = pVDevice->VDeviceCapacity;
		pInfo->Capacity.hi32 = sizeof(LBA_T)>4? (pVDevice->VDeviceCapacity>>32) : 0;
		pInfo->ParentArray = VDEV_TO_ID(pVDevice->pParent);
		get_array_info_v2(pVDevice, &pInfo->u.array);
	return 0;
}
#endif

	pInfo->Type = LDT_DEVICE;
	pInfo->ParentArray = pVDevice->pParent? VDEV_TO_ID(pVDevice->pParent) : INVALID_DEVICEID;
	/* report real capacity to be compatible with old arrays */
	pInfo->Capacity.lo32 = pVDevice->u.disk.dDeRealCapacity;
	pInfo->Capacity.hi32 = 0;
	return get_disk_info(pVDevice, &pInfo->u.device);
}