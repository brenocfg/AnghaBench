#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_port_dnrx; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_8__ {int /*<<< orphan*/  ref; scalar_t__ auto_xfer_rdy_dnrx; TYPE_1__* hw; } ;
typedef  TYPE_2__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_io_free_common (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_init (int /*<<< orphan*/ *,void (*) (void*),TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_hw_io_free_port_owned(void *arg)
{
	ocs_hw_io_t *io = (ocs_hw_io_t *)arg;
	ocs_hw_t *hw = io->hw;

	/*
	 * For auto xfer rdy, if the dnrx bit is set, then add it to the list of XRIs
	 * waiting for buffers.
	 */
	if (io->auto_xfer_rdy_dnrx) {
		ocs_lock(&hw->io_lock);
			/* take a reference count because we still own the IO until the buffer is posted */
			ocs_ref_init(&io->ref, ocs_hw_io_free_port_owned, io);
			ocs_list_add_tail(&hw->io_port_dnrx, io);
		ocs_unlock(&hw->io_lock);
	}

	/* perform common cleanup */
	ocs_hw_io_free_common(hw, io);
}