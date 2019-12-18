#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_14__ {int n_io; } ;
struct TYPE_15__ {int /*<<< orphan*/  os; TYPE_3__** io; int /*<<< orphan*/  io_free; int /*<<< orphan*/  sli; TYPE_1__ config; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
struct TYPE_16__ {scalar_t__ indicator; int /*<<< orphan*/  state; scalar_t__ is_port_owned; TYPE_4__* sgl; } ;
typedef  TYPE_3__ ocs_hw_io_t ;
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ ocs_dma_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  OCS_CMD_POLL ; 
 int /*<<< orphan*/  OCS_HW_IO_STATE_FREE ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_MIN_DMA_ALIGNMENT ; 
 int /*<<< orphan*/  OCS_M_NOWAIT ; 
 int SLI4_BMBX_SIZE ; 
 scalar_t__ ocs_dma_alloc (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_4__**,int) ; 
 scalar_t__ ocs_hw_command (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__** ocs_malloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_cmd_fcoe_post_sgl_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__,int,TYPE_4__**,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int sli_get_sgl_preregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_init_io(ocs_hw_t *hw)
{
	uint32_t        i = 0, io_index = 0;
	uint32_t        prereg = 0;
	ocs_hw_io_t	*io = NULL;
	uint8_t		cmd[SLI4_BMBX_SIZE];
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;
	uint32_t	nremaining;
	uint32_t	n = 0;
	uint32_t	sgls_per_request = 256;
	ocs_dma_t	**sgls = NULL;
	ocs_dma_t	reqbuf = { 0 };

	prereg = sli_get_sgl_preregister(&hw->sli);

	if (prereg) {
		sgls = ocs_malloc(hw->os, sizeof(*sgls) * sgls_per_request, OCS_M_NOWAIT);
		if (sgls == NULL) {
			ocs_log_err(hw->os, "ocs_malloc sgls failed\n");
			return OCS_HW_RTN_NO_MEMORY;
		}

		rc = ocs_dma_alloc(hw->os, &reqbuf, 32 + sgls_per_request*16, OCS_MIN_DMA_ALIGNMENT);
		if (rc) {
			ocs_log_err(hw->os, "ocs_dma_alloc reqbuf failed\n");
			ocs_free(hw->os, sgls, sizeof(*sgls) * sgls_per_request);
			return OCS_HW_RTN_NO_MEMORY;
		}
	}

	io = hw->io[io_index];
	for (nremaining = hw->config.n_io; nremaining; nremaining -= n) {
		if (prereg) {
			/* Copy address of SGL's into local sgls[] array, break out if the xri
			 * is not contiguous.
			 */
			for (n = 0; n < MIN(sgls_per_request, nremaining); n++) {
				/* Check that we have contiguous xri values */
				if (n > 0) {
					if (hw->io[io_index + n]->indicator != (hw->io[io_index + n-1]->indicator+1)) {
						break;
					}
				}
				sgls[n] = hw->io[io_index + n]->sgl;
			}

			if (sli_cmd_fcoe_post_sgl_pages(&hw->sli, cmd, sizeof(cmd),
						io->indicator, n, sgls, NULL, &reqbuf)) {
				if (ocs_hw_command(hw, cmd, OCS_CMD_POLL, NULL, NULL)) {
					rc = OCS_HW_RTN_ERROR;
					ocs_log_err(hw->os, "SGL post failed\n");
					break;
				}
			}
		} else {
			n = nremaining;
		}

		/* Add to tail if successful */
		for (i = 0; i < n; i ++) {
			io->is_port_owned = 0;
			io->state = OCS_HW_IO_STATE_FREE;
			ocs_list_add_tail(&hw->io_free, io);
			io = hw->io[io_index+1];
			io_index++;
		}
	}

	if (prereg) {
		ocs_dma_free(hw->os, &reqbuf);
		ocs_free(hw->os, sgls, sizeof(*sgls) * sgls_per_request);
	}

	return rc;
}