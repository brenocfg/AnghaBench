#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
struct elink_vars {int link_status; int phy_link_up; int line_speed; int duplex; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  flow_ctrl; } ;
struct elink_phy {scalar_t__ req_line_speed; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  ELINK_FLOW_CTRL_NONE ; 
#define  ELINK_GP_STATUS_100M 142 
#define  ELINK_GP_STATUS_10G_CX4 141 
#define  ELINK_GP_STATUS_10G_HIG 140 
#define  ELINK_GP_STATUS_10G_KR 139 
#define  ELINK_GP_STATUS_10G_KX4 138 
#define  ELINK_GP_STATUS_10G_SFI 137 
#define  ELINK_GP_STATUS_10G_XFI 136 
#define  ELINK_GP_STATUS_10M 135 
#define  ELINK_GP_STATUS_1G 134 
#define  ELINK_GP_STATUS_1G_KX 133 
#define  ELINK_GP_STATUS_20G_DXGXS 132 
#define  ELINK_GP_STATUS_20G_KR2 131 
#define  ELINK_GP_STATUS_2_5G 130 
#define  ELINK_GP_STATUS_5G 129 
#define  ELINK_GP_STATUS_6G 128 
 int ELINK_LINK_1000TFD ; 
 int ELINK_LINK_1000THD ; 
 int ELINK_LINK_100TXFD ; 
 int ELINK_LINK_100TXHD ; 
 int ELINK_LINK_10GTFD ; 
 int ELINK_LINK_10TFD ; 
 int ELINK_LINK_10THD ; 
 int ELINK_LINK_20GTFD ; 
 int ELINK_LINK_2500TFD ; 
 int ELINK_LINK_2500THD ; 
 int /*<<< orphan*/  ELINK_MAC_TYPE_NONE ; 
 int ELINK_SPEED_10 ; 
 int ELINK_SPEED_100 ; 
 int ELINK_SPEED_1000 ; 
 int ELINK_SPEED_10000 ; 
 int ELINK_SPEED_20000 ; 
 int ELINK_SPEED_2500 ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  ELINK_STATUS_ERROR ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int LINK_STATUS_AUTO_NEGOTIATE_ENABLED ; 
 int LINK_STATUS_LINK_UP ; 

__attribute__((used)) static elink_status_t elink_get_link_speed_duplex(struct elink_phy *phy,
				     struct elink_params *params,
				      struct elink_vars *vars,
				      uint16_t is_link_up,
				      uint16_t speed_mask,
				      uint16_t is_duplex)
{
	struct bxe_softc *sc = params->sc;
	if (phy->req_line_speed == ELINK_SPEED_AUTO_NEG)
		vars->link_status |= LINK_STATUS_AUTO_NEGOTIATE_ENABLED;
	if (is_link_up) {
		ELINK_DEBUG_P0(sc, "phy link up\n");

		vars->phy_link_up = 1;
		vars->link_status |= LINK_STATUS_LINK_UP;

		switch (speed_mask) {
		case ELINK_GP_STATUS_10M:
			vars->line_speed = ELINK_SPEED_10;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= ELINK_LINK_10TFD;
			else
				vars->link_status |= ELINK_LINK_10THD;
			break;

		case ELINK_GP_STATUS_100M:
			vars->line_speed = ELINK_SPEED_100;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= ELINK_LINK_100TXFD;
			else
				vars->link_status |= ELINK_LINK_100TXHD;
			break;

		case ELINK_GP_STATUS_1G:
		case ELINK_GP_STATUS_1G_KX:
			vars->line_speed = ELINK_SPEED_1000;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= ELINK_LINK_1000TFD;
			else
				vars->link_status |= ELINK_LINK_1000THD;
			break;

		case ELINK_GP_STATUS_2_5G:
			vars->line_speed = ELINK_SPEED_2500;
			if (is_duplex == DUPLEX_FULL)
				vars->link_status |= ELINK_LINK_2500TFD;
			else
				vars->link_status |= ELINK_LINK_2500THD;
			break;

		case ELINK_GP_STATUS_5G:
		case ELINK_GP_STATUS_6G:
			ELINK_DEBUG_P1(sc,
				 "link speed unsupported  gp_status 0x%x\n",
				  speed_mask);
			return ELINK_STATUS_ERROR;

		case ELINK_GP_STATUS_10G_KX4:
		case ELINK_GP_STATUS_10G_HIG:
		case ELINK_GP_STATUS_10G_CX4:
		case ELINK_GP_STATUS_10G_KR:
		case ELINK_GP_STATUS_10G_SFI:
		case ELINK_GP_STATUS_10G_XFI:
			vars->line_speed = ELINK_SPEED_10000;
			vars->link_status |= ELINK_LINK_10GTFD;
			break;
		case ELINK_GP_STATUS_20G_DXGXS:
		case ELINK_GP_STATUS_20G_KR2:
			vars->line_speed = ELINK_SPEED_20000;
			vars->link_status |= ELINK_LINK_20GTFD;
			break;
		default:
			ELINK_DEBUG_P1(sc,
				  "link speed unsupported gp_status 0x%x\n",
				  speed_mask);
			return ELINK_STATUS_ERROR;
		}
	} else { /* link_down */
		ELINK_DEBUG_P0(sc, "phy link down\n");

		vars->phy_link_up = 0;

		vars->duplex = DUPLEX_FULL;
		vars->flow_ctrl = ELINK_FLOW_CTRL_NONE;
		vars->mac_type = ELINK_MAC_TYPE_NONE;
	}
	ELINK_DEBUG_P2(sc, " in elink_get_link_speed_duplex vars->link_status = %x, vars->duplex = %x\n",
			vars->link_status, vars->duplex);
	ELINK_DEBUG_P2(sc, " phy_link_up %x line_speed %d\n",
		    vars->phy_link_up, vars->line_speed);
	return ELINK_STATUS_OK;
}