#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int capable_10_half; int capable_100base_x_half; scalar_t__ capable_extended_status; scalar_t__ capable_100base_x_full; scalar_t__ capable_10_full; scalar_t__ capable_100base_t4; } ;
struct TYPE_23__ {TYPE_3__ s; void* u16; } ;
typedef  TYPE_7__ cvmx_mdio_phy_reg_status_t ;
struct TYPE_17__ {int capable_1000base_t_half; scalar_t__ capable_1000base_t_full; } ;
struct TYPE_24__ {TYPE_1__ s; void* u16; } ;
typedef  TYPE_8__ cvmx_mdio_phy_reg_extended_status_t ;
struct TYPE_18__ {int autoneg_enable; int restart_autoneg; int speed_msb; int speed_lsb; scalar_t__ duplex; } ;
struct TYPE_25__ {void* u16; TYPE_2__ s; } ;
typedef  TYPE_9__ cvmx_mdio_phy_reg_control_t ;
struct TYPE_20__ {int advert_1000base_t_half; scalar_t__ advert_1000base_t_full; } ;
struct TYPE_14__ {void* u16; TYPE_4__ s; } ;
typedef  TYPE_10__ cvmx_mdio_phy_reg_control_1000_t ;
struct TYPE_22__ {int asymmetric_pause; int pause; int advert_10base_tx_half; int advert_100base_tx_half; scalar_t__ advert_100base_tx_full; scalar_t__ advert_10base_tx_full; scalar_t__ advert_100base_t4; } ;
struct TYPE_15__ {void* u16; TYPE_6__ s; } ;
typedef  TYPE_11__ cvmx_mdio_phy_reg_autoneg_adver_t ;
struct TYPE_21__ {int speed; scalar_t__ full_duplex; } ;
struct TYPE_16__ {TYPE_5__ s; } ;
typedef  TYPE_12__ cvmx_helper_link_info_t ;
typedef  int cvmx_helper_board_set_phy_link_flags_types_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MDIO_PHY_REG_AUTONEG_ADVER ; 
 int /*<<< orphan*/  CVMX_MDIO_PHY_REG_CONTROL ; 
 int /*<<< orphan*/  CVMX_MDIO_PHY_REG_CONTROL_1000 ; 
 int /*<<< orphan*/  CVMX_MDIO_PHY_REG_EXTENDED_STATUS ; 
 int /*<<< orphan*/  CVMX_MDIO_PHY_REG_STATUS ; 
 void* cvmx_mdio_read (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_mdio_write (int,int,int /*<<< orphan*/ ,void*) ; 
 int set_phy_link_flags_autoneg ; 
 int set_phy_link_flags_flow_control_dont_touch ; 
 int set_phy_link_flags_flow_control_enable ; 
 int set_phy_link_flags_flow_control_mask ; 

int cvmx_helper_board_link_set_phy(int phy_addr, cvmx_helper_board_set_phy_link_flags_types_t link_flags,
                                   cvmx_helper_link_info_t link_info)
{

    /* Set the flow control settings based on link_flags */
    if ((link_flags & set_phy_link_flags_flow_control_mask) != set_phy_link_flags_flow_control_dont_touch)
    {
        cvmx_mdio_phy_reg_autoneg_adver_t reg_autoneg_adver;
        reg_autoneg_adver.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_AUTONEG_ADVER);
        reg_autoneg_adver.s.asymmetric_pause = (link_flags & set_phy_link_flags_flow_control_mask) == set_phy_link_flags_flow_control_enable;
        reg_autoneg_adver.s.pause = (link_flags & set_phy_link_flags_flow_control_mask) == set_phy_link_flags_flow_control_enable;
        cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_AUTONEG_ADVER, reg_autoneg_adver.u16);
    }

    /* If speed isn't set and autoneg is on advertise all supported modes */
    if ((link_flags & set_phy_link_flags_autoneg) && (link_info.s.speed == 0))
    {
        cvmx_mdio_phy_reg_control_t reg_control;
        cvmx_mdio_phy_reg_status_t reg_status;
        cvmx_mdio_phy_reg_autoneg_adver_t reg_autoneg_adver;
        cvmx_mdio_phy_reg_extended_status_t reg_extended_status;
        cvmx_mdio_phy_reg_control_1000_t reg_control_1000;

        reg_status.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_STATUS);
        reg_autoneg_adver.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_AUTONEG_ADVER);
        reg_autoneg_adver.s.advert_100base_t4 = reg_status.s.capable_100base_t4;
        reg_autoneg_adver.s.advert_10base_tx_full = reg_status.s.capable_10_full;
        reg_autoneg_adver.s.advert_10base_tx_half = reg_status.s.capable_10_half;
        reg_autoneg_adver.s.advert_100base_tx_full = reg_status.s.capable_100base_x_full;
        reg_autoneg_adver.s.advert_100base_tx_half = reg_status.s.capable_100base_x_half;
        cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_AUTONEG_ADVER, reg_autoneg_adver.u16);
        if (reg_status.s.capable_extended_status)
        {
            reg_extended_status.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_EXTENDED_STATUS);
            reg_control_1000.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL_1000);
            reg_control_1000.s.advert_1000base_t_full = reg_extended_status.s.capable_1000base_t_full;
            reg_control_1000.s.advert_1000base_t_half = reg_extended_status.s.capable_1000base_t_half;
            cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL_1000, reg_control_1000.u16);
        }
        reg_control.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL);
        reg_control.s.autoneg_enable = 1;
        reg_control.s.restart_autoneg = 1;
        cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL, reg_control.u16);
    }
    else if ((link_flags & set_phy_link_flags_autoneg))
    {
        cvmx_mdio_phy_reg_control_t reg_control;
        cvmx_mdio_phy_reg_status_t reg_status;
        cvmx_mdio_phy_reg_autoneg_adver_t reg_autoneg_adver;
        cvmx_mdio_phy_reg_control_1000_t reg_control_1000;

        reg_status.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_STATUS);
        reg_autoneg_adver.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_AUTONEG_ADVER);
        reg_autoneg_adver.s.advert_100base_t4 = 0;
        reg_autoneg_adver.s.advert_10base_tx_full = 0;
        reg_autoneg_adver.s.advert_10base_tx_half = 0;
        reg_autoneg_adver.s.advert_100base_tx_full = 0;
        reg_autoneg_adver.s.advert_100base_tx_half = 0;
        if (reg_status.s.capable_extended_status)
        {
            reg_control_1000.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL_1000);
            reg_control_1000.s.advert_1000base_t_full = 0;
            reg_control_1000.s.advert_1000base_t_half = 0;
        }
        switch (link_info.s.speed)
        {
            case 10:
                reg_autoneg_adver.s.advert_10base_tx_full = link_info.s.full_duplex;
                reg_autoneg_adver.s.advert_10base_tx_half = !link_info.s.full_duplex;
                break;
            case 100:
                reg_autoneg_adver.s.advert_100base_tx_full = link_info.s.full_duplex;
                reg_autoneg_adver.s.advert_100base_tx_half = !link_info.s.full_duplex;
                break;
            case 1000:
                reg_control_1000.s.advert_1000base_t_full = link_info.s.full_duplex;
                reg_control_1000.s.advert_1000base_t_half = !link_info.s.full_duplex;
                break;
        }
        cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_AUTONEG_ADVER, reg_autoneg_adver.u16);
        if (reg_status.s.capable_extended_status)
            cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL_1000, reg_control_1000.u16);
        reg_control.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL);
        reg_control.s.autoneg_enable = 1;
        reg_control.s.restart_autoneg = 1;
        cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL, reg_control.u16);
    }
    else
    {
        cvmx_mdio_phy_reg_control_t reg_control;
        reg_control.u16 = cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL);
        reg_control.s.autoneg_enable = 0;
        reg_control.s.restart_autoneg = 1;
        reg_control.s.duplex = link_info.s.full_duplex;
        if (link_info.s.speed == 1000)
        {
            reg_control.s.speed_msb = 1;
            reg_control.s.speed_lsb = 0;
        }
        else if (link_info.s.speed == 100)
        {
            reg_control.s.speed_msb = 0;
            reg_control.s.speed_lsb = 1;
        }
        else if (link_info.s.speed == 10)
        {
            reg_control.s.speed_msb = 0;
            reg_control.s.speed_lsb = 0;
        }
        cvmx_mdio_write(phy_addr >> 8, phy_addr & 0xff, CVMX_MDIO_PHY_REG_CONTROL, reg_control.u16);
    }
    return 0;
}