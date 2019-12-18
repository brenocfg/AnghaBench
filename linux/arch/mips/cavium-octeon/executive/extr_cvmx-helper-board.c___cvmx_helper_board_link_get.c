#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; int duplex; int speed; } ;
union cvmx_gmxx_rxx_rx_inbnd {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
struct TYPE_6__ {int link_up; int full_duplex; int speed; } ;
struct TYPE_7__ {scalar_t__ u64; TYPE_2__ s; } ;
typedef  TYPE_3__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_RX_INBND (int,int) ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN50XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_is_simulation () ; 

cvmx_helper_link_info_t __cvmx_helper_board_link_get(int ipd_port)
{
	cvmx_helper_link_info_t result;

	WARN(!octeon_is_simulation(),
	     "Using deprecated link status - please update your DT");

	/* Unless we fix it later, all links are defaulted to down */
	result.u64 = 0;

	if (octeon_is_simulation()) {
		/* The simulator gives you a simulated 1Gbps full duplex link */
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 1000;
		return result;
	}

	if (OCTEON_IS_MODEL(OCTEON_CN3XXX)
		   || OCTEON_IS_MODEL(OCTEON_CN58XX)
		   || OCTEON_IS_MODEL(OCTEON_CN50XX)) {
		/*
		 * We don't have a PHY address, so attempt to use
		 * in-band status. It is really important that boards
		 * not supporting in-band status never get
		 * here. Reading broken in-band status tends to do bad
		 * things
		 */
		union cvmx_gmxx_rxx_rx_inbnd inband_status;
		int interface = cvmx_helper_get_interface_num(ipd_port);
		int index = cvmx_helper_get_interface_index_num(ipd_port);
		inband_status.u64 =
		    cvmx_read_csr(CVMX_GMXX_RXX_RX_INBND(index, interface));

		result.s.link_up = inband_status.s.status;
		result.s.full_duplex = inband_status.s.duplex;
		switch (inband_status.s.speed) {
		case 0: /* 10 Mbps */
			result.s.speed = 10;
			break;
		case 1: /* 100 Mbps */
			result.s.speed = 100;
			break;
		case 2: /* 1 Gbps */
			result.s.speed = 1000;
			break;
		case 3: /* Illegal */
			result.u64 = 0;
			break;
		}
	} else {
		/*
		 * We don't have a PHY address and we don't have
		 * in-band status. There is no way to determine the
		 * link speed. Return down assuming this port isn't
		 * wired
		 */
		result.u64 = 0;
	}

	/* If link is down, return all fields as zero. */
	if (!result.s.link_up)
		result.u64 = 0;

	return result;
}