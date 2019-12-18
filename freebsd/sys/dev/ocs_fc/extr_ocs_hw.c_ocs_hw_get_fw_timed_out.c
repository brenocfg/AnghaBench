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
struct TYPE_3__ {int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_REG_SLIPORT_ERROR1 ; 
 int /*<<< orphan*/  SLI4_REG_SLIPORT_ERROR2 ; 
 int sli_reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_get_fw_timed_out(ocs_hw_t *hw)
{
	/* The error values below are taken from LOWLEVEL_SET_WATCHDOG_TIMER_rev1.pdf
	* No further explanation is given in the document.
	* */
	return (sli_reg_read(&hw->sli, SLI4_REG_SLIPORT_ERROR1) == 0x2 &&
		sli_reg_read(&hw->sli, SLI4_REG_SLIPORT_ERROR2) == 0x10);
}