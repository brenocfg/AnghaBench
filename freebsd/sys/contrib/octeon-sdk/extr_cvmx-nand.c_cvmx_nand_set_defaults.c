#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cvmx_nand_status_t ;
struct TYPE_2__ {int page_size; int oob_size; int pages_per_block; int blocks; int onfi_timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NAND_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_NAND_SUCCESS ; 
 TYPE_1__ cvmx_nand_default ; 

cvmx_nand_status_t cvmx_nand_set_defaults(int page_size, int oob_size, int pages_per_block, int blocks, int onfi_timing_mode)
{
    if (!page_size || !oob_size || !pages_per_block || !blocks || onfi_timing_mode > 5)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);

    cvmx_nand_default.page_size = page_size;
    cvmx_nand_default.oob_size = oob_size;
    cvmx_nand_default.pages_per_block = pages_per_block;
    cvmx_nand_default.blocks = blocks;
    cvmx_nand_default.onfi_timing = onfi_timing_mode;

    CVMX_NAND_RETURN(CVMX_NAND_SUCCESS);
}