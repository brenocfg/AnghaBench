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
typedef  size_t uint32_t ;
struct TYPE_8__ {size_t quarantine_index; TYPE_3__** quarantine_ios; } ;
typedef  TYPE_1__ ocs_quarantine_info_t ;
struct TYPE_9__ {int /*<<< orphan*/ * os; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_10__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  reqtag; int /*<<< orphan*/  indicator; int /*<<< orphan*/  quarantine; } ;
typedef  TYPE_3__ ocs_hw_io_t ;
struct TYPE_11__ {int /*<<< orphan*/  queue; TYPE_1__ quarantine_info; } ;
typedef  TYPE_4__ hw_wq_t ;

/* Variables and functions */
 size_t OCS_HW_QUARANTINE_QUEUE_DEPTH ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_ref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_queue_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_queue_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_hw_io_quarantine(ocs_hw_t *hw, hw_wq_t *wq, ocs_hw_io_t *io)
{
	ocs_quarantine_info_t *q_info = &wq->quarantine_info;
	uint32_t	index;
	ocs_hw_io_t	*free_io = NULL;

	/* return if the QX bit was clear */
	if (!io->quarantine) {
		return;
	}

	/* increment the IO refcount to prevent it from being freed before the quarantine is over */
	if (ocs_ref_get_unless_zero(&io->ref) == 0) {
		/* command no longer active */
		ocs_log_debug(hw ? hw->os : NULL,
			      "io not active xri=0x%x tag=0x%x\n",
			      io->indicator, io->reqtag);
		return;
	}

	sli_queue_lock(wq->queue);
		index = q_info->quarantine_index;
		free_io = q_info->quarantine_ios[index];
		q_info->quarantine_ios[index] = io;
		q_info->quarantine_index = (index + 1) % OCS_HW_QUARANTINE_QUEUE_DEPTH;
	sli_queue_unlock(wq->queue);

	if (free_io != NULL) {
		ocs_ref_put(&free_io->ref); /* ocs_ref_get(): same function */
	}
}