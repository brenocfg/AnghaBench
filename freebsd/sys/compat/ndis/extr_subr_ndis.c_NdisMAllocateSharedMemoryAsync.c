#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ndis_allocwork {int /*<<< orphan*/ * na_iw; void* na_ctx; int /*<<< orphan*/  na_len; int /*<<< orphan*/  na_cached; } ;
typedef  int /*<<< orphan*/  ndis_status ;
struct TYPE_4__ {int /*<<< orphan*/  nmb_deviceobj; } ;
typedef  TYPE_1__ ndis_miniport_block ;
typedef  TYPE_1__* ndis_handle ;
typedef  scalar_t__ io_workitem_func ;
typedef  int /*<<< orphan*/  io_workitem ;
typedef  int /*<<< orphan*/  funcptr ;

/* Variables and functions */
 int /*<<< orphan*/ * IoAllocateWorkItem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoQueueWorkItem (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct ndis_allocwork*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  NDIS_STATUS_FAILURE ; 
 int /*<<< orphan*/  NDIS_STATUS_PENDING ; 
 int /*<<< orphan*/  WORKQUEUE_DELAYED ; 
 struct ndis_allocwork* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ndis_asyncmem_complete ; 
 scalar_t__ ndis_findwrap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ndis_status
NdisMAllocateSharedMemoryAsync(ndis_handle adapter, uint32_t len,
    uint8_t cached, void *ctx)
{
	ndis_miniport_block	*block;
	struct ndis_allocwork	*w;
	io_workitem		*iw;
	io_workitem_func	ifw;

	if (adapter == NULL)
		return (NDIS_STATUS_FAILURE);

	block = adapter;

	iw = IoAllocateWorkItem(block->nmb_deviceobj);
	if (iw == NULL)
		return (NDIS_STATUS_FAILURE);

	w = malloc(sizeof(struct ndis_allocwork), M_TEMP, M_NOWAIT);

	if (w == NULL)
		return (NDIS_STATUS_FAILURE);

	w->na_cached = cached;
	w->na_len = len;
	w->na_ctx = ctx;
	w->na_iw = iw;

	ifw = (io_workitem_func)ndis_findwrap((funcptr)ndis_asyncmem_complete);
	IoQueueWorkItem(iw, ifw, WORKQUEUE_DELAYED, w);

	return (NDIS_STATUS_PENDING);
}