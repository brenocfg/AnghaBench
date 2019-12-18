#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int WORD ;
typedef  scalar_t__ UCHAR ;
struct TYPE_23__ {TYPE_8__* mvChannel; } ;
struct TYPE_22__ {int /*<<< orphan*/  writeCacheEnabled; int /*<<< orphan*/  writeCacheSupported; int /*<<< orphan*/  readAheadEnabled; int /*<<< orphan*/  readAheadSupported; } ;
struct TYPE_21__ {scalar_t__ adapterId; TYPE_9__* IALData; } ;
struct TYPE_20__ {size_t channelNumber; int* identifyDevice; scalar_t__ queuedDMA; TYPE_7__* mvSataAdapter; } ;
struct TYPE_14__ {int /*<<< orphan*/  ModelNumber; } ;
struct TYPE_19__ {size_t PathId; int DeviceModeSetting; int Flags; int TCQSupported; int TCQEnabled; int NCQSupported; int NCQEnabled; int /*<<< orphan*/  WriteCacheEnabled; int /*<<< orphan*/  WriteCacheSupported; int /*<<< orphan*/  ReadAheadEnabled; int /*<<< orphan*/  ReadAheadSupported; TYPE_10__ IdentifyData; int /*<<< orphan*/  DeviceType; int /*<<< orphan*/  UsableMode; scalar_t__ ControllerId; scalar_t__ TargetId; } ;
struct TYPE_18__ {int SataCapability; int /*<<< orphan*/  ModelNumber; } ;
struct TYPE_15__ {int bDeUserSelectMode; int bDeModeSetting; int /*<<< orphan*/  df_on_line; int /*<<< orphan*/  bDeUsable_Mode; TYPE_6__* mv; scalar_t__ df_user_mode_set; } ;
struct TYPE_16__ {TYPE_1__ disk; } ;
struct TYPE_17__ {scalar_t__ VDeviceType; scalar_t__ vf_bootmark; scalar_t__ vf_bootable; TYPE_2__ u; } ;
typedef  TYPE_3__* PVDevice ;
typedef  TYPE_4__* PIDENTIFY_DATA ;
typedef  TYPE_5__* PDEVICE_INFO ;
typedef  TYPE_6__ MV_SATA_CHANNEL ;
typedef  TYPE_7__ MV_SATA_ADAPTER ;
typedef  TYPE_8__ MV_CHANNEL ;
typedef  int /*<<< orphan*/  IDENTIFY_DATA2 ;
typedef  TYPE_9__ IAL_ADAPTER_T ;

/* Variables and functions */
 int DEVICE_FLAG_BOOTDISK ; 
 int DEVICE_FLAG_BOOTMARK ; 
 int DEVICE_FLAG_DISABLED ; 
 int DEVICE_FLAG_IS_SPARE ; 
 int DEVICE_FLAG_SATA ; 
 int IDEN_MODEL_OFFSET ; 
 size_t IDEN_SATA_CAPABILITIES ; 
 size_t IDEN_SUPPORTED_COMMANDS2 ; 
 scalar_t__ MV_EDMA_MODE_NATIVE_QUEUING ; 
 scalar_t__ MV_EDMA_MODE_QUEUED ; 
 scalar_t__ MV_SATA_GEN_2 (TYPE_7__*) ; 
 int /*<<< orphan*/  PDT_HARDDISK ; 
 scalar_t__ VD_SPARE ; 
 int /*<<< orphan*/  memcpy (TYPE_10__*,int*,int) ; 
 int shortswap (int) ; 

