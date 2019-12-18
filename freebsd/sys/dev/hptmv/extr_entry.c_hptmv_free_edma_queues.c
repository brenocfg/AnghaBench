#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  responsesArrayBaseAddr; int /*<<< orphan*/  requestsArrayBaseAddr; } ;
typedef  TYPE_1__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  REQUESTS_ARRAY_SIZE ; 
 int /*<<< orphan*/  RESPONSES_ARRAY_SIZE ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hptmv_free_edma_queues(IAL_ADAPTER_T *pAdapter)
{
	contigfree(pAdapter->requestsArrayBaseAddr, REQUESTS_ARRAY_SIZE, M_DEVBUF);
	contigfree(pAdapter->responsesArrayBaseAddr, RESPONSES_ARRAY_SIZE, M_DEVBUF);
}