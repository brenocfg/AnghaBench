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
struct TYPE_4__ {int qlm_spd; int qlm_cfg; } ;
union cvmx_mio_qlmx_cfg {TYPE_1__ s; void* u64; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  en; } ;
struct TYPE_5__ {int mode; } ;
union cvmx_gmxx_inf_mode {TYPE_3__ s; TYPE_2__ cn61xx; void* u64; } ;
typedef  int /*<<< orphan*/  cvmx_helper_interface_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_INF_MODE (int) ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_DISABLED ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_LOOP ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_NPI ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_XAUI ; 
 int /*<<< orphan*/  CVMX_MIO_QLMX_CFG (int) ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_CNF71XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_get_mode_cn68xx (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cvmx_helper_interface_mode_t __cvmx_get_mode_octeon2(int interface)
{
	union cvmx_gmxx_inf_mode mode;

	if (OCTEON_IS_MODEL(OCTEON_CN68XX))
		return __cvmx_get_mode_cn68xx(interface);

	if (interface == 2)
		return CVMX_HELPER_INTERFACE_MODE_NPI;

	if (interface == 3)
		return CVMX_HELPER_INTERFACE_MODE_LOOP;

	/* Only present in CN63XX & CN66XX Octeon model */
	if ((OCTEON_IS_MODEL(OCTEON_CN63XX) &&
	     (interface == 4 || interface == 5)) ||
	    (OCTEON_IS_MODEL(OCTEON_CN66XX) &&
	     interface >= 4 && interface <= 7)) {
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	}

	if (OCTEON_IS_MODEL(OCTEON_CN66XX)) {
		union cvmx_mio_qlmx_cfg mio_qlm_cfg;

		/* QLM2 is SGMII0 and QLM1 is SGMII1 */
		if (interface == 0)
			mio_qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(2));
		else if (interface == 1)
			mio_qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(1));
		else
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;

		if (mio_qlm_cfg.s.qlm_spd == 15)
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;

		if (mio_qlm_cfg.s.qlm_cfg == 9)
			return CVMX_HELPER_INTERFACE_MODE_SGMII;
		else if (mio_qlm_cfg.s.qlm_cfg == 11)
			return CVMX_HELPER_INTERFACE_MODE_XAUI;
		else
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	} else if (OCTEON_IS_MODEL(OCTEON_CN61XX)) {
		union cvmx_mio_qlmx_cfg qlm_cfg;

		if (interface == 0) {
			qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(2));
			if (qlm_cfg.s.qlm_cfg == 2)
				return CVMX_HELPER_INTERFACE_MODE_SGMII;
			else if (qlm_cfg.s.qlm_cfg == 3)
				return CVMX_HELPER_INTERFACE_MODE_XAUI;
			else
				return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		} else if (interface == 1) {
			qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(0));
			if (qlm_cfg.s.qlm_cfg == 2)
				return CVMX_HELPER_INTERFACE_MODE_SGMII;
			else if (qlm_cfg.s.qlm_cfg == 3)
				return CVMX_HELPER_INTERFACE_MODE_XAUI;
			else
				return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		}
	} else if (OCTEON_IS_MODEL(OCTEON_CNF71XX)) {
		if (interface == 0) {
			union cvmx_mio_qlmx_cfg qlm_cfg;
			qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(0));
			if (qlm_cfg.s.qlm_cfg == 2)
				return CVMX_HELPER_INTERFACE_MODE_SGMII;
		}
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	}

	if (interface == 1 && OCTEON_IS_MODEL(OCTEON_CN63XX))
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;

	mode.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(interface));

	if (OCTEON_IS_MODEL(OCTEON_CN63XX)) {
		switch (mode.cn61xx.mode) {
		case 0:
			return CVMX_HELPER_INTERFACE_MODE_SGMII;
		case 1:
			return CVMX_HELPER_INTERFACE_MODE_XAUI;
		default:
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		}
	} else {
		if (!mode.s.en)
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;

		if (mode.s.type)
			return CVMX_HELPER_INTERFACE_MODE_GMII;
		else
			return CVMX_HELPER_INTERFACE_MODE_RGMII;
	}
}