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
typedef  size_t uint32_t ;
struct TYPE_6__ {int* advertising; size_t* link_config; int* supported; } ;
struct TYPE_5__ {int num_phys; size_t* req_flow_ctrl; void** req_duplex; void** req_line_speed; int /*<<< orphan*/ * speed_cap_mask; TYPE_1__* phy; } ;
struct bxe_softc {TYPE_3__ port; TYPE_2__ link_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_2500baseX_Full ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,void*,void*,size_t,int) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,void*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P3 (struct bxe_softc*,char*,void*,void*,int) ; 
 size_t ELINK_EXT_PHY1 ; 
 size_t ELINK_FLOW_CTRL_AUTO ; 
 size_t ELINK_FLOW_CTRL_NONE ; 
 void* ELINK_SPEED_10 ; 
 void* ELINK_SPEED_100 ; 
 void* ELINK_SPEED_1000 ; 
 void* ELINK_SPEED_10000 ; 
 void* ELINK_SPEED_20000 ; 
 void* ELINK_SPEED_2500 ; 
 void* ELINK_SPEED_AUTO_NEG ; 
 int ELINK_SUPPORTED_10000baseT_Full ; 
 int ELINK_SUPPORTED_1000baseT_Full ; 
 int ELINK_SUPPORTED_100baseT_Full ; 
 int ELINK_SUPPORTED_100baseT_Half ; 
 int ELINK_SUPPORTED_10baseT_Full ; 
 int ELINK_SUPPORTED_10baseT_Half ; 
 int ELINK_SUPPORTED_2500baseX_Full ; 
 int ELINK_SUPPORTED_Autoneg ; 
 size_t PORT_FEATURE_FLOW_CONTROL_MASK ; 
