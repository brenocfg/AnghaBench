#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {scalar_t__* req_line_speed; TYPE_1__* phy; } ;
struct TYPE_12__ {int* supported; int /*<<< orphan*/  phy_addr; int /*<<< orphan*/ * advertising; } ;
struct TYPE_10__ {int /*<<< orphan*/  line_speed; int /*<<< orphan*/  duplex; scalar_t__ link_up; } ;
struct bxe_softc {scalar_t__ state; int flags; TYPE_5__ link_params; TYPE_4__ port; TYPE_2__ link_vars; } ;
struct TYPE_14__ {int supported; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  advertising; } ;
typedef  TYPE_6__ bxe_dev_setting_t ;
struct TYPE_15__ {TYPE_3__* port_hw_config; } ;
struct TYPE_11__ {int /*<<< orphan*/  external_phy_config; } ;
struct TYPE_9__ {scalar_t__ media_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseT_Full ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int BXE_MF_FUNC_DIS ; 
 int /*<<< orphan*/  BXE_NOMCP (struct bxe_softc*) ; 
 scalar_t__ BXE_STATE_OPEN ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 scalar_t__ ELINK_ETH_PHY_SFP_1G_FIBER ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int ELINK_SUPPORTED_10000baseT_Full ; 
 int ELINK_SUPPORTED_FIBRE ; 
 int ELINK_SUPPORTED_TP ; 
 int /*<<< orphan*/  ELINK_XGXS_EXT_PHY_ADDR (int) ; 
 scalar_t__ IS_MF (struct bxe_softc*) ; 
 int PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT ; 
 int PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE ; 
 int PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK ; 
 int PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN ; 
 int SC_PORT (struct bxe_softc*) ; 
 int SHMEM_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 size_t bxe_get_cur_phy_idx (struct bxe_softc*) ; 
 int bxe_get_link_cfg_idx (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_get_mf_speed (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_media_detect (struct bxe_softc*) ; 
 TYPE_7__ dev_info ; 

__attribute__((used)) static int
bxe_get_settings(struct bxe_softc *sc, bxe_dev_setting_t *dev_p)
{
    uint32_t ext_phy_config;
    int port = SC_PORT(sc);
    int cfg_idx = bxe_get_link_cfg_idx(sc);

    dev_p->supported = sc->port.supported[cfg_idx] |
            (sc->port.supported[cfg_idx ^ 1] &
            (ELINK_SUPPORTED_TP | ELINK_SUPPORTED_FIBRE));
    dev_p->advertising = sc->port.advertising[cfg_idx];
    if(sc->link_params.phy[bxe_get_cur_phy_idx(sc)].media_type ==
        ELINK_ETH_PHY_SFP_1G_FIBER) {
        dev_p->supported = ~(ELINK_SUPPORTED_10000baseT_Full);
        dev_p->advertising &= ~(ADVERTISED_10000baseT_Full);
    }
    if ((sc->state == BXE_STATE_OPEN) && sc->link_vars.link_up &&
        !(sc->flags & BXE_MF_FUNC_DIS)) {
        dev_p->duplex = sc->link_vars.duplex;
        if (IS_MF(sc) && !BXE_NOMCP(sc))
            dev_p->speed = bxe_get_mf_speed(sc);
        else
            dev_p->speed = sc->link_vars.line_speed;
    } else {
        dev_p->duplex = DUPLEX_UNKNOWN;
        dev_p->speed = SPEED_UNKNOWN;
    }

    dev_p->port = bxe_media_detect(sc);

    ext_phy_config = SHMEM_RD(sc,
                         dev_info.port_hw_config[port].external_phy_config);
    if((ext_phy_config & PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK) ==
        PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT)
        dev_p->phy_address =  sc->port.phy_addr;
    else if(((ext_phy_config & PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK) !=
            PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE) &&
        ((ext_phy_config & PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK) !=
            PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN))
        dev_p->phy_address = ELINK_XGXS_EXT_PHY_ADDR(ext_phy_config);
    else
        dev_p->phy_address = 0;

    if(sc->link_params.req_line_speed[cfg_idx] == ELINK_SPEED_AUTO_NEG)
        dev_p->autoneg = AUTONEG_ENABLE;
    else
       dev_p->autoneg = AUTONEG_DISABLE;


    return 0;
}