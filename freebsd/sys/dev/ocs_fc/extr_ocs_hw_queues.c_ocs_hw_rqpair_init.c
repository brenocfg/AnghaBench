#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ auto_xfer_rdy_size; scalar_t__ auto_xfer_rdy_xri_cnt; } ;
struct TYPE_7__ {int /*<<< orphan*/  os; TYPE_1__ config; int /*<<< orphan*/ * auto_xfer_rdy_buf_pool; int /*<<< orphan*/  sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;

/* Variables and functions */
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 scalar_t__ ocs_hw_rqpair_auto_xfer_rdy_buffer_alloc (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ocs_hw_xri_move_to_port_owned (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_pool_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_auto_xfer_rdy_capable (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_rqpair_init(ocs_hw_t *hw)
{
	ocs_hw_rtn_e	rc;
	uint32_t xris_posted;

	ocs_log_debug(hw->os, "RQ Pair mode\n");

	/*
	 * If we get this far, the auto XFR_RDY feature was enabled successfully, otherwise ocs_hw_init() would
	 * return with an error. So allocate the buffers based on the initial XRI pool required to support this
	 * feature.
	 */
	if (sli_get_auto_xfer_rdy_capable(&hw->sli) &&
	    hw->config.auto_xfer_rdy_size > 0) {
		if (hw->auto_xfer_rdy_buf_pool == NULL) {
			/*
			 * Allocate one more buffer than XRIs so that when all the XRIs are in use, we still have
			 * one to post back for the case where the response phase is started in the context of
			 * the data completion.
			 */
			rc = ocs_hw_rqpair_auto_xfer_rdy_buffer_alloc(hw, hw->config.auto_xfer_rdy_xri_cnt + 1);
			if (rc != OCS_HW_RTN_SUCCESS) {
				return rc;
			}
		} else {
			ocs_pool_reset(hw->auto_xfer_rdy_buf_pool);
		}

		/* Post the auto XFR_RDY XRIs */
		xris_posted = ocs_hw_xri_move_to_port_owned(hw, hw->config.auto_xfer_rdy_xri_cnt);
		if (xris_posted != hw->config.auto_xfer_rdy_xri_cnt) {
			ocs_log_err(hw->os, "post_xri failed, only posted %d XRIs\n", xris_posted);
			return OCS_HW_RTN_ERROR;
		}
	}

	return 0;
}