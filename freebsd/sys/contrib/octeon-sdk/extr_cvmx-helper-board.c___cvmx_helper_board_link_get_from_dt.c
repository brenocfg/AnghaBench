#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ phy_addr; scalar_t__ direct_connect; int phy_type; } ;
typedef  TYPE_2__ cvmx_phy_info_t ;
struct TYPE_10__ {int link_up; int full_duplex; int speed; } ;
struct TYPE_12__ {TYPE_1__ s; scalar_t__ u64; } ;
typedef  TYPE_3__ cvmx_helper_link_info_t ;
struct TYPE_13__ {scalar_t__ board_type; } ;

/* Variables and functions */
#define  BROADCOM_GENERIC_PHY 129 
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
#define  MARVELL_GENERIC_PHY 128 
 TYPE_3__ __get_broadcom_phy_link_state (scalar_t__) ; 
 TYPE_3__ __get_inband_link_state (int) ; 
 TYPE_3__ __get_marvell_phy_link_state (scalar_t__) ; 
 TYPE_2__ __get_phy_info_from_dt (int) ; 
 int /*<<< orphan*/  __switch_mdio_mux (int) ; 
 TYPE_4__* cvmx_sysinfo_get () ; 

cvmx_helper_link_info_t __cvmx_helper_board_link_get_from_dt(int ipd_port)
{
    cvmx_helper_link_info_t  result;
    cvmx_phy_info_t phy_info;

    result.u64 = 0;
    if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
    {
        /* The simulator gives you a simulated 1Gbps full duplex link */
        result.s.link_up = 1;
        result.s.full_duplex = 1;
        result.s.speed = 1000;
        return result;
    }
    phy_info = __get_phy_info_from_dt(ipd_port);
    //cvmx_dprintf("ipd_port=%d phy_addr=%d dc=%d type=%d \n", ipd_port,
    //             phy_info.phy_addr, phy_info.direct_connect, phy_info.phy_type);
    if (phy_info.phy_addr < 0) return result;

    if (phy_info.direct_connect == 0)
        __switch_mdio_mux(ipd_port);
    switch(phy_info.phy_type)
    {
        case BROADCOM_GENERIC_PHY:
            result = __get_broadcom_phy_link_state(phy_info.phy_addr);
            break;
        case MARVELL_GENERIC_PHY:
            result = __get_marvell_phy_link_state(phy_info.phy_addr);
            break;
        default:
            result = __get_inband_link_state(ipd_port);
    }
    return result;

}