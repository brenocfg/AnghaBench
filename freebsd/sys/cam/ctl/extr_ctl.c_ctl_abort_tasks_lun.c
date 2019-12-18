#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tag_type; int /*<<< orphan*/  tag_num; } ;
struct TYPE_6__ {scalar_t__ targ_port; scalar_t__ initid; } ;
struct TYPE_10__ {TYPE_1__ nexus; int /*<<< orphan*/  flags; } ;
union ctl_io {TYPE_3__ scsiio; TYPE_5__ io_hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/ * serializing_sc; int /*<<< orphan*/ * original_sc; int /*<<< orphan*/  msg_type; TYPE_1__ nexus; } ;
struct TYPE_7__ {int /*<<< orphan*/  tag_type; int /*<<< orphan*/  tag_num; int /*<<< orphan*/  task_action; } ;
union ctl_ha_msg {TYPE_4__ hdr; TYPE_2__ task; } ;
typedef  scalar_t__ uint32_t ;
struct ctl_lun {int flags; int /*<<< orphan*/  ooa_queue; int /*<<< orphan*/  lun_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_ABORT ; 
 int /*<<< orphan*/  CTL_FLAG_ABORT_STATUS ; 
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 int CTL_LUN_PRIMARY_SC ; 
 int /*<<< orphan*/  CTL_MSG_MANAGE_TASKS ; 
 int /*<<< orphan*/  CTL_TASK_ABORT_TASK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_NEXT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  ctl_ha_msg_send (int /*<<< orphan*/ ,union ctl_ha_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_try_unblock_io (struct ctl_lun*,union ctl_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ooa_links ; 

__attribute__((used)) static void
ctl_abort_tasks_lun(struct ctl_lun *lun, uint32_t targ_port, uint32_t init_id,
    int other_sc)
{
	union ctl_io *xio;

	mtx_assert(&lun->lun_lock, MA_OWNED);

	/*
	 * Run through the OOA queue and attempt to find the given I/O.
	 * The target port, initiator ID, tag type and tag number have to
	 * match the values that we got from the initiator.  If we have an
	 * untagged command to abort, simply abort the first untagged command
	 * we come to.  We only allow one untagged command at a time of course.
	 */
	for (xio = (union ctl_io *)TAILQ_FIRST(&lun->ooa_queue); xio != NULL;
	     xio = (union ctl_io *)TAILQ_NEXT(&xio->io_hdr, ooa_links)) {

		if ((targ_port == UINT32_MAX ||
		     targ_port == xio->io_hdr.nexus.targ_port) &&
		    (init_id == UINT32_MAX ||
		     init_id == xio->io_hdr.nexus.initid)) {
			if (targ_port != xio->io_hdr.nexus.targ_port ||
			    init_id != xio->io_hdr.nexus.initid)
				xio->io_hdr.flags |= CTL_FLAG_ABORT_STATUS;
			xio->io_hdr.flags |= CTL_FLAG_ABORT;
			if (!other_sc && !(lun->flags & CTL_LUN_PRIMARY_SC)) {
				union ctl_ha_msg msg_info;

				msg_info.hdr.nexus = xio->io_hdr.nexus;
				msg_info.task.task_action = CTL_TASK_ABORT_TASK;
				msg_info.task.tag_num = xio->scsiio.tag_num;
				msg_info.task.tag_type = xio->scsiio.tag_type;
				msg_info.hdr.msg_type = CTL_MSG_MANAGE_TASKS;
				msg_info.hdr.original_sc = NULL;
				msg_info.hdr.serializing_sc = NULL;
				ctl_ha_msg_send(CTL_HA_CHAN_CTL, &msg_info,
				    sizeof(msg_info.task), M_NOWAIT);
			}
			ctl_try_unblock_io(lun, xio, FALSE);
		}
	}
}