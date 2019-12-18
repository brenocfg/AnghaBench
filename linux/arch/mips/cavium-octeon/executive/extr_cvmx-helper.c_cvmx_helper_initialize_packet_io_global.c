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
struct TYPE_2__ {scalar_t__ rfb_arb_mode; scalar_t__ lrf_arb_mode; } ;
union cvmx_l2c_cfg {int /*<<< orphan*/  u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_CFG ; 
 int /*<<< orphan*/  OCTEON_CN52XX_PASS1_0 ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_helper_errata_qlm_disable_2nd_order_cdr (int) ; 
 int __cvmx_helper_global_setup_backpressure () ; 
 int __cvmx_helper_global_setup_ipd () ; 
 int __cvmx_helper_global_setup_pko () ; 
 int __cvmx_helper_interface_setup_ipd (int) ; 
 int __cvmx_helper_interface_setup_pko (int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_number_of_interfaces () ; 
 int /*<<< orphan*/  cvmx_helper_interface_get_mode (int) ; 
 int /*<<< orphan*/  cvmx_helper_interface_mode_to_string (int /*<<< orphan*/ ) ; 
 int cvmx_helper_interface_probe (int) ; 
 int cvmx_helper_ipd_and_packet_input_enable () ; 
 scalar_t__ cvmx_helper_ports_on_interface (int) ; 
 int /*<<< orphan*/  cvmx_pko_initialize_global () ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cvmx_helper_initialize_packet_io_global(void)
{
	int result = 0;
	int interface;
	union cvmx_l2c_cfg l2c_cfg;
	const int num_interfaces = cvmx_helper_get_number_of_interfaces();

	/*
	 * CN52XX pass 1: Due to a bug in 2nd order CDR, it needs to
	 * be disabled.
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN52XX_PASS1_0))
		__cvmx_helper_errata_qlm_disable_2nd_order_cdr(1);

	/*
	 * Tell L2 to give the IOB statically higher priority compared
	 * to the cores. This avoids conditions where IO blocks might
	 * be starved under very high L2 loads.
	 */
	l2c_cfg.u64 = cvmx_read_csr(CVMX_L2C_CFG);
	l2c_cfg.s.lrf_arb_mode = 0;
	l2c_cfg.s.rfb_arb_mode = 0;
	cvmx_write_csr(CVMX_L2C_CFG, l2c_cfg.u64);

	cvmx_pko_initialize_global();
	for (interface = 0; interface < num_interfaces; interface++) {
		result |= cvmx_helper_interface_probe(interface);
		if (cvmx_helper_ports_on_interface(interface) > 0)
			cvmx_dprintf("Interface %d has %d ports (%s)\n",
				     interface,
				     cvmx_helper_ports_on_interface(interface),
				     cvmx_helper_interface_mode_to_string
				     (cvmx_helper_interface_get_mode
				      (interface)));
		result |= __cvmx_helper_interface_setup_ipd(interface);
		result |= __cvmx_helper_interface_setup_pko(interface);
	}

	result |= __cvmx_helper_global_setup_ipd();
	result |= __cvmx_helper_global_setup_pko();

	/* Enable any flow control and backpressure */
	result |= __cvmx_helper_global_setup_backpressure();

#if CVMX_HELPER_ENABLE_IPD
	result |= cvmx_helper_ipd_and_packet_input_enable();
#endif
	return result;
}