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
typedef  int uint64_t ;
struct TYPE_6__ {int mac; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ cvmx_mgmt_port_state_t ;
typedef  int /*<<< orphan*/  cvmx_mgmt_port_result_t ;
struct TYPE_5__ {int cam_mode; int bcst; scalar_t__ mcst; } ;
struct TYPE_7__ {int u64; TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_agl_gmx_rxx_adr_ctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM0 (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM1 (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM2 (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM3 (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM4 (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM5 (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CAM_EN (int) ; 
 int /*<<< orphan*/  CVMX_AGL_GMX_RXX_ADR_CTL (int) ; 
 int /*<<< orphan*/  CVMX_MGMT_PORT_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_MGMT_PORT_SUCCESS ; 
 int __cvmx_mgmt_port_num_ports () ; 
 TYPE_2__* cvmx_mgmt_port_state_ptr ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

cvmx_mgmt_port_result_t cvmx_mgmt_port_set_mac(int port, uint64_t mac)
{
    cvmx_mgmt_port_state_t *state;
    cvmx_agl_gmx_rxx_adr_ctl_t agl_gmx_rxx_adr_ctl;

    if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
        return CVMX_MGMT_PORT_INVALID_PARAM;

    state = cvmx_mgmt_port_state_ptr + port;

    cvmx_spinlock_lock(&state->lock);

    agl_gmx_rxx_adr_ctl.u64 = 0;
    agl_gmx_rxx_adr_ctl.s.cam_mode = 1; /* Only accept matching MAC addresses */
    agl_gmx_rxx_adr_ctl.s.mcst = 0;     /* Drop multicast */
    agl_gmx_rxx_adr_ctl.s.bcst = 1;     /* Allow broadcast */
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CTL(port), agl_gmx_rxx_adr_ctl.u64);

    /* Only using one of the CAMs */
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM0(port), (mac >> 40) & 0xff);
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM1(port), (mac >> 32) & 0xff);
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM2(port), (mac >> 24) & 0xff);
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM3(port), (mac >> 16) & 0xff);
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM4(port), (mac >> 8) & 0xff);
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM5(port), (mac >> 0) & 0xff);
    cvmx_write_csr(CVMX_AGL_GMX_RXX_ADR_CAM_EN(port), 1);
    state->mac = mac;

    cvmx_spinlock_unlock(&state->lock);
    return CVMX_MGMT_PORT_SUCCESS;
}