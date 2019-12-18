#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* mvChannel; } ;
struct TYPE_15__ {int /*<<< orphan*/  adapterId; scalar_t__ IALData; } ;
struct TYPE_14__ {int /*<<< orphan*/  maxUltraDmaModeSupported; int /*<<< orphan*/  maxPioModeSupported; } ;
typedef  size_t MV_U8 ;
typedef  TYPE_2__ MV_SATA_ADAPTER ;
typedef  TYPE_3__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  MV_ATA_SET_FEATURES_TRANSFER ; 
 int /*<<< orphan*/  MV_ATA_TRANSFER_PIO_SLOW ; 
 int /*<<< orphan*/  MV_ERROR (char*,size_t,...) ; 
 scalar_t__ MV_FALSE ; 
 int /*<<< orphan*/  MV_FLUSH_TYPE_CALLBACK ; 
 int /*<<< orphan*/  MV_NON_UDMA_PROTOCOL_NON_DATA ; 
 int /*<<< orphan*/  hptmv_free_channel (TYPE_3__*,size_t) ; 
 scalar_t__ mvSataChannelHardReset (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  mvSataDisableChannelDma (TYPE_2__*,size_t) ; 
 scalar_t__ mvSataEnableChannelDma (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  mvSataFlushDmaQueue (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ mvSataIsStorageDeviceConnected (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  mvStorageDevATAExecuteNonUDMACommand (TYPE_2__*,size_t,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mvStorageDevATASetFeatures (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mvStorageDevATASoftResetDevice (TYPE_2__*,size_t) ; 

int
MvSataResetChannel(MV_SATA_ADAPTER *pMvSataAdapter, MV_U8 channel)
{
	IAL_ADAPTER_T   *pAdapter = (IAL_ADAPTER_T *)pMvSataAdapter->IALData;

	mvSataDisableChannelDma(pMvSataAdapter, channel);
	/* Flush pending commands */
	mvSataFlushDmaQueue (pMvSataAdapter, channel, MV_FLUSH_TYPE_CALLBACK);

	/* Software reset channel */
	if (mvStorageDevATASoftResetDevice(pMvSataAdapter, channel) == MV_FALSE)
	{
		MV_ERROR("RR18xx [%d,%d]: failed to perform Software reset\n",
				 pMvSataAdapter->adapterId, channel);
		hptmv_free_channel(pAdapter, channel);
		return -1;
	}
	
	/* Hardware reset channel */
	if (mvSataChannelHardReset(pMvSataAdapter, channel)== MV_FALSE)
	{
		MV_ERROR("RR18xx [%d,%d] Failed to Hard reser the SATA channel\n",
				 pMvSataAdapter->adapterId, channel);
		hptmv_free_channel(pAdapter, channel);
		return -1;
	}

	if (mvSataIsStorageDeviceConnected(pMvSataAdapter, channel) == MV_FALSE)
	{
		 MV_ERROR("RR18xx [%d,%d] Failed to Connect Device\n",
				 pMvSataAdapter->adapterId, channel);
		hptmv_free_channel(pAdapter, channel);
		return -1;
	}else
	{
		MV_ERROR("channel %d: perform recalibrate command", channel);
		if (!mvStorageDevATAExecuteNonUDMACommand(pMvSataAdapter, channel,
								MV_NON_UDMA_PROTOCOL_NON_DATA,
								MV_FALSE,
								NULL,	 /* pBuffer*/
								0,		 /* count  */
								0,		/*features*/
										/* sectorCount */
								0,
								0,	/* lbaLow */
								0,	/* lbaMid */
									/* lbaHigh */
								0,
								0,		/* device */
										/* command */
								0x10))
			MV_ERROR("channel %d: recalibrate failed", channel);
		
		/* Set transfer mode */
		if((mvStorageDevATASetFeatures(pMvSataAdapter, channel,
						MV_ATA_SET_FEATURES_TRANSFER,
						MV_ATA_TRANSFER_PIO_SLOW, 0, 0, 0) == MV_FALSE) || 
			(mvStorageDevATASetFeatures(pMvSataAdapter, channel,
						MV_ATA_SET_FEATURES_TRANSFER,
						pAdapter->mvChannel[channel].maxPioModeSupported, 0, 0, 0) == MV_FALSE) ||
			(mvStorageDevATASetFeatures(pMvSataAdapter, channel,
						MV_ATA_SET_FEATURES_TRANSFER,
						pAdapter->mvChannel[channel].maxUltraDmaModeSupported, 0, 0, 0) == MV_FALSE) )
		{
			MV_ERROR("channel %d: Set Features failed", channel);
			hptmv_free_channel(pAdapter, channel);
			return -1;
		}
		/* Enable EDMA */
		if (mvSataEnableChannelDma(pMvSataAdapter, channel) == MV_FALSE)
		{
			MV_ERROR("Failed to enable DMA, channel=%d", channel);
			hptmv_free_channel(pAdapter, channel);
			return -1;
		}
	}
	return 0;
}