#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ linkcfg; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_linkcfg_e ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ OCS_HW_LINKCFG_NA ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
ocs_hw_init_linkcfg_cb(int32_t status, uintptr_t value, void *arg)
{
	ocs_hw_t *hw = (ocs_hw_t *)arg;
	if (status == 0) {
		hw->linkcfg = (ocs_hw_linkcfg_e)value;
	} else {
		hw->linkcfg = OCS_HW_LINKCFG_NA;
	}
	ocs_log_debug(hw->os, "linkcfg=%d\n", hw->linkcfg);
}