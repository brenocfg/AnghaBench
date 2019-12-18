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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_6__ {int /*<<< orphan*/ * ovfl_io; int /*<<< orphan*/  ovfl_sgl_count; int /*<<< orphan*/ * ovfl_sgl; } ;
typedef  TYPE_2__ ocs_hw_io_t ;
typedef  int /*<<< orphan*/  ocs_dma_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sli_get_sgl_preregister (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_io_register_sgl(ocs_hw_t *hw, ocs_hw_io_t *io, ocs_dma_t *sgl, uint32_t sgl_count)
{
	if (sli_get_sgl_preregister(&hw->sli)) {
		ocs_log_err(hw->os, "can't use temporary SGL with pre-registered SGLs\n");
		return OCS_HW_RTN_ERROR;
	}
	io->ovfl_sgl = sgl;
	io->ovfl_sgl_count = sgl_count;
	io->ovfl_io = NULL;

	return OCS_HW_RTN_SUCCESS;
}