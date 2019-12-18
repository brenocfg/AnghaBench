#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_17__ {struct TYPE_17__* mdl_next; } ;
typedef  TYPE_3__ mdl ;
struct TYPE_16__ {int /*<<< orphan*/  irp_irpcnt; TYPE_4__* irp_master; } ;
struct TYPE_15__ {scalar_t__ isb_status; } ;
struct TYPE_18__ {scalar_t__ irp_currentstackloc; scalar_t__ irp_stackcnt; scalar_t__ irp_pendingreturned; scalar_t__ irp_cancel; int irp_flags; TYPE_3__* irp_mdl; TYPE_2__ irp_assoc; int /*<<< orphan*/ * irp_usrevent; TYPE_1__ irp_iostat; TYPE_1__* irp_usriostat; } ;
typedef  TYPE_4__ irp ;
struct TYPE_19__ {int isl_ctl; int /*<<< orphan*/  isl_completionctx; int /*<<< orphan*/ * isl_completionfunc; int /*<<< orphan*/ * isl_devobj; } ;
typedef  TYPE_5__ io_stack_location ;
typedef  int /*<<< orphan*/  device_object ;
typedef  int /*<<< orphan*/ * completion_func ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int IRP_ASSOCIATED_IRP ; 
 int IRP_PAGING_IO ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoFreeIrp (TYPE_4__*) ; 
 int /*<<< orphan*/  IoFreeMdl (TYPE_3__*) ; 
 TYPE_5__* IoGetCurrentIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  IoMarkIrpPending (TYPE_4__*) ; 
 int /*<<< orphan*/  IoSkipCurrentIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MSCALL3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int SL_INVOKE_ON_CANCEL ; 
 int SL_INVOKE_ON_ERROR ; 
 int SL_INVOKE_ON_SUCCESS ; 
 int SL_PENDING_RETURNED ; 
 scalar_t__ STATUS_MORE_PROCESSING_REQUIRED ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 

void
IofCompleteRequest(irp *ip, uint8_t prioboost)
{
	uint32_t		status;
	device_object		*dobj;
	io_stack_location	*sl;
	completion_func		cf;

	KASSERT(ip->irp_iostat.isb_status != STATUS_PENDING,
	    ("incorrect IRP(%p) status (STATUS_PENDING)", ip));

	sl = IoGetCurrentIrpStackLocation(ip);
	IoSkipCurrentIrpStackLocation(ip);

	do {
		if (sl->isl_ctl & SL_PENDING_RETURNED)
			ip->irp_pendingreturned = TRUE;

		if (ip->irp_currentstackloc != (ip->irp_stackcnt + 1))
			dobj = IoGetCurrentIrpStackLocation(ip)->isl_devobj;
		else
			dobj = NULL;

		if (sl->isl_completionfunc != NULL &&
		    ((ip->irp_iostat.isb_status == STATUS_SUCCESS &&
		    sl->isl_ctl & SL_INVOKE_ON_SUCCESS) ||
		    (ip->irp_iostat.isb_status != STATUS_SUCCESS &&
		    sl->isl_ctl & SL_INVOKE_ON_ERROR) ||
		    (ip->irp_cancel == TRUE &&
		    sl->isl_ctl & SL_INVOKE_ON_CANCEL))) {
			cf = sl->isl_completionfunc;
			status = MSCALL3(cf, dobj, ip, sl->isl_completionctx);
			if (status == STATUS_MORE_PROCESSING_REQUIRED)
				return;
		} else {
			if ((ip->irp_currentstackloc <= ip->irp_stackcnt) &&
			    (ip->irp_pendingreturned == TRUE))
				IoMarkIrpPending(ip);
		}

		/* move to the next.  */
		IoSkipCurrentIrpStackLocation(ip);
		sl++;
	} while (ip->irp_currentstackloc <= (ip->irp_stackcnt + 1));

	if (ip->irp_usriostat != NULL)
		*ip->irp_usriostat = ip->irp_iostat;
	if (ip->irp_usrevent != NULL)
		KeSetEvent(ip->irp_usrevent, prioboost, FALSE);

	/* Handle any associated IRPs. */

	if (ip->irp_flags & IRP_ASSOCIATED_IRP) {
		uint32_t		masterirpcnt;
		irp			*masterirp;
		mdl			*m;

		masterirp = ip->irp_assoc.irp_master;
		masterirpcnt =
		    InterlockedDecrement(&masterirp->irp_assoc.irp_irpcnt);

		while ((m = ip->irp_mdl) != NULL) {
			ip->irp_mdl = m->mdl_next;
			IoFreeMdl(m);
		}
		IoFreeIrp(ip);
		if (masterirpcnt == 0)
			IoCompleteRequest(masterirp, IO_NO_INCREMENT);
		return;
	}

	/* With any luck, these conditions will never arise. */

	if (ip->irp_flags & IRP_PAGING_IO) {
		if (ip->irp_mdl != NULL)
			IoFreeMdl(ip->irp_mdl);
		IoFreeIrp(ip);
	}
}