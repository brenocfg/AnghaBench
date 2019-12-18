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
struct TYPE_2__ {scalar_t__ minerr_en; scalar_t__ maxerr_en; } ;
union cvmx_pip_prt_cfgx {int /*<<< orphan*/  u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_PRT_CFGX (int) ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_ipd_port (int,int) ; 
 int cvmx_helper_ports_on_interface (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __cvmx_helper_npi_enable(int interface)
{
	/*
	 * On CN50XX, CN52XX, and CN56XX we need to disable length
	 * checking so packet < 64 bytes and jumbo frames don't get
	 * errors.
	 */
	if (!OCTEON_IS_MODEL(OCTEON_CN3XXX) &&
	    !OCTEON_IS_MODEL(OCTEON_CN58XX)) {
		int num_ports = cvmx_helper_ports_on_interface(interface);
		int port;
		for (port = 0; port < num_ports; port++) {
			union cvmx_pip_prt_cfgx port_cfg;
			int ipd_port =
			    cvmx_helper_get_ipd_port(interface, port);
			port_cfg.u64 =
			    cvmx_read_csr(CVMX_PIP_PRT_CFGX(ipd_port));
			port_cfg.s.maxerr_en = 0;
			port_cfg.s.minerr_en = 0;
			cvmx_write_csr(CVMX_PIP_PRT_CFGX(ipd_port),
				       port_cfg.u64);
		}
	}

	/* Enables are controlled by the remote host, so nothing to do here */
	return 0;
}