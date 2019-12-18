#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int phy_addr; } ;
typedef  TYPE_1__ cvmx_phy_info_t ;

/* Variables and functions */
 TYPE_1__ __get_phy_info_from_dt (int) ; 

int cvmx_helper_board_get_mii_address_from_dt(int ipd_port)
{
        cvmx_phy_info_t phy_info = __get_phy_info_from_dt(ipd_port);
        return phy_info.phy_addr;
}