#define  PORT_FEATURE_LINK_SPEED_100M_FULL 136 
#define  PORT_FEATURE_LINK_SPEED_100M_HALF 135 
#define  PORT_FEATURE_LINK_SPEED_10G_CX4 134 
#define  PORT_FEATURE_LINK_SPEED_10M_FULL 133 
#define  PORT_FEATURE_LINK_SPEED_10M_HALF 132 
#define  PORT_FEATURE_LINK_SPEED_1G 131 
#define  PORT_FEATURE_LINK_SPEED_20G 130 
#define  PORT_FEATURE_LINK_SPEED_2_5G 129 
#define  PORT_FEATURE_LINK_SPEED_AUTO 128 
 size_t PORT_FEATURE_LINK_SPEED_MASK ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833 ; 
 int /*<<< orphan*/  bxe_set_requested_fc (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_link_settings_requested(struct bxe_softc *sc)
{
    uint32_t link_config;
    uint32_t idx;
    uint32_t cfg_size = 0;

    sc->port.advertising[0] = 0;
    sc->port.advertising[1] = 0;

    switch (sc->link_params.num_phys) {
    case 1:
    case 2:
        cfg_size = 1;
        break;
    case 3:
        cfg_size = 2;
        break;
    }

    for (idx = 0; idx < cfg_size; idx++) {
        sc->link_params.req_duplex[idx] = DUPLEX_FULL;
        link_config = sc->port.link_config[idx];

        switch (link_config & PORT_FEATURE_LINK_SPEED_MASK) {
        case PORT_FEATURE_LINK_SPEED_AUTO:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_Autoneg) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_AUTO_NEG;
                sc->port.advertising[idx] |= sc->port.supported[idx];
                if (sc->link_params.phy[ELINK_EXT_PHY1].type ==
                    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833)
                    sc->port.advertising[idx] |=
                        (ELINK_SUPPORTED_100baseT_Half |
                         ELINK_SUPPORTED_100baseT_Full);
            } else {
                /* force 10G, no AN */
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_10000;
                sc->port.advertising[idx] |=
                    (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
                continue;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_10M_FULL:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_10baseT_Full) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_10;
                sc->port.advertising[idx] |= (ADVERTISED_10baseT_Full |
                                              ADVERTISED_TP);
            } else {
                BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                          "speed_cap_mask=0x%08x\n",
                      link_config, sc->link_params.speed_cap_mask[idx]);
                return;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_10M_HALF:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_10baseT_Half) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_10;
                sc->link_params.req_duplex[idx] = DUPLEX_HALF;
                sc->port.advertising[idx] |= (ADVERTISED_10baseT_Half |
                                              ADVERTISED_TP);
				ELINK_DEBUG_P1(sc, "driver requesting DUPLEX_HALF req_duplex = %x!\n",
								sc->link_params.req_duplex[idx]);
            } else {
                BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                          "speed_cap_mask=0x%08x\n",
                      link_config, sc->link_params.speed_cap_mask[idx]);
                return;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_100M_FULL:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_100baseT_Full) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_100;
                sc->port.advertising[idx] |= (ADVERTISED_100baseT_Full |
                                              ADVERTISED_TP);
            } else {
                BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                          "speed_cap_mask=0x%08x\n",
                      link_config, sc->link_params.speed_cap_mask[idx]);
                return;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_100M_HALF:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_100baseT_Half) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_100;
                sc->link_params.req_duplex[idx] = DUPLEX_HALF;
                sc->port.advertising[idx] |= (ADVERTISED_100baseT_Half |
                                              ADVERTISED_TP);
            } else {
                BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                          "speed_cap_mask=0x%08x\n",
                      link_config, sc->link_params.speed_cap_mask[idx]);
                return;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_1G:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_1000baseT_Full) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_1000;
                sc->port.advertising[idx] |= (ADVERTISED_1000baseT_Full |
                                              ADVERTISED_TP);
            } else {
                BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                          "speed_cap_mask=0x%08x\n",
                      link_config, sc->link_params.speed_cap_mask[idx]);
                return;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_2_5G:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_2500baseX_Full) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_2500;
                sc->port.advertising[idx] |= (ADVERTISED_2500baseX_Full |
                                              ADVERTISED_TP);
            } else {
                BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                          "speed_cap_mask=0x%08x\n",
                      link_config, sc->link_params.speed_cap_mask[idx]);
                return;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_10G_CX4:
            if (sc->port.supported[idx] & ELINK_SUPPORTED_10000baseT_Full) {
                sc->link_params.req_line_speed[idx] = ELINK_SPEED_10000;
                sc->port.advertising[idx] |= (ADVERTISED_10000baseT_Full |
                                              ADVERTISED_FIBRE);
            } else {
                BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                          "speed_cap_mask=0x%08x\n",
                      link_config, sc->link_params.speed_cap_mask[idx]);
                return;
            }
            break;

        case PORT_FEATURE_LINK_SPEED_20G:
            sc->link_params.req_line_speed[idx] = ELINK_SPEED_20000;
            break;

        default:
            BLOGE(sc, "Invalid NVRAM config link_config=0x%08x "
                      "speed_cap_mask=0x%08x\n",
                  link_config, sc->link_params.speed_cap_mask[idx]);
            sc->link_params.req_line_speed[idx] = ELINK_SPEED_AUTO_NEG;
            sc->port.advertising[idx] = sc->port.supported[idx];
            break;
        }

        sc->link_params.req_flow_ctrl[idx] =
            (link_config & PORT_FEATURE_FLOW_CONTROL_MASK);

        if (sc->link_params.req_flow_ctrl[idx] == ELINK_FLOW_CTRL_AUTO) {
            if (!(sc->port.supported[idx] & ELINK_SUPPORTED_Autoneg)) {
                sc->link_params.req_flow_ctrl[idx] = ELINK_FLOW_CTRL_NONE;
            } else {
                bxe_set_requested_fc(sc);
            }
        }

        BLOGD(sc, DBG_LOAD, "req_line_speed=%d req_duplex=%d "
                            "req_flow_ctrl=0x%x advertising=0x%x\n",
              sc->link_params.req_line_speed[idx],
              sc->link_params.req_duplex[idx],
              sc->link_params.req_flow_ctrl[idx],
              sc->port.advertising[idx]);
		ELINK_DEBUG_P3(sc, "req_line_speed=%d req_duplex=%d "
						"advertising=0x%x\n",
						sc->link_params.req_line_speed[idx],
						sc->link_params.req_duplex[idx],
						sc->port.advertising[idx]);
    }
}