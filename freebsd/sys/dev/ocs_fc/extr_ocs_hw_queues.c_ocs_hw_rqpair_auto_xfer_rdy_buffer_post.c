#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {void* sge_type; void* last; int /*<<< orphan*/  buffer_length; int /*<<< orphan*/  buffer_address_low; int /*<<< orphan*/  buffer_address_high; } ;
typedef  TYPE_5__ sli4_sge_t ;
struct TYPE_18__ {int /*<<< orphan*/  dif_blk_size; void* auto_incr_ref_tag; int /*<<< orphan*/  check_app_tag; int /*<<< orphan*/  app_tag_cmp; int /*<<< orphan*/  repl_app_tag; int /*<<< orphan*/  sge_type; } ;
typedef  TYPE_6__ sli4_diseed_sge_t ;
struct TYPE_14__ {int /*<<< orphan*/  auto_xfer_rdy_blk_size_chip; int /*<<< orphan*/  auto_xfer_rdy_app_tag_valid; int /*<<< orphan*/  auto_xfer_rdy_app_tag_value; scalar_t__ auto_xfer_rdy_p_type; } ;
struct TYPE_19__ {TYPE_2__ config; int /*<<< orphan*/  auto_xfer_rdy_buf_pool; } ;
typedef  TYPE_7__ ocs_hw_t ;
struct TYPE_13__ {TYPE_5__* virt; } ;
struct TYPE_20__ {TYPE_9__* axr_buf; TYPE_1__ def_sgl; } ;
typedef  TYPE_8__ ocs_hw_io_t ;
struct TYPE_15__ {int /*<<< orphan*/  size; int /*<<< orphan*/  phys; } ;
struct TYPE_16__ {TYPE_3__ dma; } ;
struct TYPE_21__ {TYPE_4__ payload; } ;
typedef  TYPE_9__ ocs_hw_auto_xfer_rdy_buffer_t ;

/* Variables and functions */
 void* SLI4_SGE_TYPE_DATA ; 
 int /*<<< orphan*/  SLI4_SGE_TYPE_DISEED ; 
 void* SLI4_SGE_TYPE_SKIP ; 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 TYPE_9__* ocs_pool_get (int /*<<< orphan*/ ) ; 

uint8_t
ocs_hw_rqpair_auto_xfer_rdy_buffer_post(ocs_hw_t *hw, ocs_hw_io_t *io, int reuse_buf)
{
	ocs_hw_auto_xfer_rdy_buffer_t *buf;
	sli4_sge_t	*data;

	if(!reuse_buf) {
		buf = ocs_pool_get(hw->auto_xfer_rdy_buf_pool);
		io->axr_buf = buf;
	}

	data = io->def_sgl.virt;
	data[0].sge_type = SLI4_SGE_TYPE_SKIP;
	data[0].last = 0;

	/*
	 * Note: if we are doing DIF assists, then the SGE[1] must contain the
	 * DI_SEED SGE. The host is responsible for programming:
	 *   SGE Type (Word 2, bits 30:27)
	 *   Replacement App Tag (Word 2 bits 15:0)
	 *   App Tag (Word 3 bits 15:0)
	 *   New Ref Tag (Word 3 bit 23)
	 *   Metadata Enable (Word 3 bit 20)
	 *   Auto-Increment RefTag (Word 3 bit 19)
	 *   Block Size (Word 3 bits 18:16)
	 * The following fields are managed by the SLI Port:
	 *    Ref Tag Compare (Word 0)
	 *    Replacement Ref Tag (Word 1) - In not the LBA
	 *    NA (Word 2 bit 25)
	 *    Opcode RX (Word 3 bits 27:24)
	 *    Checksum Enable (Word 3 bit 22)
	 *    RefTag Enable (Word 3 bit 21)
	 *
	 * The first two SGLs are cleared by ocs_hw_io_init_sges(), so assume eveything is cleared.
	 */
	if (hw->config.auto_xfer_rdy_p_type) {
		sli4_diseed_sge_t *diseed = (sli4_diseed_sge_t*)&data[1];

		diseed->sge_type = SLI4_SGE_TYPE_DISEED;
		diseed->repl_app_tag = hw->config.auto_xfer_rdy_app_tag_value;
		diseed->app_tag_cmp = hw->config.auto_xfer_rdy_app_tag_value;
		diseed->check_app_tag = hw->config.auto_xfer_rdy_app_tag_valid;
		diseed->auto_incr_ref_tag = TRUE; /* Always the LBA */
		diseed->dif_blk_size = hw->config.auto_xfer_rdy_blk_size_chip;
	} else {
		data[1].sge_type = SLI4_SGE_TYPE_SKIP;
		data[1].last = 0;
	}

	data[2].sge_type = SLI4_SGE_TYPE_DATA;
	data[2].buffer_address_high = ocs_addr32_hi(io->axr_buf->payload.dma.phys);
	data[2].buffer_address_low  = ocs_addr32_lo(io->axr_buf->payload.dma.phys);
	data[2].buffer_length = io->axr_buf->payload.dma.size;
	data[2].last = TRUE;
	data[3].sge_type = SLI4_SGE_TYPE_SKIP;

	return 0;
}