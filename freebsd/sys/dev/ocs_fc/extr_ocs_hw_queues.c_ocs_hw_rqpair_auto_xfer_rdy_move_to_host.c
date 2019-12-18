#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  auto_xfer_rdy_buf_pool; int /*<<< orphan*/  io_port_dnrx; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_10__ {int /*<<< orphan*/ * axr_buf; scalar_t__ auto_xfer_rdy_dnrx; int /*<<< orphan*/  dnrx_link; } ;
typedef  TYPE_2__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_io_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_hw_rqpair_auto_xfer_rdy_dnrx_check (TYPE_1__*) ; 
 scalar_t__ ocs_list_on_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_pool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

void
ocs_hw_rqpair_auto_xfer_rdy_move_to_host(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	if (io->axr_buf != NULL) {
		ocs_lock(&hw->io_lock);
			/* check  list and remove if there */
			if (ocs_list_on_list(&io->dnrx_link)) {
				ocs_list_remove(&hw->io_port_dnrx, io);
				io->auto_xfer_rdy_dnrx = 0;

				/* release the count for waiting for a buffer */
				ocs_hw_io_free(hw, io);
			}

			ocs_pool_put(hw->auto_xfer_rdy_buf_pool, io->axr_buf);
			io->axr_buf = NULL;
		ocs_unlock(&hw->io_lock);

		ocs_hw_rqpair_auto_xfer_rdy_dnrx_check(hw);
	}
	return;
}