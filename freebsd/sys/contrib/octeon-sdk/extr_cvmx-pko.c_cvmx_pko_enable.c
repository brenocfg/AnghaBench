#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ena_pko; int store_be; int /*<<< orphan*/  ena_dwb; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_pko_reg_flags_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_HELPER_CFG_OPT_USE_DWB ; 
 int /*<<< orphan*/  CVMX_PKO_REG_FLAGS ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int /*<<< orphan*/  cvmx_helper_cfg_opt_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvmx_pko_enable(void)
{
    cvmx_pko_reg_flags_t flags;

    flags.u64 = cvmx_read_csr(CVMX_PKO_REG_FLAGS);
    if (flags.s.ena_pko)
        cvmx_dprintf("Warning: Enabling PKO when PKO already enabled.\n");

    flags.s.ena_dwb = cvmx_helper_cfg_opt_get(CVMX_HELPER_CFG_OPT_USE_DWB);
    flags.s.ena_pko = 1;
    flags.s.store_be =1;  /*
    			   * always enable big endian for 3-word command.
			   * Does nothing for 2-word.
    			   */
    cvmx_write_csr(CVMX_PKO_REG_FLAGS, flags.u64);
}