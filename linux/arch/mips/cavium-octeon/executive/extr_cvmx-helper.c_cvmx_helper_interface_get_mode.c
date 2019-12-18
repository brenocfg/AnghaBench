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
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  en; } ;
struct TYPE_3__ {int mode; } ;
union cvmx_gmxx_inf_mode {TYPE_2__ s; TYPE_1__ cn52xx; int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  cvmx_helper_interface_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_INF_MODE (int) ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_DISABLED ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_LOOP ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_NPI ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_PICMG ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_SPI ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_XAUI ; 
 int /*<<< orphan*/  OCTEON_CN30XX ; 
 int /*<<< orphan*/  OCTEON_CN31XX ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN50XX ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CN7XXX ; 
 int /*<<< orphan*/  OCTEON_CNF71XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_get_mode_cn7xxx (int) ; 
 int /*<<< orphan*/  __cvmx_get_mode_octeon2 (int) ; 
 int cvmx_helper_get_number_of_interfaces () ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

cvmx_helper_interface_mode_t cvmx_helper_interface_get_mode(int interface)
{
	union cvmx_gmxx_inf_mode mode;

	if (interface < 0 ||
	    interface >= cvmx_helper_get_number_of_interfaces())
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;

	/*
	 * OCTEON III models
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN7XXX))
		return __cvmx_get_mode_cn7xxx(interface);

	/*
	 * Octeon II models
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF71XX))
		return __cvmx_get_mode_octeon2(interface);

	/*
	 * Octeon and Octeon Plus models
	 */
	if (interface == 2)
		return CVMX_HELPER_INTERFACE_MODE_NPI;

	if (interface == 3) {
		if (OCTEON_IS_MODEL(OCTEON_CN56XX)
		    || OCTEON_IS_MODEL(OCTEON_CN52XX))
			return CVMX_HELPER_INTERFACE_MODE_LOOP;
		else
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	}

	/* Interface 1 is always disabled on CN31XX and CN30XX */
	if ((interface == 1)
	    && (OCTEON_IS_MODEL(OCTEON_CN31XX) || OCTEON_IS_MODEL(OCTEON_CN30XX)
		|| OCTEON_IS_MODEL(OCTEON_CN50XX)
		|| OCTEON_IS_MODEL(OCTEON_CN52XX)))
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;

	mode.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(interface));

	if (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN52XX)) {
		switch (mode.cn52xx.mode) {
		case 0:
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		case 1:
			return CVMX_HELPER_INTERFACE_MODE_XAUI;
		case 2:
			return CVMX_HELPER_INTERFACE_MODE_SGMII;
		case 3:
			return CVMX_HELPER_INTERFACE_MODE_PICMG;
		default:
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		}
	} else {
		if (!mode.s.en)
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;

		if (mode.s.type) {
			if (OCTEON_IS_MODEL(OCTEON_CN38XX)
			    || OCTEON_IS_MODEL(OCTEON_CN58XX))
				return CVMX_HELPER_INTERFACE_MODE_SPI;
			else
				return CVMX_HELPER_INTERFACE_MODE_GMII;
		} else
			return CVMX_HELPER_INTERFACE_MODE_RGMII;
	}
}