#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_port_dnrx; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_io_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ ocs_hw_reque_xri (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_hw_rqpair_auto_xfer_rdy_dnrx_check(ocs_hw_t *hw)
{
	ocs_hw_io_t *io;
	int32_t rc;

	ocs_lock(&hw->io_lock);

	while (!ocs_list_empty(&hw->io_port_dnrx)) {
		io = ocs_list_remove_head(&hw->io_port_dnrx);
		rc = ocs_hw_reque_xri(hw, io);
		if(rc) {
			break;
		}
	}

	ocs_unlock(&hw->io_lock);
}