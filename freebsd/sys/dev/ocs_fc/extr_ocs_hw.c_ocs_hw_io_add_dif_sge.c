#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  last; int /*<<< orphan*/  buffer_address_low; int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  sge_type; } ;
typedef  TYPE_4__ sli4_dif_sge_t ;
struct TYPE_13__ {scalar_t__ if_type; } ;
struct TYPE_11__ {scalar_t__ n_sgl; } ;
struct TYPE_15__ {TYPE_3__ sli; int /*<<< orphan*/ * os; TYPE_1__ config; } ;
typedef  TYPE_5__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
struct TYPE_16__ {scalar_t__ n_sge; scalar_t__ type; TYPE_2__* sgl; } ;
typedef  TYPE_6__ ocs_hw_io_t ;
struct TYPE_12__ {TYPE_4__* virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OCS_HW_IO_INITIATOR_READ ; 
 scalar_t__ OCS_HW_IO_TARGET_WRITE ; 
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  SLI4_SGE_TYPE_DIF ; 
 int /*<<< orphan*/  SLI4_SGE_TYPE_SKIP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (uintptr_t) ; 
 int /*<<< orphan*/  ocs_addr32_lo (uintptr_t) ; 
 scalar_t__ ocs_hw_io_overflow_sgl (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 

ocs_hw_rtn_e
ocs_hw_io_add_dif_sge(ocs_hw_t *hw, ocs_hw_io_t *io, uintptr_t addr)
{
	sli4_dif_sge_t	*data = NULL;

	if (!hw || !io || !addr) {
		ocs_log_err(hw ? hw->os : NULL,
			    "bad parameter hw=%p io=%p addr=%lx\n",
			    hw, io, addr);
		return OCS_HW_RTN_ERROR;
	}

	if ((io->n_sge + 1) > hw->config.n_sgl) {
		if (ocs_hw_io_overflow_sgl(hw, io) != OCS_HW_RTN_ERROR) {
			ocs_log_err(hw->os, "SGL full (%d)\n", io->n_sge);
			return OCS_HW_RTN_ERROR;
		}
	}

	data = io->sgl->virt;
	data += io->n_sge;

	data->sge_type = SLI4_SGE_TYPE_DIF;
	/* Workaround for SKH (BZ157233) */
	if (((io->type == OCS_HW_IO_TARGET_WRITE) || (io->type == OCS_HW_IO_INITIATOR_READ)) &&
		(SLI4_IF_TYPE_LANCER_FC_ETH != hw->sli.if_type)) {
		data->sge_type = SLI4_SGE_TYPE_SKIP;
	}

	data->buffer_address_high = ocs_addr32_hi(addr);
	data->buffer_address_low  = ocs_addr32_lo(addr);

	/*
	 * Always assume this is the last entry and mark as such.
	 * If this is not the first entry unset the "last SGE"
	 * indication for the previous entry
	 */
	data->last = TRUE;
	if (io->n_sge) {
		data[-1].last = FALSE;
	}

	io->n_sge++;

	return OCS_HW_RTN_SUCCESS;
}