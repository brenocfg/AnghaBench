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
struct TYPE_5__ {scalar_t__ if_type; } ;
struct TYPE_6__ {TYPE_1__ sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  int ocs_hw_rtn_e ;
typedef  int /*<<< orphan*/  ocs_hw_fw_cb_t ;
typedef  int /*<<< orphan*/  ocs_dma_t ;

/* Variables and functions */
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int ocs_hw_firmware_write_lancer (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

ocs_hw_rtn_e
ocs_hw_firmware_write(ocs_hw_t *hw, ocs_dma_t *dma, uint32_t size, uint32_t offset, int last, ocs_hw_fw_cb_t cb, void *arg)
{
	if (hw->sli.if_type == SLI4_IF_TYPE_LANCER_FC_ETH) {
		return ocs_hw_firmware_write_lancer(hw, dma, size, offset, last, cb, arg);
	} else {
		/* Write firmware_write for BE3/Skyhawk not supported */
		return -1;
	}
}