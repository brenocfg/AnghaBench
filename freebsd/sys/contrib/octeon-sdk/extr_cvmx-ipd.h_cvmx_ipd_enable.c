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
struct TYPE_3__ {scalar_t__ rst_done; int ipd_en; int len_m8; } ;
struct TYPE_4__ {void* u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_ipd_ctl_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IPD_CTL_STATUS ; 
 int /*<<< orphan*/  OCTEON_CN38XX_PASS2 ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void cvmx_ipd_enable(void)
{
    cvmx_ipd_ctl_status_t ipd_reg;

    ipd_reg.u64 = cvmx_read_csr(CVMX_IPD_CTL_STATUS);

    /*
     * busy-waiting for rst_done in o68
     */
    if (OCTEON_IS_MODEL(OCTEON_CN68XX))
        while(ipd_reg.s.rst_done != 0)
            ipd_reg.u64 = cvmx_read_csr(CVMX_IPD_CTL_STATUS);

    if (ipd_reg.s.ipd_en)
        cvmx_dprintf("Warning: Enabling IPD when IPD already enabled.\n");

    ipd_reg.s.ipd_en = 1;

#if  CVMX_ENABLE_LEN_M8_FIX
    if(!OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2))
        ipd_reg.s.len_m8 = 1;
#endif

    cvmx_write_csr(CVMX_IPD_CTL_STATUS, ipd_reg.u64);
}