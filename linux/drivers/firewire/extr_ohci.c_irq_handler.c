#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int /*<<< orphan*/  tasklet; } ;
struct TYPE_11__ {int /*<<< orphan*/  tasklet; } ;
struct TYPE_10__ {int /*<<< orphan*/  tasklet; } ;
struct TYPE_9__ {int /*<<< orphan*/  tasklet; } ;
struct fw_ohci {int /*<<< orphan*/  lock; TYPE_8__* it_context_list; TYPE_6__* ir_context_list; TYPE_4__ at_response_ctx; TYPE_3__ at_request_ctx; TYPE_2__ ar_response_ctx; TYPE_1__ ar_request_ctx; int /*<<< orphan*/  bus_reset_work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_15__ {int /*<<< orphan*/  tasklet; } ;
struct TYPE_16__ {TYPE_7__ context; } ;
struct TYPE_13__ {int /*<<< orphan*/  tasklet; } ;
struct TYPE_14__ {TYPE_5__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  OHCI1394_IntEventClear ; 
 int /*<<< orphan*/  OHCI1394_IsoRecvIntEventClear ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitIntEventClear ; 
 int /*<<< orphan*/  OHCI1394_LinkControlSet ; 
 int OHCI1394_LinkControl_cycleMaster ; 
 int /*<<< orphan*/  OHCI1394_PostedWriteAddressHi ; 
 int /*<<< orphan*/  OHCI1394_PostedWriteAddressLo ; 
 int OHCI1394_RQPkt ; 
 int OHCI1394_RSPkt ; 
 int OHCI1394_busReset ; 
 int OHCI1394_cycle64Seconds ; 
 int OHCI1394_cycleInconsistent ; 
 int OHCI1394_cycleTooLong ; 
 int OHCI1394_isochRx ; 
 int OHCI1394_isochTx ; 
 int OHCI1394_postedWriteErr ; 
 int OHCI1394_regAccessFail ; 
 int OHCI1394_reqTxComplete ; 
 int OHCI1394_respTxComplete ; 
 int OHCI1394_selfIDComplete ; 
 int OHCI1394_unrecoverableError ; 
 int ffs (int) ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 int /*<<< orphan*/  handle_dead_contexts (struct fw_ohci*) ; 
 int /*<<< orphan*/  log_irqs (struct fw_ohci*,int) ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*) ; 
 int /*<<< orphan*/  ohci_notice (struct fw_ohci*,char*) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selfid_workqueue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_bus_time (struct fw_ohci*) ; 

__attribute__((used)) static irqreturn_t irq_handler(int irq, void *data)
{
	struct fw_ohci *ohci = data;
	u32 event, iso_event;
	int i;

	event = reg_read(ohci, OHCI1394_IntEventClear);

	if (!event || !~event)
		return IRQ_NONE;

	/*
	 * busReset and postedWriteErr must not be cleared yet
	 * (OHCI 1.1 clauses 7.2.3.2 and 13.2.8.1)
	 */
	reg_write(ohci, OHCI1394_IntEventClear,
		  event & ~(OHCI1394_busReset | OHCI1394_postedWriteErr));
	log_irqs(ohci, event);

	if (event & OHCI1394_selfIDComplete)
		queue_work(selfid_workqueue, &ohci->bus_reset_work);

	if (event & OHCI1394_RQPkt)
		tasklet_schedule(&ohci->ar_request_ctx.tasklet);

	if (event & OHCI1394_RSPkt)
		tasklet_schedule(&ohci->ar_response_ctx.tasklet);

	if (event & OHCI1394_reqTxComplete)
		tasklet_schedule(&ohci->at_request_ctx.tasklet);

	if (event & OHCI1394_respTxComplete)
		tasklet_schedule(&ohci->at_response_ctx.tasklet);

	if (event & OHCI1394_isochRx) {
		iso_event = reg_read(ohci, OHCI1394_IsoRecvIntEventClear);
		reg_write(ohci, OHCI1394_IsoRecvIntEventClear, iso_event);

		while (iso_event) {
			i = ffs(iso_event) - 1;
			tasklet_schedule(
				&ohci->ir_context_list[i].context.tasklet);
			iso_event &= ~(1 << i);
		}
	}

	if (event & OHCI1394_isochTx) {
		iso_event = reg_read(ohci, OHCI1394_IsoXmitIntEventClear);
		reg_write(ohci, OHCI1394_IsoXmitIntEventClear, iso_event);

		while (iso_event) {
			i = ffs(iso_event) - 1;
			tasklet_schedule(
				&ohci->it_context_list[i].context.tasklet);
			iso_event &= ~(1 << i);
		}
	}

	if (unlikely(event & OHCI1394_regAccessFail))
		ohci_err(ohci, "register access failure\n");

	if (unlikely(event & OHCI1394_postedWriteErr)) {
		reg_read(ohci, OHCI1394_PostedWriteAddressHi);
		reg_read(ohci, OHCI1394_PostedWriteAddressLo);
		reg_write(ohci, OHCI1394_IntEventClear,
			  OHCI1394_postedWriteErr);
		if (printk_ratelimit())
			ohci_err(ohci, "PCI posted write error\n");
	}

	if (unlikely(event & OHCI1394_cycleTooLong)) {
		if (printk_ratelimit())
			ohci_notice(ohci, "isochronous cycle too long\n");
		reg_write(ohci, OHCI1394_LinkControlSet,
			  OHCI1394_LinkControl_cycleMaster);
	}

	if (unlikely(event & OHCI1394_cycleInconsistent)) {
		/*
		 * We need to clear this event bit in order to make
		 * cycleMatch isochronous I/O work.  In theory we should
		 * stop active cycleMatch iso contexts now and restart
		 * them at least two cycles later.  (FIXME?)
		 */
		if (printk_ratelimit())
			ohci_notice(ohci, "isochronous cycle inconsistent\n");
	}

	if (unlikely(event & OHCI1394_unrecoverableError))
		handle_dead_contexts(ohci);

	if (event & OHCI1394_cycle64Seconds) {
		spin_lock(&ohci->lock);
		update_bus_time(ohci);
		spin_unlock(&ohci->lock);
	} else
		flush_writes(ohci);

	return IRQ_HANDLED;
}