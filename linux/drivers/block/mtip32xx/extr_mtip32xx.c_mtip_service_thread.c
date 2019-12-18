#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtip_port {int flags; int* cmds_to_issue; int /*<<< orphan*/  svc_wait; } ;
struct driver_data {int slot_groups; int dd_flag; int /*<<< orphan*/  queue; struct mtip_port* port; int /*<<< orphan*/  tags; TYPE_1__* pdev; int /*<<< orphan*/  irq_workers_active; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long MTIP_DDF_REMOVE_PENDING_BIT ; 
 unsigned long MTIP_PF_EH_ACTIVE_BIT ; 
 unsigned long MTIP_PF_ISSUE_CMDS_BIT ; 
 unsigned long MTIP_PF_REBUILD_BIT ; 
 unsigned long MTIP_PF_SVC_THD_ACTIVE_BIT ; 
 unsigned long MTIP_PF_SVC_THD_STOP_BIT ; 
 int MTIP_PF_SVC_THD_WORK ; 
 unsigned long MTIP_PF_TO_ACTIVE_BIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct driver_data*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (unsigned long,int*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned long find_next_bit (int*,unsigned int,unsigned long) ; 
 unsigned long jiffies ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mtip_abort_cmd ; 
 scalar_t__ mtip_device_reset (struct driver_data*) ; 
 scalar_t__ mtip_ftl_rebuild_poll (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_handle_tfe (struct driver_data*) ; 
 int /*<<< orphan*/  mtip_issue_ncq_command (struct mtip_port*,unsigned long) ; 
 int /*<<< orphan*/  mtip_queue_cmd ; 
 int /*<<< orphan*/  set_bit (unsigned long,int*) ; 
 int test_bit (unsigned long,int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtip_service_thread(void *data)
{
	struct driver_data *dd = (struct driver_data *)data;
	unsigned long slot, slot_start, slot_wrap, to;
	unsigned int num_cmd_slots = dd->slot_groups * 32;
	struct mtip_port *port = dd->port;

	while (1) {
		if (kthread_should_stop() ||
			test_bit(MTIP_PF_SVC_THD_STOP_BIT, &port->flags))
			goto st_out;
		clear_bit(MTIP_PF_SVC_THD_ACTIVE_BIT, &port->flags);

		/*
		 * the condition is to check neither an internal command is
		 * is in progress nor error handling is active
		 */
		wait_event_interruptible(port->svc_wait, (port->flags) &&
			(port->flags & MTIP_PF_SVC_THD_WORK));

		if (kthread_should_stop() ||
			test_bit(MTIP_PF_SVC_THD_STOP_BIT, &port->flags))
			goto st_out;

		if (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT,
				&dd->dd_flag)))
			goto st_out;

		set_bit(MTIP_PF_SVC_THD_ACTIVE_BIT, &port->flags);

restart_eh:
		/* Demux bits: start with error handling */
		if (test_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags)) {
			mtip_handle_tfe(dd);
			clear_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags);
		}

		if (test_bit(MTIP_PF_EH_ACTIVE_BIT, &port->flags))
			goto restart_eh;

		if (test_bit(MTIP_PF_TO_ACTIVE_BIT, &port->flags)) {
			to = jiffies + msecs_to_jiffies(5000);

			do {
				mdelay(100);
			} while (atomic_read(&dd->irq_workers_active) != 0 &&
				time_before(jiffies, to));

			if (atomic_read(&dd->irq_workers_active) != 0)
				dev_warn(&dd->pdev->dev,
					"Completion workers still active!");

			blk_mq_quiesce_queue(dd->queue);

			blk_mq_tagset_busy_iter(&dd->tags, mtip_queue_cmd, dd);

			set_bit(MTIP_PF_ISSUE_CMDS_BIT, &dd->port->flags);

			if (mtip_device_reset(dd))
				blk_mq_tagset_busy_iter(&dd->tags,
							mtip_abort_cmd, dd);

			clear_bit(MTIP_PF_TO_ACTIVE_BIT, &dd->port->flags);

			blk_mq_unquiesce_queue(dd->queue);
		}

		if (test_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags)) {
			slot = 1;
			/* used to restrict the loop to one iteration */
			slot_start = num_cmd_slots;
			slot_wrap = 0;
			while (1) {
				slot = find_next_bit(port->cmds_to_issue,
						num_cmd_slots, slot);
				if (slot_wrap == 1) {
					if ((slot_start >= slot) ||
						(slot >= num_cmd_slots))
						break;
				}
				if (unlikely(slot_start == num_cmd_slots))
					slot_start = slot;

				if (unlikely(slot == num_cmd_slots)) {
					slot = 1;
					slot_wrap = 1;
					continue;
				}

				/* Issue the command to the hardware */
				mtip_issue_ncq_command(port, slot);

				clear_bit(slot, port->cmds_to_issue);
			}

			clear_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags);
		}

		if (test_bit(MTIP_PF_REBUILD_BIT, &port->flags)) {
			if (mtip_ftl_rebuild_poll(dd) == 0)
				clear_bit(MTIP_PF_REBUILD_BIT, &port->flags);
		}
	}

st_out:
	return 0;
}