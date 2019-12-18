#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  adapterIoBaseAddress; int /*<<< orphan*/ ** sataChannel; } ;
struct TYPE_22__ {TYPE_6__* VDevices; TYPE_7__ mvSataAdapter; scalar_t__ beeping; } ;
struct TYPE_15__ {scalar_t__ dDeRealCapacity; scalar_t__ df_removable_drive; scalar_t__ df_atapi; } ;
struct TYPE_16__ {TYPE_1__ disk; } ;
struct TYPE_20__ {size_t VDeviceType; int vf_online; TYPE_5__* pParent; int /*<<< orphan*/  pfnDeviceFailed; int /*<<< orphan*/  pfnSendCommand; TYPE_2__ u; scalar_t__ VDeviceCapacity; } ;
struct TYPE_17__ {int bArnMember; int /*<<< orphan*/ ** pMember; } ;
struct TYPE_18__ {TYPE_3__ array; } ;
struct TYPE_19__ {TYPE_4__ u; } ;
typedef  TYPE_6__* PVDevice ;
typedef  size_t MV_U8 ;
typedef  int /*<<< orphan*/  MV_SATA_CHANNEL ;
typedef  TYPE_7__ MV_SATA_ADAPTER ;
typedef  TYPE_8__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  BeepOff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_DEVICE_PLUGGED ; 
 int /*<<< orphan*/  RegisterVDevice (TYPE_6__*) ; 
 scalar_t__ SAVE_FOR_RAID_INFO ; 
 size_t VD_ATAPI ; 
 size_t VD_REMOVABLE ; 
 size_t VD_SINGLE_DISK ; 
 int /*<<< orphan*/  fCheckBootable (TYPE_6__*) ; 
 int /*<<< orphan*/  fNotifyGUI (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  failDevice (TYPE_6__*) ; 
 int /*<<< orphan*/  init_vdev_params (TYPE_8__*,size_t) ; 
 int /*<<< orphan*/ * pfnDeviceFailed ; 
 int /*<<< orphan*/ * pfnSendCommand ; 

__attribute__((used)) static void device_change(IAL_ADAPTER_T *pAdapter , MV_U8 channelIndex, int plugged)
{
	PVDevice pVDev;
	MV_SATA_ADAPTER  *pMvSataAdapter = &pAdapter->mvSataAdapter;
	MV_SATA_CHANNEL  *pMvSataChannel = pMvSataAdapter->sataChannel[channelIndex];
	
	if (!pMvSataChannel) return;

	if (plugged)
	{
		pVDev = &(pAdapter->VDevices[channelIndex]);
		init_vdev_params(pAdapter, channelIndex);

		pVDev->VDeviceType = pVDev->u.disk.df_atapi? VD_ATAPI : 
			pVDev->u.disk.df_removable_drive? VD_REMOVABLE : VD_SINGLE_DISK;

		pVDev->VDeviceCapacity = pVDev->u.disk.dDeRealCapacity-SAVE_FOR_RAID_INFO;
		pVDev->pfnSendCommand = pfnSendCommand[pVDev->VDeviceType];
		pVDev->pfnDeviceFailed = pfnDeviceFailed[pVDev->VDeviceType];
		pVDev->vf_online = 1;

#ifdef SUPPORT_ARRAY
		if(pVDev->pParent) 
		{
			int iMember;
			for(iMember = 0; iMember < 	pVDev->pParent->u.array.bArnMember; iMember++)
				if((PVDevice)pVDev->pParent->u.array.pMember[iMember] == pVDev)
					pVDev->pParent->u.array.pMember[iMember] = NULL;
			pVDev->pParent = NULL;
		}
#endif
		fNotifyGUI(ET_DEVICE_PLUGGED,pVDev);
		fCheckBootable(pVDev);
		RegisterVDevice(pVDev);

#ifndef FOR_DEMO
		if (pAdapter->beeping) {
			pAdapter->beeping = 0;
			BeepOff(pAdapter->mvSataAdapter.adapterIoBaseAddress);
		}
#endif

	}
	else
	{
		pVDev  = &(pAdapter->VDevices[channelIndex]);
		failDevice(pVDev);
	}
}