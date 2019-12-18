#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sli4_sge_t ;
struct TYPE_11__ {int segment_length; scalar_t__ last; int /*<<< orphan*/  sge_type; int /*<<< orphan*/  buffer_address_low; int /*<<< orphan*/  buffer_address_high; } ;
typedef  TYPE_2__ sli4_lsp_sge_t ;
struct TYPE_12__ {int /*<<< orphan*/  sli; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_13__ {int def_sgl_count; int n_sge; int /*<<< orphan*/  ovfl_sgl_count; int /*<<< orphan*/  sgl_count; TYPE_1__* ovfl_sgl; TYPE_1__* sgl; TYPE_2__* ovfl_lsp; TYPE_8__* ovfl_io; } ;
typedef  TYPE_4__ ocs_hw_io_t ;
struct TYPE_10__ {int /*<<< orphan*/  phys; scalar_t__ virt; } ;
struct TYPE_14__ {int /*<<< orphan*/  indicator; int /*<<< orphan*/  def_sgl_count; TYPE_1__ def_sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_VF ; 
 int /*<<< orphan*/  SLI4_SGE_TYPE_LSP ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 TYPE_8__* ocs_hw_io_alloc (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sli_get_if_type (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_sgl_preregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_skh_chain_sge_build (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_io_overflow_sgl(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	sli4_lsp_sge_t *lsp;

	/* fail if we're already pointing to the overflow SGL */
	if (io->sgl == io->ovfl_sgl) {
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * For skyhawk, we can use another SGL to extend the SGL list. The
	 * Chained entry must not be in the first 4 entries.
	 *
	 * Note: For DIF enabled IOs, we will use the ovfl_io for the sec_hio.
	 */
	if (sli_get_sgl_preregister(&hw->sli) &&
	    io->def_sgl_count > 4 &&
	    io->ovfl_io == NULL &&
	    ((SLI4_IF_TYPE_BE3_SKH_PF == sli_get_if_type(&hw->sli)) ||
		(SLI4_IF_TYPE_BE3_SKH_VF == sli_get_if_type(&hw->sli)))) {
		io->ovfl_io = ocs_hw_io_alloc(hw);
		if (io->ovfl_io != NULL) {
			/*
			 * Note: We can't call ocs_hw_io_register_sgl() here
			 * because it checks that SGLs are not pre-registered
			 * and for shyhawk, preregistered SGLs are required.
			 */
			io->ovfl_sgl = &io->ovfl_io->def_sgl;
			io->ovfl_sgl_count = io->ovfl_io->def_sgl_count;
		}
	}

	/* fail if we don't have an overflow SGL registered */
	if (io->ovfl_io == NULL || io->ovfl_sgl == NULL) {
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Overflow, we need to put a link SGE in the last location of the current SGL, after
	 * copying the the last SGE to the overflow SGL
	 */

	((sli4_sge_t*)io->ovfl_sgl->virt)[0] = ((sli4_sge_t*)io->sgl->virt)[io->n_sge - 1];

	lsp = &((sli4_lsp_sge_t*)io->sgl->virt)[io->n_sge - 1];
	ocs_memset(lsp, 0, sizeof(*lsp));

	if ((SLI4_IF_TYPE_BE3_SKH_PF == sli_get_if_type(&hw->sli)) ||
	    (SLI4_IF_TYPE_BE3_SKH_VF == sli_get_if_type(&hw->sli))) {
		sli_skh_chain_sge_build(&hw->sli,
					(sli4_sge_t*)lsp,
					io->ovfl_io->indicator,
					0, /* frag_num */
					0); /* offset */
	} else {
		lsp->buffer_address_high = ocs_addr32_hi(io->ovfl_sgl->phys);
		lsp->buffer_address_low  = ocs_addr32_lo(io->ovfl_sgl->phys);
		lsp->sge_type = SLI4_SGE_TYPE_LSP;
		lsp->last = 0;
		io->ovfl_lsp = lsp;
		io->ovfl_lsp->segment_length = sizeof(sli4_sge_t);
	}

	/* Update the current SGL pointer, and n_sgl */
	io->sgl = io->ovfl_sgl;
	io->sgl_count = io->ovfl_sgl_count;
	io->n_sge = 1;

	return OCS_HW_RTN_SUCCESS;
}