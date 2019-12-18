#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
union ccb {TYPE_1__ ccb_h; int /*<<< orphan*/  ccb_adapter; } ;
struct TYPE_9__ {scalar_t__ outstandingCommands; } ;
struct TYPE_8__ {TYPE_3__* pAdapter; } ;
typedef  TYPE_2__* PBUS_DMAMAP ;
typedef  TYPE_3__ IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  Check_Idle_Call (TYPE_3__*) ; 
 scalar_t__ DPC_Request_Nums ; 
 int /*<<< orphan*/  KdPrintI (char*) ; 
 int /*<<< orphan*/  dmamap_put (TYPE_2__*) ; 
 int /*<<< orphan*/  wakeup (TYPE_3__*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
ccb_done(union ccb *ccb)
{
	PBUS_DMAMAP pmap = (PBUS_DMAMAP)ccb->ccb_adapter;
	IAL_ADAPTER_T * pAdapter = pmap->pAdapter;
	KdPrintI(("ccb_done: ccb %p status %x\n", ccb, ccb->ccb_h.status));

	dmamap_put(pmap);
	xpt_done(ccb);

	pAdapter->outstandingCommands--;

	if (pAdapter->outstandingCommands == 0)
	{
		if(DPC_Request_Nums == 0)
			Check_Idle_Call(pAdapter);
		wakeup(pAdapter);
	}
}