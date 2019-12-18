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
struct TYPE_7__ {int /*<<< orphan*/ * os; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_8__ {int indicator; } ;
typedef  TYPE_2__ ocs_hw_io_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_1__*,TYPE_2__*) ; 

int32_t
ocs_hw_io_get_xid(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	if (!hw || !io) {
		ocs_log_err(hw ? hw->os : NULL,
			    "bad parameter hw=%p io=%p\n", hw, io);
		return -1;
	}

	return io->indicator;
}