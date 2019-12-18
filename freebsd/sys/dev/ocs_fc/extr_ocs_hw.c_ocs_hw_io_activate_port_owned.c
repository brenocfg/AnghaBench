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
struct TYPE_7__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_8__ {int /*<<< orphan*/  xbusy; int /*<<< orphan*/  ref; int /*<<< orphan*/  indicator; int /*<<< orphan*/ * wq; } ;
typedef  TYPE_2__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_hw_io_free_port_owned ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ocs_ref_read_count (int /*<<< orphan*/ *) ; 

ocs_hw_io_t *
ocs_hw_io_activate_port_owned(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	if (ocs_ref_read_count(&io->ref) > 0) {
		ocs_log_err(hw->os, "Bad parameter: refcount > 0\n");
		return NULL;
	}

	if (io->wq != NULL) {
		ocs_log_err(hw->os, "XRI %x already in use\n", io->indicator);
		return NULL;
	}

	ocs_ref_init(&io->ref, ocs_hw_io_free_port_owned, io);
	io->xbusy = TRUE;

	return io;
}