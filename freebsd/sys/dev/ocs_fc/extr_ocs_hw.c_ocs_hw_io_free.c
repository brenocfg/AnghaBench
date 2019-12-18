#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_6__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  reqtag; int /*<<< orphan*/  indicator; } ;
typedef  TYPE_2__ ocs_hw_io_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocs_ref_put (int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_ref_read_count (int /*<<< orphan*/ *) ; 

int32_t
ocs_hw_io_free(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	/* just put refcount */
	if (ocs_ref_read_count(&io->ref) <= 0) {
		ocs_log_err(hw->os, "Bad parameter: refcount <= 0 xri=%x tag=%x\n",
			    io->indicator, io->reqtag);
		return -1;
	}

	return ocs_ref_put(&io->ref); /* ocs_ref_get(): ocs_hw_io_alloc() */
}