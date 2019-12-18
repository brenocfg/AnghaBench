#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mvDmaResponseQueueEntry {int dummy; } ;
struct mvDmaRequestQueueEntry {int dummy; } ;
typedef  int dma_addr_t ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_7__ {size_t adapterId; TYPE_3__** sataChannel; } ;
struct TYPE_10__ {int requestsArrayBaseDmaAlignedAddr; int responsesArrayBaseDmaAlignedAddr; TYPE_2__* mvChannel; TYPE_1__ mvSataAdapter; scalar_t__ responsesArrayBaseAlignedAddr; scalar_t__ requestsArrayBaseAlignedAddr; } ;
struct TYPE_9__ {size_t channelNumber; int requestQueuePciLowAddress; int responseQueuePciLowAddress; struct mvDmaResponseQueueEntry* responseQueue; scalar_t__ responseQueuePciHiAddress; struct mvDmaRequestQueueEntry* requestQueue; scalar_t__ requestQueuePciHiAddress; void* maxReadTransfer; void* lba48Address; } ;
struct TYPE_8__ {int /*<<< orphan*/  online; } ;
typedef  size_t MV_U8 ;
typedef  TYPE_3__ MV_SATA_CHANNEL ;
typedef  TYPE_4__ IAL_ADAPTER_T ;
typedef  size_t HPT_U64 ;

/* Variables and functions */
 int /*<<< orphan*/  KdPrint (char*) ; 
 size_t MV_EDMA_REQUEST_QUEUE_SIZE ; 
 size_t MV_EDMA_RESPONSE_QUEUE_SIZE ; 
 int /*<<< orphan*/  MV_ERROR (char*,size_t,size_t,...) ; 
 void* MV_FALSE ; 
 size_t MV_SATA_CHANNELS_NUM ; 
 int /*<<< orphan*/  MV_TRUE ; 
 TYPE_3__** gMvSataChannels ; 

__attribute__((used)) static int
hptmv_init_channel(IAL_ADAPTER_T *pAdapter, MV_U8 channelNum)
{
	MV_SATA_CHANNEL *pMvSataChannel;
	dma_addr_t    req_dma_addr;
	dma_addr_t    rsp_dma_addr;

	if (channelNum >= MV_SATA_CHANNELS_NUM)
	{
		MV_ERROR("RR18xx[%d]: Bad channelNum=%d",
				 pAdapter->mvSataAdapter.adapterId, channelNum);
		return -1;
	}

	pMvSataChannel = &gMvSataChannels[pAdapter->mvSataAdapter.adapterId][channelNum];
	pAdapter->mvSataAdapter.sataChannel[channelNum] = pMvSataChannel;
	pMvSataChannel->channelNumber = channelNum;
	pMvSataChannel->lba48Address = MV_FALSE;
	pMvSataChannel->maxReadTransfer = MV_FALSE;

	pMvSataChannel->requestQueue = (struct mvDmaRequestQueueEntry *)
								   (pAdapter->requestsArrayBaseAlignedAddr + (channelNum * MV_EDMA_REQUEST_QUEUE_SIZE));
	req_dma_addr = pAdapter->requestsArrayBaseDmaAlignedAddr + (channelNum * MV_EDMA_REQUEST_QUEUE_SIZE);


	KdPrint(("requestQueue addr is 0x%llX", (HPT_U64)(ULONG_PTR)req_dma_addr));

	/* check the 1K alignment of the request queue*/
	if (req_dma_addr & 0x3ff)
	{
		MV_ERROR("RR18xx[%d]: request queue allocated isn't 1 K aligned,"
				 " dma_addr=%llx channel=%d\n", pAdapter->mvSataAdapter.adapterId,
				 (HPT_U64)(ULONG_PTR)req_dma_addr, channelNum);
		return -1;
	}
	pMvSataChannel->requestQueuePciLowAddress = req_dma_addr;
	pMvSataChannel->requestQueuePciHiAddress = 0;
	KdPrint(("RR18xx[%d,%d]: request queue allocated: 0x%p",
			  pAdapter->mvSataAdapter.adapterId, channelNum,
			  pMvSataChannel->requestQueue));
	pMvSataChannel->responseQueue = (struct mvDmaResponseQueueEntry *)
									(pAdapter->responsesArrayBaseAlignedAddr + (channelNum * MV_EDMA_RESPONSE_QUEUE_SIZE));
	rsp_dma_addr = pAdapter->responsesArrayBaseDmaAlignedAddr + (channelNum * MV_EDMA_RESPONSE_QUEUE_SIZE);

	/* check the 256 alignment of the response queue*/
	if (rsp_dma_addr & 0xff)
	{
		MV_ERROR("RR18xx[%d,%d]: response queue allocated isn't 256 byte "
				 "aligned, dma_addr=%llx\n",
				 pAdapter->mvSataAdapter.adapterId, channelNum, (HPT_U64)(ULONG_PTR)rsp_dma_addr);
		return -1;
	}
	pMvSataChannel->responseQueuePciLowAddress = rsp_dma_addr;
	pMvSataChannel->responseQueuePciHiAddress = 0;
	KdPrint(("RR18xx[%d,%d]: response queue allocated: 0x%p",
			  pAdapter->mvSataAdapter.adapterId, channelNum,
			  pMvSataChannel->responseQueue));

	pAdapter->mvChannel[channelNum].online = MV_TRUE;
	return 0;
}