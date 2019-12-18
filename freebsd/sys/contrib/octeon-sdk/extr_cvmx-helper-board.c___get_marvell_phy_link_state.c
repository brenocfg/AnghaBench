#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int link_up; int full_duplex; int speed; } ;
struct TYPE_5__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int cvmx_mdio_read (int,int,int) ; 

__attribute__((used)) static cvmx_helper_link_info_t __get_marvell_phy_link_state(int phy_addr)
{
    cvmx_helper_link_info_t  result;
    int phy_status;

    result.u64 = 0;
    /*All the speed information can be read from register 17 in one go.*/
    phy_status = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, 17);

    /* If the resolve bit 11 isn't set, see if autoneg is turned off
       (bit 12, reg 0). The resolve bit doesn't get set properly when
       autoneg is off, so force it */
    if ((phy_status & (1<<11)) == 0)
    {
        int auto_status = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, 0);
        if ((auto_status & (1<<12)) == 0)
            phy_status |= 1<<11;
    }

    /* Only return a link if the PHY has finished auto negotiation
       and set the resolved bit (bit 11) */
    if (phy_status & (1<<11))
    {
        result.s.link_up = 1;
        result.s.full_duplex = ((phy_status>>13)&1);
        switch ((phy_status>>14)&3)
        {
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
    }
    return result;
}