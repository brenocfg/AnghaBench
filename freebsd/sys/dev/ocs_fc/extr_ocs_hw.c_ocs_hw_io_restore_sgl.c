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
typedef  int /*<<< orphan*/  ocs_hw_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ovfl_lsp; scalar_t__ ovfl_sgl_count; int /*<<< orphan*/ * ovfl_sgl; int /*<<< orphan*/ * ovfl_io; int /*<<< orphan*/  def_sgl_count; int /*<<< orphan*/  sgl_count; int /*<<< orphan*/  def_sgl; int /*<<< orphan*/ * sgl; } ;
typedef  TYPE_1__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_io_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_hw_io_restore_sgl(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	/* Restore the default */
	io->sgl = &io->def_sgl;
	io->sgl_count = io->def_sgl_count;

	/*
	 * For skyhawk, we need to free the IO allocated for the chained
	 * SGL. For all devices, clear the overflow fields on the IO.
	 *
	 * Note: For DIF IOs, we may be using the same XRI for the sec_hio and
	 *       the chained SGLs. If so, then we clear the ovfl_io field
	 *       when the sec_hio is freed.
	 */
	if (io->ovfl_io != NULL) {
		ocs_hw_io_free(hw, io->ovfl_io);
		io->ovfl_io = NULL;
	}

	/* Clear the overflow SGL */
	io->ovfl_sgl = NULL;
	io->ovfl_sgl_count = 0;
	io->ovfl_lsp = NULL;
}