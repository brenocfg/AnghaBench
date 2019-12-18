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
struct TYPE_9__ {int /*<<< orphan*/  wqe_link; } ;
typedef  TYPE_3__ ocs_hw_io_t ;

/* Variables and functions */
 scalar_t__ ocs_list_on_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ocs_hw_remove_io_timed_wqe(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	if (hw->config.emulate_tgt_wqe_timeout) {
		/*
		 * If target wqe timeouts are enabled,
		 * remove from active wqe list.
		 */
		ocs_lock(&hw->io_lock);
			if (ocs_list_on_list(&io->wqe_link)) {
				ocs_list_remove(&hw->io_timed_wqe, io);
			}
		ocs_unlock(&hw->io_lock);
	}
}