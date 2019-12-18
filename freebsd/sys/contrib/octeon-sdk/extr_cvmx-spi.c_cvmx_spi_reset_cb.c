#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_20__ {int oddpar; } ;
struct TYPE_23__ {void* u64; TYPE_3__ s; } ;
typedef  TYPE_6__ cvmx_stxx_spi4_calx_t ;
struct TYPE_24__ {void* u64; } ;
typedef  TYPE_7__ cvmx_stxx_int_msk_t ;
struct TYPE_19__ {int oddpar; } ;
struct TYPE_25__ {void* u64; TYPE_2__ s; } ;
typedef  TYPE_8__ cvmx_srxx_spi4_calx_t ;
struct TYPE_22__ {int jitter; int clr_boot; int maxdist; int macro_en; int mux_en; scalar_t__ set_boot; scalar_t__ trntest; } ;
struct TYPE_26__ {void* u64; TYPE_5__ s; } ;
typedef  TYPE_9__ cvmx_spxx_trn4_ctl_t ;
struct TYPE_14__ {void* u64; } ;
typedef  TYPE_10__ cvmx_spxx_int_msk_t ;
struct TYPE_15__ {void* u64; } ;
typedef  TYPE_11__ cvmx_spxx_dbg_deskew_ctl_t ;
struct TYPE_21__ {int runbist; int clkdly; int statrcv; int srxdlck; scalar_t__ rcvtrn; scalar_t__ drptrn; scalar_t__ sndtrn; scalar_t__ statdrv; scalar_t__ seetrn; } ;
struct TYPE_16__ {void* u64; TYPE_4__ s; } ;
typedef  TYPE_12__ cvmx_spxx_clk_ctl_t ;
struct TYPE_18__ {scalar_t__ stat2; scalar_t__ stat1; scalar_t__ stat0; } ;
struct TYPE_17__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_13__ cvmx_spxx_bist_stat_t ;
typedef  int /*<<< orphan*/  cvmx_spi_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CLOCK_CORE ; 
 int /*<<< orphan*/  CVMX_SPXX_BIST_STAT (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_CLK_CTL (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_DBG_DESKEW_CTL (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_INT_MSK (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_INT_REG (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_TRN4_CTL (int) ; 
 int /*<<< orphan*/  CVMX_SRXX_COM_CTL (int) ; 
 int /*<<< orphan*/  CVMX_SRXX_SPI4_CALX (int,int) ; 
 int /*<<< orphan*/  CVMX_STXX_COM_CTL (int) ; 
 int /*<<< orphan*/  CVMX_STXX_INT_MSK (int) ; 
 int /*<<< orphan*/  CVMX_STXX_INT_REG (int) ; 
 int /*<<< orphan*/  CVMX_STXX_SPI4_CALX (int,int) ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

int cvmx_spi_reset_cb(int interface, cvmx_spi_mode_t mode)
{
    cvmx_spxx_dbg_deskew_ctl_t spxx_dbg_deskew_ctl;
    cvmx_spxx_clk_ctl_t spxx_clk_ctl;
    cvmx_spxx_bist_stat_t spxx_bist_stat;
    cvmx_spxx_int_msk_t spxx_int_msk;
    cvmx_stxx_int_msk_t stxx_int_msk;
    cvmx_spxx_trn4_ctl_t spxx_trn4_ctl;
    int index;
    uint64_t MS = cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000;

    /* Disable SPI error events while we run BIST */
    spxx_int_msk.u64 = cvmx_read_csr(CVMX_SPXX_INT_MSK(interface));
    cvmx_write_csr(CVMX_SPXX_INT_MSK(interface), 0);
    stxx_int_msk.u64 = cvmx_read_csr(CVMX_STXX_INT_MSK(interface));
    cvmx_write_csr(CVMX_STXX_INT_MSK(interface), 0);

    /* Run BIST in the SPI interface */
    cvmx_write_csr(CVMX_SRXX_COM_CTL(interface), 0);
    cvmx_write_csr(CVMX_STXX_COM_CTL(interface), 0);
    spxx_clk_ctl.u64 = 0;
    spxx_clk_ctl.s.runbist = 1;
    cvmx_write_csr(CVMX_SPXX_CLK_CTL(interface), spxx_clk_ctl.u64);
    cvmx_wait (10 * MS);
    spxx_bist_stat.u64 = cvmx_read_csr(CVMX_SPXX_BIST_STAT(interface));
    if (spxx_bist_stat.s.stat0)
        cvmx_dprintf("ERROR SPI%d: BIST failed on receive datapath FIFO\n", interface);
    if (spxx_bist_stat.s.stat1)
        cvmx_dprintf("ERROR SPI%d: BIST failed on RX calendar table\n", interface);
    if (spxx_bist_stat.s.stat2)
        cvmx_dprintf("ERROR SPI%d: BIST failed on TX calendar table\n", interface);

    /* Clear the calendar table after BIST to fix parity errors */
    for (index=0; index<32; index++)
    {
        cvmx_srxx_spi4_calx_t srxx_spi4_calx;
        cvmx_stxx_spi4_calx_t stxx_spi4_calx;

        srxx_spi4_calx.u64 = 0;
        srxx_spi4_calx.s.oddpar = 1;
        cvmx_write_csr(CVMX_SRXX_SPI4_CALX(index, interface), srxx_spi4_calx.u64);

        stxx_spi4_calx.u64 = 0;
        stxx_spi4_calx.s.oddpar = 1;
        cvmx_write_csr(CVMX_STXX_SPI4_CALX(index, interface), stxx_spi4_calx.u64);
    }

    /* Re enable reporting of error interrupts */
    cvmx_write_csr(CVMX_SPXX_INT_REG(interface), cvmx_read_csr(CVMX_SPXX_INT_REG(interface)));
    cvmx_write_csr(CVMX_SPXX_INT_MSK(interface), spxx_int_msk.u64);
    cvmx_write_csr(CVMX_STXX_INT_REG(interface), cvmx_read_csr(CVMX_STXX_INT_REG(interface)));
    cvmx_write_csr(CVMX_STXX_INT_MSK(interface), stxx_int_msk.u64);

    // Setup the CLKDLY right in the middle
    spxx_clk_ctl.u64 = 0;
    spxx_clk_ctl.s.seetrn = 0;
    spxx_clk_ctl.s.clkdly = 0x10;
    spxx_clk_ctl.s.runbist = 0;
    spxx_clk_ctl.s.statdrv = 0;
    spxx_clk_ctl.s.statrcv = 1; /* This should always be on the opposite edge as statdrv */
    spxx_clk_ctl.s.sndtrn = 0;
    spxx_clk_ctl.s.drptrn = 0;
    spxx_clk_ctl.s.rcvtrn = 0;
    spxx_clk_ctl.s.srxdlck = 0;
    cvmx_write_csr(CVMX_SPXX_CLK_CTL(interface), spxx_clk_ctl.u64);
    cvmx_wait (100 * MS);

    // Reset SRX0 DLL
    spxx_clk_ctl.s.srxdlck = 1;
    cvmx_write_csr(CVMX_SPXX_CLK_CTL(interface), spxx_clk_ctl.u64);

    // Waiting for Inf0 Spi4 RX DLL to lock
    cvmx_wait (100 * MS);

    // Enable dynamic alignment
    spxx_trn4_ctl.s.trntest = 0;
    spxx_trn4_ctl.s.jitter = 1;
    spxx_trn4_ctl.s.clr_boot = 1;
    spxx_trn4_ctl.s.set_boot = 0;
    if (OCTEON_IS_MODEL(OCTEON_CN58XX))
        spxx_trn4_ctl.s.maxdist = 3;
    else
        spxx_trn4_ctl.s.maxdist = 8;
    spxx_trn4_ctl.s.macro_en = 1;
    spxx_trn4_ctl.s.mux_en = 1;
    cvmx_write_csr (CVMX_SPXX_TRN4_CTL(interface), spxx_trn4_ctl.u64);

    spxx_dbg_deskew_ctl.u64 = 0;
    cvmx_write_csr (CVMX_SPXX_DBG_DESKEW_CTL(interface), spxx_dbg_deskew_ctl.u64);

    return 0;
}