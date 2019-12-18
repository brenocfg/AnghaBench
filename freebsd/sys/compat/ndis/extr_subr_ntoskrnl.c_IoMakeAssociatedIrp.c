#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {TYPE_4__* irp_master; } ;
struct TYPE_8__ {int /*<<< orphan*/  irp_thread; } ;
struct TYPE_9__ {TYPE_1__ irp_overlay; } ;
struct TYPE_11__ {TYPE_3__ irp_assoc; TYPE_2__ irp_tail; int /*<<< orphan*/  irp_flags; } ;
typedef  TYPE_4__ irp ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IRP_ASSOCIATED_IRP ; 
 TYPE_4__* IoAllocateIrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntoskrnl_dispatchlock ; 

__attribute__((used)) static irp *
IoMakeAssociatedIrp(irp *ip, uint8_t stsize)
{
	irp			*associrp;

	associrp = IoAllocateIrp(stsize, FALSE);
	if (associrp == NULL)
		return (NULL);

	mtx_lock(&ntoskrnl_dispatchlock);
	associrp->irp_flags |= IRP_ASSOCIATED_IRP;
	associrp->irp_tail.irp_overlay.irp_thread =
	    ip->irp_tail.irp_overlay.irp_thread;
	associrp->irp_assoc.irp_master = ip;
	mtx_unlock(&ntoskrnl_dispatchlock);

	return (associrp);
}