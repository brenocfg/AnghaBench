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
struct ifnet {int if_flags; scalar_t__ if_softc; } ;
struct TYPE_5__ {int bcst; int mcst; int cam_mode; } ;
struct TYPE_6__ {int u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_gmxx_rxx_adr_ctl_t ;
struct TYPE_7__ {unsigned long long u64; } ;
typedef  TYPE_3__ cvmx_gmxx_prtx_cfg_t ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;
typedef  TYPE_4__ cvm_oct_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CAM_EN (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_ADR_CTL (int,int) ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_SPI ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int INDEX (int /*<<< orphan*/ ) ; 
 int INTERFACE (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_helper_interface_get_mode (int) ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

void cvm_oct_common_set_multicast_list(struct ifnet *ifp)
{
	cvmx_gmxx_prtx_cfg_t gmx_cfg;
	cvm_oct_private_t *priv = (cvm_oct_private_t *)ifp->if_softc;
	int interface = INTERFACE(priv->port);
	int index = INDEX(priv->port);

	if ((interface < 2) && (cvmx_helper_interface_get_mode(interface) != CVMX_HELPER_INTERFACE_MODE_SPI)) {
		cvmx_gmxx_rxx_adr_ctl_t control;
		control.u64 = 0;
		control.s.bcst = 1;     /* Allow broadcast MAC addresses */

		if (/*ifp->mc_list || */(ifp->if_flags&IFF_ALLMULTI) ||
		    (ifp->if_flags & IFF_PROMISC))
			control.s.mcst = 2; /* Force accept multicast packets */
		else
			control.s.mcst = 1; /* Force reject multicat packets */

		if (ifp->if_flags & IFF_PROMISC)
			control.s.cam_mode = 0; /* Reject matches if promisc. Since CAM is shut off, should accept everything */
		else
			control.s.cam_mode = 1; /* Filter packets based on the CAM */

		gmx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64 & ~1ull);

		cvmx_write_csr(CVMX_GMXX_RXX_ADR_CTL(index, interface), control.u64);
		if (ifp->if_flags&IFF_PROMISC)
			cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM_EN(index, interface), 0);
		else
			cvmx_write_csr(CVMX_GMXX_RXX_ADR_CAM_EN(index, interface), 1);

		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);
	}
}