#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
struct TYPE_8__ {int clr_boot; } ;
struct TYPE_10__ {void* u64; TYPE_2__ s; } ;
typedef  TYPE_4__ cvmx_spxx_trn4_ctl_t ;
struct TYPE_9__ {scalar_t__ srxtrn; } ;
struct TYPE_11__ {TYPE_3__ s; void* u64; } ;
typedef  TYPE_5__ cvmx_spxx_clk_stat_t ;
struct TYPE_7__ {int clkdly; int statrcv; int sndtrn; int drptrn; int rcvtrn; int srxdlck; scalar_t__ statdrv; scalar_t__ runbist; scalar_t__ seetrn; } ;
struct TYPE_12__ {void* u64; TYPE_1__ s; } ;
typedef  TYPE_6__ cvmx_spxx_clk_ctl_t ;
typedef  int /*<<< orphan*/  cvmx_spi_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CLOCK_CORE ; 
 int /*<<< orphan*/  CVMX_SPXX_CLK_CTL (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_CLK_STAT (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_TRN4_CTL (int) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 unsigned long long cvmx_get_cycle () ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

int cvmx_spi_training_cb(int interface, cvmx_spi_mode_t mode, int timeout)
{
    cvmx_spxx_trn4_ctl_t         spxx_trn4_ctl;
    cvmx_spxx_clk_stat_t         stat;
    uint64_t                     MS = cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000;
    uint64_t                     timeout_time = cvmx_get_cycle() + 1000ull * MS * timeout;
    int                          rx_training_needed;

    // SRX0 & STX0 Inf0 Links are configured - begin training
    cvmx_spxx_clk_ctl_t spxx_clk_ctl;
    spxx_clk_ctl.u64 = 0;
    spxx_clk_ctl.s.seetrn = 0;
    spxx_clk_ctl.s.clkdly = 0x10;
    spxx_clk_ctl.s.runbist = 0;
    spxx_clk_ctl.s.statdrv = 0;
    spxx_clk_ctl.s.statrcv = 1; /* This should always be on the opposite edge as statdrv */
    spxx_clk_ctl.s.sndtrn = 1;
    spxx_clk_ctl.s.drptrn = 1;
    spxx_clk_ctl.s.rcvtrn = 1;
    spxx_clk_ctl.s.srxdlck = 1;
    cvmx_write_csr(CVMX_SPXX_CLK_CTL(interface), spxx_clk_ctl.u64);
    cvmx_wait (1000 * MS);

    // SRX0 clear the boot bit
    spxx_trn4_ctl.u64 = cvmx_read_csr(CVMX_SPXX_TRN4_CTL(interface));
    spxx_trn4_ctl.s.clr_boot = 1;
    cvmx_write_csr (CVMX_SPXX_TRN4_CTL(interface), spxx_trn4_ctl.u64);

    // Wait for the training sequence to complete
    cvmx_dprintf ("SPI%d: Waiting for training\n", interface);
    cvmx_wait (1000 * MS);
#if !defined(OCTEON_VENDOR_LANNER)
    timeout_time = cvmx_get_cycle() + 1000ull * MS * 600;  /* Wait a really long time here */
#else
    timeout_time = cvmx_get_cycle() + 1000ull * MS * 10;
#endif
    /* The HRM says we must wait for 34 + 16 * MAXDIST training sequences.
        We'll be pessimistic and wait for a lot more */
    rx_training_needed = 500;
    do {
        stat.u64 = cvmx_read_csr (CVMX_SPXX_CLK_STAT(interface));
        if (stat.s.srxtrn && rx_training_needed)
        {
            rx_training_needed--;
            cvmx_write_csr(CVMX_SPXX_CLK_STAT(interface), stat.u64);
            stat.s.srxtrn = 0;
        }
        if (cvmx_get_cycle() > timeout_time)
        {
            cvmx_dprintf ("SPI%d: Timeout\n", interface);
            return -1;
        }
    } while (stat.s.srxtrn == 0);

    return 0;
}