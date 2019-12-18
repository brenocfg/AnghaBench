#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {int* speed_cap_mask; TYPE_1__* phy; } ;
struct bxe_softc {int /*<<< orphan*/  media; TYPE_2__ link_params; } ;
struct TYPE_3__ {int media_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*) ; 
#define  ELINK_ETH_PHY_BASE_T 136 
#define  ELINK_ETH_PHY_CX4 135 
#define  ELINK_ETH_PHY_DA_TWINAX 134 
#define  ELINK_ETH_PHY_KR 133 
#define  ELINK_ETH_PHY_NOT_PRESENT 132 
#define  ELINK_ETH_PHY_SFPP_10G_FIBER 131 
#define  ELINK_ETH_PHY_SFP_1G_FIBER 130 
#define  ELINK_ETH_PHY_UNSPECIFIED 129 
#define  ELINK_ETH_PHY_XFP_FIBER 128 
 int /*<<< orphan*/  IFM_1000_SX ; 
 int /*<<< orphan*/  IFM_1000_T ; 
 int /*<<< orphan*/  IFM_10G_CX4 ; 
 int /*<<< orphan*/  IFM_10G_SR ; 
 int /*<<< orphan*/  IFM_10G_T ; 
 int /*<<< orphan*/  IFM_10G_TWINAX ; 
 int PORT_DA ; 
 int PORT_FIBRE ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int PORT_OTHER ; 
 int PORT_TP ; 
 size_t bxe_get_cur_phy_idx (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_media_detect(struct bxe_softc *sc)
{
    int port_type;
    uint32_t phy_idx = bxe_get_cur_phy_idx(sc);

    switch (sc->link_params.phy[phy_idx].media_type) {
    case ELINK_ETH_PHY_SFPP_10G_FIBER:
    case ELINK_ETH_PHY_XFP_FIBER:
        BLOGI(sc, "Found 10Gb Fiber media.\n");
        sc->media = IFM_10G_SR;
        port_type = PORT_FIBRE;
        break;
    case ELINK_ETH_PHY_SFP_1G_FIBER:
        BLOGI(sc, "Found 1Gb Fiber media.\n");
        sc->media = IFM_1000_SX;
        port_type = PORT_FIBRE;
        break;
    case ELINK_ETH_PHY_KR:
    case ELINK_ETH_PHY_CX4:
        BLOGI(sc, "Found 10GBase-CX4 media.\n");
        sc->media = IFM_10G_CX4;
        port_type = PORT_FIBRE;
        break;
    case ELINK_ETH_PHY_DA_TWINAX:
        BLOGI(sc, "Found 10Gb Twinax media.\n");
        sc->media = IFM_10G_TWINAX;
        port_type = PORT_DA;
        break;
    case ELINK_ETH_PHY_BASE_T:
        if (sc->link_params.speed_cap_mask[0] &
            PORT_HW_CFG_SPEED_CAPABILITY_D0_10G) {
            BLOGI(sc, "Found 10GBase-T media.\n");
            sc->media = IFM_10G_T;
            port_type = PORT_TP;
        } else {
            BLOGI(sc, "Found 1000Base-T media.\n");
            sc->media = IFM_1000_T;
            port_type = PORT_TP;
        }
        break;
    case ELINK_ETH_PHY_NOT_PRESENT:
        BLOGI(sc, "Media not present.\n");
        sc->media = 0;
        port_type = PORT_OTHER;
        break;
    case ELINK_ETH_PHY_UNSPECIFIED:
    default:
        BLOGI(sc, "Unknown media!\n");
        sc->media = 0;
        port_type = PORT_OTHER;
        break;
    }
    return port_type;
}