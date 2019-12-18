#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int st_en; } ;
union cvmx_stxx_com_ctl {void* u64; TYPE_2__ s; } ;
struct TYPE_5__ {int inf_en; int st_en; } ;
union cvmx_srxx_com_ctl {void* u64; TYPE_1__ s; } ;
struct TYPE_7__ {scalar_t__ stxcal; } ;
union cvmx_spxx_clk_stat {void* u64; TYPE_3__ s; } ;
typedef  unsigned long long uint64_t ;
typedef  int cvmx_spi_mode_t ;
struct TYPE_8__ {int cpu_clock_hz; } ;

/* Variables and functions */
 int CVMX_SPI_MODE_RX_HALFPLEX ; 
 int CVMX_SPI_MODE_TX_HALFPLEX ; 
 int /*<<< orphan*/  CVMX_SPXX_CLK_STAT (int) ; 
 int /*<<< orphan*/  CVMX_SRXX_COM_CTL (int) ; 
 int /*<<< orphan*/  CVMX_STXX_COM_CTL (int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,...) ; 
 unsigned long long cvmx_get_cycle () ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_4__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

int cvmx_spi_calendar_sync_cb(int interface, cvmx_spi_mode_t mode, int timeout)
{
	uint64_t MS = cvmx_sysinfo_get()->cpu_clock_hz / 1000;
	if (mode & CVMX_SPI_MODE_RX_HALFPLEX) {
		/* SRX0 interface should be good, send calendar data */
		union cvmx_srxx_com_ctl srxx_com_ctl;
		cvmx_dprintf
		    ("SPI%d: Rx is synchronized, start sending calendar data\n",
		     interface);
		srxx_com_ctl.u64 = cvmx_read_csr(CVMX_SRXX_COM_CTL(interface));
		srxx_com_ctl.s.inf_en = 1;
		srxx_com_ctl.s.st_en = 1;
		cvmx_write_csr(CVMX_SRXX_COM_CTL(interface), srxx_com_ctl.u64);
	}

	if (mode & CVMX_SPI_MODE_TX_HALFPLEX) {
		/* STX0 has achieved sync */
		/* The corespondant board should be sending calendar data */
		/* Enable the STX0 STAT receiver. */
		union cvmx_spxx_clk_stat stat;
		uint64_t timeout_time;
		union cvmx_stxx_com_ctl stxx_com_ctl;
		stxx_com_ctl.u64 = 0;
		stxx_com_ctl.s.st_en = 1;
		cvmx_write_csr(CVMX_STXX_COM_CTL(interface), stxx_com_ctl.u64);

		/* Waiting for calendar sync on STX0 STAT */
		cvmx_dprintf("SPI%d: Waiting to sync on STX[%d] STAT\n",
			     interface, interface);
		timeout_time = cvmx_get_cycle() + 1000ull * MS * timeout;
		/* SPX0_CLK_STAT - SPX0_CLK_STAT[STXCAL] should be 1 (bit10) */
		do {
			stat.u64 = cvmx_read_csr(CVMX_SPXX_CLK_STAT(interface));
			if (cvmx_get_cycle() > timeout_time) {
				cvmx_dprintf("SPI%d: Timeout\n", interface);
				return -1;
			}
		} while (stat.s.stxcal == 0);
	}

	return 0;
}