__attribute__((used)) static int get_disk_info(PVDevice pVDevice, PDEVICE_INFO pDiskInfo)
{
	MV_SATA_ADAPTER *pSataAdapter;
	MV_SATA_CHANNEL *pSataChannel;
	IAL_ADAPTER_T   *pAdapter;
	MV_CHANNEL		*channelInfo;
	char *p;
	int i;

	/* device location */
	pSataChannel = pVDevice->u.disk.mv;
	if(pSataChannel == NULL)	return -1;	
	pDiskInfo->TargetId = 0;
	pSataAdapter = pSataChannel->mvSataAdapter;
	if(pSataAdapter == NULL)	return -1;

	pAdapter = pSataAdapter->IALData;

	pDiskInfo->PathId = pSataChannel->channelNumber;
	pDiskInfo->ControllerId = (UCHAR)pSataAdapter->adapterId;

/*GUI uses DeviceModeSetting to display to users
(1) if users select a mode, GUI/BIOS should display that mode.
(2) if SATA/150, GUI/BIOS should display 150 if case (1) isn't satisfied.
(3) display real mode if case (1)&&(2) not satisfied.
*/
	if (pVDevice->u.disk.df_user_mode_set)
		pDiskInfo->DeviceModeSetting = pVDevice->u.disk.bDeUserSelectMode;
	else if (((((PIDENTIFY_DATA)pVDevice->u.disk.mv->identifyDevice)->SataCapability) & 3)==2)
		pDiskInfo->DeviceModeSetting = 15;
	else {
		p = (char *)&((PIDENTIFY_DATA)pVDevice->u.disk.mv->identifyDevice)->ModelNumber;
		if (*(WORD*)p==(0x5354) /*'ST'*/ &&
			(*(WORD*)(p+8)==(0x4153)/*'AS'*/ || (p[8]=='A' && p[11]=='S')))
			pDiskInfo->DeviceModeSetting = 15;
		else
			pDiskInfo->DeviceModeSetting = pVDevice->u.disk.bDeModeSetting;
	}
		
	pDiskInfo->UsableMode = pVDevice->u.disk.bDeUsable_Mode;

	pDiskInfo->DeviceType = PDT_HARDDISK;

	pDiskInfo->Flags = 0x0;

	/* device is disabled */
	if(!pVDevice->u.disk.df_on_line)
		pDiskInfo->Flags |= DEVICE_FLAG_DISABLED;

	/* disk has a active partition */
	if(pVDevice->vf_bootable)
		pDiskInfo->Flags |= DEVICE_FLAG_BOOTDISK;

	/* disk has boot mark set */
	if(pVDevice->vf_bootmark)
		pDiskInfo->Flags |= DEVICE_FLAG_BOOTMARK;

	pDiskInfo->Flags |= DEVICE_FLAG_SATA;

	/* is a spare disk */
	if(pVDevice->VDeviceType == VD_SPARE)
		pDiskInfo->Flags |= DEVICE_FLAG_IS_SPARE;

	memcpy(&(pDiskInfo->IdentifyData), (pSataChannel->identifyDevice), sizeof(IDENTIFY_DATA2));
	p = (char *)&pDiskInfo->IdentifyData.ModelNumber;
	for (i = 0; i < 20; i++)
		((WORD*)p)[i] = shortswap(pSataChannel->identifyDevice[IDEN_MODEL_OFFSET+i]);
	p[39] = '\0';

	channelInfo = &pAdapter->mvChannel[pSataChannel->channelNumber];
	pDiskInfo->ReadAheadSupported = channelInfo->readAheadSupported;
	pDiskInfo->ReadAheadEnabled = channelInfo->readAheadEnabled;
	pDiskInfo->WriteCacheSupported = channelInfo->writeCacheSupported;
	pDiskInfo->WriteCacheEnabled = channelInfo->writeCacheEnabled;
	pDiskInfo->TCQSupported = (pSataChannel->identifyDevice[IDEN_SUPPORTED_COMMANDS2] & (0x2))!=0;
	pDiskInfo->TCQEnabled = pSataChannel->queuedDMA==MV_EDMA_MODE_QUEUED;
	pDiskInfo->NCQSupported = MV_SATA_GEN_2(pSataAdapter) &&
		(pSataChannel->identifyDevice[IDEN_SATA_CAPABILITIES] & (0x0100));
	pDiskInfo->NCQEnabled = pSataChannel->queuedDMA==MV_EDMA_MODE_NATIVE_QUEUING;
	return 0;
}