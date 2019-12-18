#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_11__ {void* last; void* sge_type; int /*<<< orphan*/  buffer_length; int /*<<< orphan*/  buffer_address_low; int /*<<< orphan*/  buffer_address_high; } ;
typedef  TYPE_3__ sli4_sge_t ;
struct TYPE_12__ {int /*<<< orphan*/ * os; } ;
typedef  TYPE_4__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
typedef  int ocs_hw_io_type_e ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/  phys; } ;
struct TYPE_9__ {TYPE_3__* virt; } ;
struct TYPE_13__ {int n_sge; int type; TYPE_2__ xfer_rdy; TYPE_1__* sgl; scalar_t__ sge_offset; scalar_t__ first_data_sge; int /*<<< orphan*/  def_sgl_count; int /*<<< orphan*/  sgl_count; TYPE_1__ def_sgl; } ;
typedef  TYPE_5__ ocs_hw_io_t ;

/* Variables and functions */
#define  OCS_HW_IO_INITIATOR_NODATA 133 
#define  OCS_HW_IO_INITIATOR_READ 132 
#define  OCS_HW_IO_INITIATOR_WRITE 131 
#define  OCS_HW_IO_TARGET_READ 130 
#define  OCS_HW_IO_TARGET_RSP 129 
#define  OCS_HW_IO_TARGET_WRITE 128 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 scalar_t__ OCS_TARGET_READ_SKIPS ; 
 scalar_t__ OCS_TARGET_WRITE_SKIPS ; 
 void* SLI4_SGE_TYPE_DATA ; 
 void* SLI4_SGE_TYPE_SKIP ; 
 void* TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

ocs_hw_rtn_e
ocs_hw_io_init_sges(ocs_hw_t *hw, ocs_hw_io_t *io, ocs_hw_io_type_e type)
{
	sli4_sge_t	*data = NULL;
	uint32_t	i = 0;
	uint32_t	skips = 0;

	if (!hw || !io) {
		ocs_log_err(hw ? hw->os : NULL, "bad parameter hw=%p io=%p\n",
			    hw, io);
		return OCS_HW_RTN_ERROR;
	}

	/* Clear / reset the scatter-gather list */
	io->sgl = &io->def_sgl;
	io->sgl_count = io->def_sgl_count;
	io->first_data_sge = 0;

	ocs_memset(io->sgl->virt, 0, 2 * sizeof(sli4_sge_t));
	io->n_sge = 0;
	io->sge_offset = 0;

	io->type = type;

	data = io->sgl->virt;

	/*
	 * Some IO types have underlying hardware requirements on the order
	 * of SGEs. Process all special entries here.
	 */
	switch (type) {
	case OCS_HW_IO_INITIATOR_READ:
	case OCS_HW_IO_INITIATOR_WRITE:
	case OCS_HW_IO_INITIATOR_NODATA:
		/*
		 * No skips, 2 special for initiator I/Os
		 * The addresses and length are written later
		 */
		/* setup command pointer */
		data->sge_type = SLI4_SGE_TYPE_DATA;
		data++;

		/* setup response pointer */
		data->sge_type = SLI4_SGE_TYPE_DATA;

		if (OCS_HW_IO_INITIATOR_NODATA == type) {
			data->last = TRUE;
		}
		data++;

		io->n_sge = 2;
		break;
	case OCS_HW_IO_TARGET_WRITE:
#define OCS_TARGET_WRITE_SKIPS	2
		skips = OCS_TARGET_WRITE_SKIPS;

		/* populate host resident XFER_RDY buffer */
		data->sge_type = SLI4_SGE_TYPE_DATA;
		data->buffer_address_high = ocs_addr32_hi(io->xfer_rdy.phys);
		data->buffer_address_low  = ocs_addr32_lo(io->xfer_rdy.phys);
		data->buffer_length = io->xfer_rdy.size;
		data++;

		skips--;

		io->n_sge = 1;
		break;
	case OCS_HW_IO_TARGET_READ:
		/*
		 * For FCP_TSEND64, the first 2 entries are SKIP SGE's
		 */
#define OCS_TARGET_READ_SKIPS	2
		skips = OCS_TARGET_READ_SKIPS;
		break;
	case OCS_HW_IO_TARGET_RSP:
		/*
		 * No skips, etc. for FCP_TRSP64
		 */
		break;
	default:
		ocs_log_err(hw->os, "unsupported IO type %#x\n", type);
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Write skip entries
	 */
	for (i = 0; i < skips; i++) {
		data->sge_type = SLI4_SGE_TYPE_SKIP;
		data++;
	}

	io->n_sge += skips;

	/*
	 * Set last
	 */
	data->last = TRUE;

	return OCS_HW_RTN_SUCCESS;
}