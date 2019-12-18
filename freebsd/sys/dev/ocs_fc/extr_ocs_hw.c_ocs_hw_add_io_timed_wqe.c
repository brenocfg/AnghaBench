#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ emulate_tgt_wqe_timeout; } ;
struct TYPE_8__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_timed_wqe; TYPE_1__ config; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_9__ {int /*<<< orphan*/  submit_ticks; scalar_t__ tgt_wqe_timeout; } ;
typedef  TYPE_3__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_get_os_ticks () ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ocs_hw_add_io_timed_wqe(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	if (hw->config.emulate_tgt_wqe_timeout && io->tgt_wqe_timeout) {
		/*
		 * Active WQE list currently only used for
		 * target WQE timeouts.
		 */
		ocs_lock(&hw->io_lock);
			ocs_list_add_tail(&hw->io_timed_wqe, io);
			io->submit_ticks = ocs_get_os_ticks();
		ocs_unlock(&hw->io_lock);
	}
}