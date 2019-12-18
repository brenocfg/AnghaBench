#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_9__ {int /*<<< orphan*/  indicator; int /*<<< orphan*/  def_sgl; } ;
typedef  TYPE_2__ ocs_hw_io_t ;
typedef  int /*<<< orphan*/  ocs_dma_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_NO_MEMORY ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_hw_command (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_hw_rqpair_auto_xfer_rdy_buffer_post (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_rqpair_auto_xfer_rdy_move_to_port_cb ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ocs_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_cmd_fcoe_post_sgl_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_get_sgl_preregister (int /*<<< orphan*/ *) ; 

ocs_hw_rtn_e
ocs_hw_rqpair_auto_xfer_rdy_move_to_port(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	/* We only need to preregister the SGL if it has not yet been done. */
	if (!sli_get_sgl_preregister(&hw->sli)) {
		uint8_t	*post_sgl;
		ocs_dma_t *psgls = &io->def_sgl;
		ocs_dma_t **sgls = &psgls;

		/* non-local buffer required for mailbox queue */
		post_sgl = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_NOWAIT);
		if (post_sgl == NULL) {
			ocs_log_err(hw->os, "no buffer for command\n");
			return OCS_HW_RTN_NO_MEMORY;
		}
		if (sli_cmd_fcoe_post_sgl_pages(&hw->sli, post_sgl, SLI4_BMBX_SIZE,
						io->indicator, 1, sgls, NULL, NULL)) {
			if (ocs_hw_command(hw, post_sgl, OCS_CMD_NOWAIT,
					    ocs_hw_rqpair_auto_xfer_rdy_move_to_port_cb, NULL)) {
				ocs_free(hw->os, post_sgl, SLI4_BMBX_SIZE);
				ocs_log_err(hw->os, "SGL post failed\n");
				return OCS_HW_RTN_ERROR;
			}
		}
	}

	ocs_lock(&hw->io_lock);
	if (ocs_hw_rqpair_auto_xfer_rdy_buffer_post(hw, io, 0) != 0) { /* DNRX set - no buffer */
		ocs_unlock(&hw->io_lock);
		return OCS_HW_RTN_ERROR;
	}
	ocs_unlock(&hw->io_lock);
	return OCS_HW_RTN_SUCCESS;
}