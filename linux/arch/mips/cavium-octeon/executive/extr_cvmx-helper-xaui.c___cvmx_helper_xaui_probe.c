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
struct TYPE_3__ {int qos_mask; int eid; int pid; scalar_t__ static_p; } ;
union cvmx_pko_mem_port_ptrs {scalar_t__ u64; TYPE_1__ s; } ;
struct TYPE_4__ {int en; } ;
union cvmx_gmxx_inf_mode {scalar_t__ u64; TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_INF_MODE (int) ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_PORT_PTRS ; 
 int /*<<< orphan*/  __cvmx_helper_setup_gmx (int,int) ; 
 int __cvmx_helper_xaui_enumerate (int) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

int __cvmx_helper_xaui_probe(int interface)
{
	int i;
	union cvmx_gmxx_inf_mode mode;

	/*
	 * Due to errata GMX-700 on CN56XXp1.x and CN52XXp1.x, the
	 * interface needs to be enabled before IPD otherwise per port
	 * backpressure may not work properly.
	 */
	mode.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(interface));
	mode.s.en = 1;
	cvmx_write_csr(CVMX_GMXX_INF_MODE(interface), mode.u64);

	__cvmx_helper_setup_gmx(interface, 1);

	/*
	 * Setup PKO to support 16 ports for HiGig2 virtual
	 * ports. We're pointing all of the PKO packet ports for this
	 * interface to the XAUI. This allows us to use HiGig2
	 * backpressure per port.
	 */
	for (i = 0; i < 16; i++) {
		union cvmx_pko_mem_port_ptrs pko_mem_port_ptrs;
		pko_mem_port_ptrs.u64 = 0;
		/*
		 * We set each PKO port to have equal priority in a
		 * round robin fashion.
		 */
		pko_mem_port_ptrs.s.static_p = 0;
		pko_mem_port_ptrs.s.qos_mask = 0xff;
		/* All PKO ports map to the same XAUI hardware port */
		pko_mem_port_ptrs.s.eid = interface * 4;
		pko_mem_port_ptrs.s.pid = interface * 16 + i;
		cvmx_write_csr(CVMX_PKO_MEM_PORT_PTRS, pko_mem_port_ptrs.u64);
	}
	return __cvmx_helper_xaui_enumerate(interface);
}