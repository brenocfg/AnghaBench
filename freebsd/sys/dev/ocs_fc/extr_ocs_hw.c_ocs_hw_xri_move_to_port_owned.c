#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_port_owned; int /*<<< orphan*/  os; int /*<<< orphan*/  io_free; scalar_t__ auto_xfer_rdy_enabled; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
struct TYPE_12__ {int is_port_owned; int /*<<< orphan*/  indicator; int /*<<< orphan*/  axr_lock; } ;
typedef  TYPE_2__ ocs_hw_io_t ;

/* Variables and functions */
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 scalar_t__ ocs_hw_post_xri (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_hw_reclaim_xri (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ocs_hw_rqpair_auto_xfer_rdy_move_to_port (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_list_add_head (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

uint32_t
ocs_hw_xri_move_to_port_owned(ocs_hw_t *hw, uint32_t num_xri)
{
	ocs_hw_io_t	*io;
	uint32_t i;
	uint32_t num_posted = 0;

	/*
	 * Note: We cannot use ocs_hw_io_alloc() because that would place the
	 *       IO on the io_inuse list. We need to move from the io_free to
	 *       the io_port_owned list.
	 */
	ocs_lock(&hw->io_lock);

	for (i = 0; i < num_xri; i++) {

		if (NULL != (io = ocs_list_remove_head(&hw->io_free))) {
			ocs_hw_rtn_e rc;

			/*
			 * if this is an auto xfer rdy XRI, then we need to attach a
			 * buffer to the XRI before submitting it to the chip. If a
			 * buffer is unavailable, then we cannot post it, so return it
			 * to the free pool.
			 */
			if (hw->auto_xfer_rdy_enabled) {
				/* Note: uses the IO lock to get the auto xfer rdy buffer */
				ocs_unlock(&hw->io_lock);
				rc = ocs_hw_rqpair_auto_xfer_rdy_move_to_port(hw, io);
				ocs_lock(&hw->io_lock);
				if (rc != OCS_HW_RTN_SUCCESS) {
					ocs_list_add_head(&hw->io_free, io);
					break;
				}
			}
			ocs_lock_init(hw->os, &io->axr_lock, "HW_axr_lock[%d]", io->indicator);
			io->is_port_owned = 1;
			ocs_list_add_tail(&hw->io_port_owned, io);

			/* Post XRI */
			if (ocs_hw_post_xri(hw, io->indicator, 1) != OCS_HW_RTN_SUCCESS ) {
				ocs_hw_reclaim_xri(hw, io->indicator, i);
				break;
			}
			num_posted++;
		} else {
			/* no more free XRIs */
			break;
		}
	}
	ocs_unlock(&hw->io_lock);

	return num_posted;
}