#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG_PTR ;
struct TYPE_4__ {int /*<<< orphan*/  adapterId; } ;
struct TYPE_5__ {int requestsArrayBaseDmaAddr; int requestsArrayBaseDmaAlignedAddr; int responsesArrayBaseDmaAddr; int responsesArrayBaseDmaAlignedAddr; int /*<<< orphan*/ * responsesArrayBaseAddr; int /*<<< orphan*/ * requestsArrayBaseAddr; TYPE_1__ mvSataAdapter; int /*<<< orphan*/ * responsesArrayBaseAlignedAddr; int /*<<< orphan*/ * requestsArrayBaseAlignedAddr; } ;
typedef  int /*<<< orphan*/  MV_U8 ;
typedef  TYPE_2__ IAL_ADAPTER_T ;

/* Variables and functions */
 int MV_EDMA_REQUEST_QUEUE_SIZE ; 
 int MV_EDMA_RESPONSE_QUEUE_SIZE ; 
 int /*<<< orphan*/  MV_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  REQUESTS_ARRAY_SIZE ; 
 int /*<<< orphan*/  RESPONSES_ARRAY_SIZE ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ contigmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long) ; 
 void* fOsPhysicalAddress (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
hptmv_allocate_edma_queues(IAL_ADAPTER_T *pAdapter)
{
	pAdapter->requestsArrayBaseAddr = (MV_U8 *)contigmalloc(REQUESTS_ARRAY_SIZE, 
			M_DEVBUF, M_NOWAIT, 0, 0xffffffff, PAGE_SIZE, 0ul);
	if (pAdapter->requestsArrayBaseAddr == NULL)
	{
		MV_ERROR("RR18xx[%d]: Failed to allocate memory for EDMA request"
				 " queues\n", pAdapter->mvSataAdapter.adapterId);
		return -1;
	}
	pAdapter->requestsArrayBaseDmaAddr = fOsPhysicalAddress(pAdapter->requestsArrayBaseAddr);
	pAdapter->requestsArrayBaseAlignedAddr = pAdapter->requestsArrayBaseAddr;
	pAdapter->requestsArrayBaseAlignedAddr += MV_EDMA_REQUEST_QUEUE_SIZE;
	pAdapter->requestsArrayBaseAlignedAddr  = (MV_U8 *)
		(((ULONG_PTR)pAdapter->requestsArrayBaseAlignedAddr) & ~(ULONG_PTR)(MV_EDMA_REQUEST_QUEUE_SIZE - 1));
	pAdapter->requestsArrayBaseDmaAlignedAddr = pAdapter->requestsArrayBaseDmaAddr; 
	pAdapter->requestsArrayBaseDmaAlignedAddr += MV_EDMA_REQUEST_QUEUE_SIZE;
	pAdapter->requestsArrayBaseDmaAlignedAddr &= ~(ULONG_PTR)(MV_EDMA_REQUEST_QUEUE_SIZE - 1);

	if ((pAdapter->requestsArrayBaseDmaAlignedAddr - pAdapter->requestsArrayBaseDmaAddr) != 
		(pAdapter->requestsArrayBaseAlignedAddr - pAdapter->requestsArrayBaseAddr))
	{
		MV_ERROR("RR18xx[%d]: Error in Request Quueues Alignment\n",
				 pAdapter->mvSataAdapter.adapterId);
		contigfree(pAdapter->requestsArrayBaseAddr, REQUESTS_ARRAY_SIZE, M_DEVBUF);
		return -1;
	}
	/* response queues */
	pAdapter->responsesArrayBaseAddr = (MV_U8 *)contigmalloc(RESPONSES_ARRAY_SIZE, 
			M_DEVBUF, M_NOWAIT, 0, 0xffffffff, PAGE_SIZE, 0ul);
	if (pAdapter->responsesArrayBaseAddr == NULL)
	{
		MV_ERROR("RR18xx[%d]: Failed to allocate memory for EDMA response"
				 " queues\n", pAdapter->mvSataAdapter.adapterId);
		contigfree(pAdapter->requestsArrayBaseAddr, RESPONSES_ARRAY_SIZE, M_DEVBUF);
		return -1;
	}
	pAdapter->responsesArrayBaseDmaAddr = fOsPhysicalAddress(pAdapter->responsesArrayBaseAddr);
	pAdapter->responsesArrayBaseAlignedAddr = pAdapter->responsesArrayBaseAddr;
	pAdapter->responsesArrayBaseAlignedAddr += MV_EDMA_RESPONSE_QUEUE_SIZE;
	pAdapter->responsesArrayBaseAlignedAddr  = (MV_U8 *)
		(((ULONG_PTR)pAdapter->responsesArrayBaseAlignedAddr) & ~(ULONG_PTR)(MV_EDMA_RESPONSE_QUEUE_SIZE - 1));
	pAdapter->responsesArrayBaseDmaAlignedAddr = pAdapter->responsesArrayBaseDmaAddr; 
	pAdapter->responsesArrayBaseDmaAlignedAddr += MV_EDMA_RESPONSE_QUEUE_SIZE;
	pAdapter->responsesArrayBaseDmaAlignedAddr &= ~(ULONG_PTR)(MV_EDMA_RESPONSE_QUEUE_SIZE - 1);

	if ((pAdapter->responsesArrayBaseDmaAlignedAddr - pAdapter->responsesArrayBaseDmaAddr) != 
		(pAdapter->responsesArrayBaseAlignedAddr - pAdapter->responsesArrayBaseAddr))
	{
		MV_ERROR("RR18xx[%d]: Error in Response Queues Alignment\n",
				 pAdapter->mvSataAdapter.adapterId);
		contigfree(pAdapter->requestsArrayBaseAddr, REQUESTS_ARRAY_SIZE, M_DEVBUF);
		contigfree(pAdapter->responsesArrayBaseAddr, RESPONSES_ARRAY_SIZE, M_DEVBUF);
		return -1;
	}
	return 0;
}