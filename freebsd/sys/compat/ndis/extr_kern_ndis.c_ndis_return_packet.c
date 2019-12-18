#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ndis_softc {TYPE_2__* ndis_block; } ;
struct TYPE_6__ {int /*<<< orphan*/  np_list; scalar_t__ np_softc; scalar_t__ np_refcnt; } ;
typedef  TYPE_1__ ndis_packet ;
struct TYPE_7__ {int /*<<< orphan*/  nmb_returnitem; int /*<<< orphan*/  nmb_returnlock; int /*<<< orphan*/  nmb_returnlist; } ;
typedef  TYPE_2__ ndis_miniport_block ;
typedef  int /*<<< orphan*/  io_workitem_func ;
struct TYPE_8__ {scalar_t__ ipt_wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoQueueWorkItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  KeAcquireSpinLockAtDpcLevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLockFromDpcLevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WORKQUEUE_CRITICAL ; 
 TYPE_4__* kernndis_functbl ; 

void
ndis_return_packet(ndis_packet *p)
{
	ndis_miniport_block	*block;

	if (p == NULL)
		return;

	/* Decrement refcount. */
	p->np_refcnt--;

	/* Release packet when refcount hits zero, otherwise return. */
	if (p->np_refcnt)
		return;

	block = ((struct ndis_softc *)p->np_softc)->ndis_block;

	KeAcquireSpinLockAtDpcLevel(&block->nmb_returnlock);
	InitializeListHead((&p->np_list));
	InsertHeadList((&block->nmb_returnlist), (&p->np_list));
	KeReleaseSpinLockFromDpcLevel(&block->nmb_returnlock);

	IoQueueWorkItem(block->nmb_returnitem,
	    (io_workitem_func)kernndis_functbl[7].ipt_wrap,
	    WORKQUEUE_CRITICAL, block);
}