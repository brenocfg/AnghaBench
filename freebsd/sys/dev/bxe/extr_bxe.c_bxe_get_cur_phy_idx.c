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
typedef  int uint32_t ;
struct TYPE_6__ {int num_phys; TYPE_2__* phy; } ;
struct TYPE_4__ {int link_status; scalar_t__ link_up; } ;
struct bxe_softc {TYPE_3__ link_params; TYPE_1__ link_vars; } ;
struct TYPE_5__ {int supported; } ;

/* Variables and functions */
 int ELINK_EXT_PHY1 ; 
 size_t ELINK_EXT_PHY2 ; 
 int ELINK_INT_PHY ; 
 int ELINK_SUPPORTED_FIBRE ; 
 int LINK_STATUS_SERDES_LINK ; 
#define  PORT_HW_CFG_PHY_SELECTION_FIRST_PHY 132 
#define  PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY 131 
#define  PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT 130 
#define  PORT_HW_CFG_PHY_SELECTION_SECOND_PHY 129 
#define  PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY 128 
 int elink_phy_selection (TYPE_3__*) ; 

__attribute__((used)) static int
bxe_get_cur_phy_idx(struct bxe_softc *sc)
{
    uint32_t sel_phy_idx = 0;

    if (sc->link_params.num_phys <= 1) {
        return (ELINK_INT_PHY);
    }

    if (sc->link_vars.link_up) {
        sel_phy_idx = ELINK_EXT_PHY1;
        /* In case link is SERDES, check if the ELINK_EXT_PHY2 is the one */
        if ((sc->link_vars.link_status & LINK_STATUS_SERDES_LINK) &&
            (sc->link_params.phy[ELINK_EXT_PHY2].supported &
             ELINK_SUPPORTED_FIBRE))
            sel_phy_idx = ELINK_EXT_PHY2;
    } else {
        switch (elink_phy_selection(&sc->link_params)) {
        case PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT:
        case PORT_HW_CFG_PHY_SELECTION_FIRST_PHY:
        case PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY:
               sel_phy_idx = ELINK_EXT_PHY1;
               break;
        case PORT_HW_CFG_PHY_SELECTION_SECOND_PHY:
        case PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY:
               sel_phy_idx = ELINK_EXT_PHY2;
               break;
        }
    }

    return (sel_phy_idx);
}