#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lnk_enb; } ;
union cvmx_pemx_ctl_status {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct TYPE_6__ {int rtl; } ;
union cvmx_pciercx_cfg448 {void* u32; TYPE_3__ s; } ;
struct TYPE_5__ {scalar_t__ dlla; int lt; int nlw; } ;
union cvmx_pciercx_cfg032 {TYPE_2__ s; void* u32; } ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PCIERCX_CFG032 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG448 (int) ; 
 int /*<<< orphan*/  CVMX_PEMX_CTL_STATUS (int) ; 
 int /*<<< orphan*/  __delay (int) ; 
 scalar_t__ cvmx_get_cycle () ; 
 void* cvmx_pcie_cfgx_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_cfgx_write (int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_get_clock_rate () ; 

__attribute__((used)) static int __cvmx_pcie_rc_initialize_link_gen2(int pcie_port)
{
	uint64_t start_cycle;
	union cvmx_pemx_ctl_status pem_ctl_status;
	union cvmx_pciercx_cfg032 pciercx_cfg032;
	union cvmx_pciercx_cfg448 pciercx_cfg448;

	/* Bring up the link */
	pem_ctl_status.u64 = cvmx_read_csr(CVMX_PEMX_CTL_STATUS(pcie_port));
	pem_ctl_status.s.lnk_enb = 1;
	cvmx_write_csr(CVMX_PEMX_CTL_STATUS(pcie_port), pem_ctl_status.u64);

	/* Wait for the link to come up */
	start_cycle = cvmx_get_cycle();
	do {
		if (cvmx_get_cycle() - start_cycle >  octeon_get_clock_rate())
			return -1;
		__delay(10000);
		pciercx_cfg032.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
	} while ((pciercx_cfg032.s.dlla == 0) || (pciercx_cfg032.s.lt == 1));

	/*
	 * Update the Replay Time Limit. Empirically, some PCIe
	 * devices take a little longer to respond than expected under
	 * load. As a workaround for this we configure the Replay Time
	 * Limit to the value expected for a 512 byte MPS instead of
	 * our actual 256 byte MPS. The numbers below are directly
	 * from the PCIe spec table 3-4
	 */
	pciercx_cfg448.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG448(pcie_port));
	switch (pciercx_cfg032.s.nlw) {
	case 1: /* 1 lane */
		pciercx_cfg448.s.rtl = 1677;
		break;
	case 2: /* 2 lanes */
		pciercx_cfg448.s.rtl = 867;
		break;
	case 4: /* 4 lanes */
		pciercx_cfg448.s.rtl = 462;
		break;
	case 8: /* 8 lanes */
		pciercx_cfg448.s.rtl = 258;
		break;
	}
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG448(pcie_port), pciercx_cfg448.u32);

	return 0;
}