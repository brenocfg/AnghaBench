#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_6__** sataChannel; } ;
struct TYPE_15__ {TYPE_4__* mvChannel; int /*<<< orphan*/  VBus; TYPE_1__ mvSataAdapter; TYPE_5__* VDevices; } ;
struct TYPE_14__ {int* identifyDevice; scalar_t__ lba48Address; scalar_t__ outstandingCommands; } ;
struct TYPE_10__ {int df_on_line; int dDeRealCapacity; int bDeUsable_Mode; int bDeModeSetting; int /*<<< orphan*/ * pVBus; TYPE_6__* mv; } ;
struct TYPE_11__ {TYPE_2__ disk; } ;
struct TYPE_13__ {TYPE_3__ u; int /*<<< orphan*/ * pVBus; } ;
struct TYPE_12__ {int maxPioModeSupported; int maxUltraDmaModeSupported; } ;
typedef  TYPE_5__* PVDevice ;
typedef  size_t MV_U8 ;
typedef  int* MV_U16_PTR ;
typedef  TYPE_6__ MV_SATA_CHANNEL ;
typedef  TYPE_7__ IAL_ADAPTER_T ;

/* Variables and functions */
 int MV_ATA_TRANSFER_PIO_0 ; 
 int MV_ATA_TRANSFER_UDMA_0 ; 
 scalar_t__ MV_TRUE ; 

__attribute__((used)) static void
init_vdev_params(IAL_ADAPTER_T *pAdapter, MV_U8 channel)
{
	PVDevice pVDev = &pAdapter->VDevices[channel];
	MV_SATA_CHANNEL *pMvSataChannel = pAdapter->mvSataAdapter.sataChannel[channel];
	MV_U16_PTR IdentifyData = pMvSataChannel->identifyDevice;

	pMvSataChannel->outstandingCommands = 0;

	pVDev->u.disk.mv         = pMvSataChannel;
	pVDev->u.disk.df_on_line = 1;
	pVDev->u.disk.pVBus      = &pAdapter->VBus;
	pVDev->pVBus             = &pAdapter->VBus;

#ifdef SUPPORT_48BIT_LBA
	if (pMvSataChannel->lba48Address == MV_TRUE)
		pVDev->u.disk.dDeRealCapacity = ((IdentifyData[101]<<16) | IdentifyData[100]) - 1;
	else
#endif
	if(IdentifyData[53] & 1) {
	pVDev->u.disk.dDeRealCapacity = 
	  (((IdentifyData[58]<<16 | IdentifyData[57]) < (IdentifyData[61]<<16 | IdentifyData[60])) ? 
		  (IdentifyData[61]<<16 | IdentifyData[60]) :
				(IdentifyData[58]<<16 | IdentifyData[57])) - 1;
	} else
		pVDev->u.disk.dDeRealCapacity = 
				 (IdentifyData[61]<<16 | IdentifyData[60]) - 1;

	pVDev->u.disk.bDeUsable_Mode = pVDev->u.disk.bDeModeSetting = 
		pAdapter->mvChannel[channel].maxPioModeSupported - MV_ATA_TRANSFER_PIO_0;

	if (pAdapter->mvChannel[channel].maxUltraDmaModeSupported!=0xFF) {
		pVDev->u.disk.bDeUsable_Mode = pVDev->u.disk.bDeModeSetting = 
			pAdapter->mvChannel[channel].maxUltraDmaModeSupported - MV_ATA_TRANSFER_UDMA_0 + 8;
	}
}