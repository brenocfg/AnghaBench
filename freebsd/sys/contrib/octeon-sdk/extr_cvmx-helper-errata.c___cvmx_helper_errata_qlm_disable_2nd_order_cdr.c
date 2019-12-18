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
struct TYPE_3__ {scalar_t__ select; } ;
struct TYPE_4__ {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cvmx_ciu_qlm_jtgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_QLM_JTGD ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_init () ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_shift (int,int,int) ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_shift_zeros (int,int) ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_update (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

void __cvmx_helper_errata_qlm_disable_2nd_order_cdr(int qlm)
{
    int lane;
    /* Apply the workaround only once. */
    cvmx_ciu_qlm_jtgd_t qlm_jtgd;
    qlm_jtgd.u64 = cvmx_read_csr(CVMX_CIU_QLM_JTGD);
    if (qlm_jtgd.s.select != 0)
        return;

    cvmx_helper_qlm_jtag_init();
    /* We need to load all four lanes of the QLM, a total of 1072 bits */
    for (lane=0; lane<4; lane++)
    {
        /* Each lane has 268 bits. We need to set cfg_cdr_incx<67:64>=3 and
            cfg_cdr_secord<77>=1. All other bits are zero. Bits go in LSB
            first, so start off with the zeros for bits <63:0> */
        cvmx_helper_qlm_jtag_shift_zeros(qlm, 63 - 0 + 1);
        /* cfg_cdr_incx<67:64>=3 */
        cvmx_helper_qlm_jtag_shift(qlm, 67 - 64 + 1, 3);
        /* Zeros for bits <76:68> */
        cvmx_helper_qlm_jtag_shift_zeros(qlm, 76 - 68 + 1);
        /* cfg_cdr_secord<77>=1 */
        cvmx_helper_qlm_jtag_shift(qlm, 77 - 77 + 1, 1);
        /* Zeros for bits <267:78> */
        cvmx_helper_qlm_jtag_shift_zeros(qlm, 267 - 78 + 1);
    }
    cvmx_helper_qlm_jtag_update(qlm);
}