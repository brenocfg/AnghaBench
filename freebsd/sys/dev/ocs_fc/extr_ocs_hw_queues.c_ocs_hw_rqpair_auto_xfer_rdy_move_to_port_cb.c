#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int32_t
ocs_hw_rqpair_auto_xfer_rdy_move_to_port_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{
	if (status != 0) {
		ocs_log_debug(hw->os, "Status 0x%x\n", status);
	}

	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
	return 0;
}