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
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ cvmx_mgmt_port_state_t ;
struct TYPE_5__ {int bcst; int mcst; int cam_mode; } ;
struct TYPE_7__ {int u64; TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_agl_gmx_rxx_adr_ctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM_EN (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CTL (int) ; 
 int CVMX_IFF_ALLMULTI ; 
 int CVMX_IFF_PROMISC ; 
 int __cvmx_mgmt_port_num_ports () ; 
 TYPE_2__* cvmx_mgmt_port_state_ptr ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

void cvmx_mgmt_port_set_multicast_list(int port, int flags)
{
    cvmx_mgmt_port_state_t *state;
    cvmx_agl_gmx_rxx_adr_ctl_t agl_gmx_rxx_adr_ctl;

    if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
        return;

    state = cvmx_mgmt_port_state_ptr + port;

    cvmx_spinlock_lock(&state->lock);

    agl_gmx_rxx_adr_ctl.u64 = cvmx_read_csr(CVMX_AGL_GMX_RXX_ADR_CTL(port));

    /* Allow broadcast MAC addresses */
    if (!agl_gmx_rxx_adr_ctl.s.bcst)
	agl_gmx_rxx_adr_ctl.s.bcst = 1;

    if ((flags & CVMX_IFF_ALLMULTI) || (flags & CVMX_IFF_PROMISC))
	agl_gmx_rxx_adr_ctl.s.mcst = 2; /* Force accept multicast packets */
    else
	agl_gmx_rxx_adr_ctl.s.mcst = 1; /* Force reject multicast packets */

    if (flags & CVMX_IFF_PROMISC)
	agl_gmx_rxx_adr_ctl.s.cam_mode = 0; /* Reject matches if promisc. Since CAM is shut off, should accept everything */
    else
	agl_gmx_rxx_adr_ctl.s.cam_mode = 1; /* Filter packets based on the CAM */

    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CTL(port), agl_gmx_rxx_adr_ctl.u64);

    if (flags & CVMX_IFF_PROMISC)
	cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM_EN(port), 0);
    else
	cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM_EN(port), 1);

    cvmx_spinlock_unlock(&state->lock);
}