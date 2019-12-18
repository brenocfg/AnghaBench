#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_inuse; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_9__ {TYPE_1__* hw; } ;
typedef  TYPE_2__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_io_free_common (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_hw_io_free_move_correct_list (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_hw_io_free_internal(void *arg)
{
	ocs_hw_io_t *io = (ocs_hw_io_t *)arg;
	ocs_hw_t *hw = io->hw;

	/* perform common cleanup */
	ocs_hw_io_free_common(hw, io);

	ocs_lock(&hw->io_lock);
		/* remove from in-use list */
		ocs_list_remove(&hw->io_inuse, io);
		ocs_hw_io_free_move_correct_list(hw, io);
	ocs_unlock(&hw->io_lock);
}