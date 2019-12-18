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
struct TYPE_2__ {int qlm_spd; int qlm_cfg; } ;
union cvmx_mio_qlmx_cfg {TYPE_1__ s; void* u64; } ;
typedef  int /*<<< orphan*/  cvmx_helper_interface_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_DISABLED ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_LOOP ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_NPI ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_XAUI ; 
 int /*<<< orphan*/  CVMX_MIO_QLMX_CFG (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cvmx_helper_interface_mode_t __cvmx_get_mode_cn68xx(int interface)
{
	union cvmx_mio_qlmx_cfg qlm_cfg;
	switch (interface) {
	case 0:
		qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(0));
		/* QLM is disabled when QLM SPD is 15. */
		if (qlm_cfg.s.qlm_spd == 15)
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;

		if (qlm_cfg.s.qlm_cfg == 2)
			return CVMX_HELPER_INTERFACE_MODE_SGMII;
		else if (qlm_cfg.s.qlm_cfg == 3)
			return CVMX_HELPER_INTERFACE_MODE_XAUI;
		else
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	case 2:
	case 3:
	case 4:
		qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(interface));
		/* QLM is disabled when QLM SPD is 15. */
		if (qlm_cfg.s.qlm_spd == 15)
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;

		if (qlm_cfg.s.qlm_cfg == 2)
			return CVMX_HELPER_INTERFACE_MODE_SGMII;
		else if (qlm_cfg.s.qlm_cfg == 3)
			return CVMX_HELPER_INTERFACE_MODE_XAUI;
		else
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	case 7:
		qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(3));
		/* QLM is disabled when QLM SPD is 15. */
		if (qlm_cfg.s.qlm_spd == 15) {
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		} else if (qlm_cfg.s.qlm_cfg != 0) {
			qlm_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(1));
			if (qlm_cfg.s.qlm_cfg != 0)
				return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		}
		return CVMX_HELPER_INTERFACE_MODE_NPI;
	case 8:
		return CVMX_HELPER_INTERFACE_MODE_LOOP;
	default:
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	}
}