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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct ifnet {scalar_t__ if_softc; } ;
struct TYPE_3__ {unsigned long long u64; } ;
typedef  TYPE_1__ cvmx_gmxx_prtx_cfg_t ;
struct TYPE_4__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ cvm_oct_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM0 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM1 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM2 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM3 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM4 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM5 (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_SMACX (int,int) ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_SPI ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvm_oct_common_set_multicast_list (struct ifnet*) ; 
 scalar_t__ cvmx_helper_interface_get_mode (int) ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

void cvm_oct_common_set_mac_address(struct ifnet *ifp, const void *addr)
{
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;
	cvmx_gmxx_prtx_cfg_t gmx_cfg;
	int interface = INTERFACE(priv->port);
	int index = INDEX(priv->port);

	memcpy(priv->mac, addr, 6);

	if ((interface < 2) && (cvmx_helper_interface_get_mode(interface) != CVMX_HELPER_INTERFACE_MODE_SPI)) {
		int i;
		const uint8_t *ptr = addr;
		uint64_t mac = 0;
		for (i = 0; i < 6; i++)
			mac = (mac<<8) | (uint64_t)(ptr[i]);

		gmx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64 & ~1ull);

		cvmx_write_csr(CVMX_GMXX_SMACX(index, interface), mac);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM0(index, interface), ptr[0]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM1(index, interface), ptr[1]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM2(index, interface), ptr[2]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM3(index, interface), ptr[3]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM4(index, interface), ptr[4]);
		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM5(index, interface), ptr[5]);
		cvm_oct_common_set_multicast_list(ifp);
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);
	}
}