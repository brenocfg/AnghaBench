#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ use_dif_sec_xri; } ;
struct TYPE_9__ {TYPE_1__ workaround; int /*<<< orphan*/  io_free; int /*<<< orphan*/  io_wait_free; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_10__ {int /*<<< orphan*/  state; scalar_t__ xbusy; } ;
typedef  TYPE_3__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_IO_STATE_FREE ; 
 int /*<<< orphan*/  OCS_HW_IO_STATE_WAIT_FREE ; 
 int /*<<< orphan*/  ocs_hw_check_sec_hio_list (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
ocs_hw_io_free_move_correct_list(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	if (io->xbusy) {
		/* add to wait_free list and wait for XRI_ABORTED CQEs to clean up */
		ocs_list_add_tail(&hw->io_wait_free, io);
		io->state = OCS_HW_IO_STATE_WAIT_FREE;
	} else {
		/* IO not busy, add to free list */
		ocs_list_add_tail(&hw->io_free, io);
		io->state = OCS_HW_IO_STATE_FREE;
	}

	/* BZ 161832 workaround */
	if (hw->workaround.use_dif_sec_xri) {
		ocs_hw_check_sec_hio_list(hw);
	}
}