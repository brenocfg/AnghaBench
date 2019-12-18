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
typedef  int uint8_t ;
struct elink_vars {scalar_t__ line_speed; int /*<<< orphan*/  link_status; } ;
struct elink_phy {scalar_t__ req_line_speed; int flags; int supported; int /*<<< orphan*/  (* config_init ) (struct elink_phy*,struct elink_params*,struct elink_vars*) ;} ;
struct elink_params {scalar_t__ loopback_mode; int num_phys; int port; struct elink_phy* phy; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 size_t ELINK_EXT_PHY1 ; 
 int ELINK_EXT_PHY2 ; 
 int ELINK_FLAGS_INIT_XGXS_FIRST ; 
 size_t ELINK_INT_PHY ; 
 scalar_t__ ELINK_LOOPBACK_EXT_PHY ; 
 scalar_t__ ELINK_LOOPBACK_XGXS ; 
 int ELINK_NIG_MASK_MI_INT ; 
 int ELINK_NIG_STATUS_SERDES0_LINK_STATUS ; 
 int ELINK_NIG_STATUS_XGXS0_LINK10G ; 
 int ELINK_NIG_STATUS_XGXS0_LINK_STATUS ; 
 scalar_t__ ELINK_SINGLE_MEDIA_DIRECT (struct elink_params*) ; 
 scalar_t__ ELINK_SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  ELINK_STATUS_OK ; 
 int ELINK_SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  LINK_STATUS_SERDES_LINK ; 
 scalar_t__ NIG_REG_STATUS_INTERRUPT_PORT0 ; 
 scalar_t__ PORT_HW_CFG_PHY_SELECTION_FIRST_PHY ; 
 int /*<<< orphan*/  USES_WARPCORE (struct bxe_softc*) ; 
 int /*<<< orphan*/  elink_bits_dis (struct bxe_softc*,scalar_t__,int) ; 
 scalar_t__ elink_phy_selection (struct elink_params*) ; 
 int /*<<< orphan*/  elink_prepare_xgxs (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  elink_set_parallel_detection (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  stub1 (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 
 int /*<<< orphan*/  stub2 (struct elink_phy*,struct elink_params*,struct elink_vars*) ; 

__attribute__((used)) static elink_status_t elink_link_initialize(struct elink_params *params,
				 struct elink_vars *vars)
{
	uint8_t phy_index, non_ext_phy;
	struct bxe_softc *sc = params->sc;
	/* In case of external phy existence, the line speed would be the
	 * line speed linked up by the external phy. In case it is direct
	 * only, then the line_speed during initialization will be
	 * equal to the req_line_speed
	 */
	vars->line_speed = params->phy[ELINK_INT_PHY].req_line_speed;

	/* Initialize the internal phy in case this is a direct board
	 * (no external phys), or this board has external phy which requires
	 * to first.
	 */
	if (!USES_WARPCORE(sc))
		elink_prepare_xgxs(&params->phy[ELINK_INT_PHY], params, vars);
	/* init ext phy and enable link state int */
	non_ext_phy = (ELINK_SINGLE_MEDIA_DIRECT(params) ||
		       (params->loopback_mode == ELINK_LOOPBACK_XGXS));

	if (non_ext_phy ||
	    (params->phy[ELINK_EXT_PHY1].flags & ELINK_FLAGS_INIT_XGXS_FIRST) ||
	    (params->loopback_mode == ELINK_LOOPBACK_EXT_PHY)) {
		struct elink_phy *phy = &params->phy[ELINK_INT_PHY];
		if (vars->line_speed == ELINK_SPEED_AUTO_NEG &&
		    (CHIP_IS_E1x(sc) ||
		     CHIP_IS_E2(sc)))
			elink_set_parallel_detection(phy, params);
		if (params->phy[ELINK_INT_PHY].config_init)
			params->phy[ELINK_INT_PHY].config_init(phy, params, vars);
	}

	/* Re-read this value in case it was changed inside config_init due to
	 * limitations of optic module
	 */
	vars->line_speed = params->phy[ELINK_INT_PHY].req_line_speed;

	/* Init external phy*/
	if (non_ext_phy) {
		if (params->phy[ELINK_INT_PHY].supported &
		    ELINK_SUPPORTED_FIBRE)
			vars->link_status |= LINK_STATUS_SERDES_LINK;
	} else {
		for (phy_index = ELINK_EXT_PHY1; phy_index < params->num_phys;
		      phy_index++) {
			/* No need to initialize second phy in case of first
			 * phy only selection. In case of second phy, we do
			 * need to initialize the first phy, since they are
			 * connected.
			 */
			if (params->phy[phy_index].supported &
			    ELINK_SUPPORTED_FIBRE)
				vars->link_status |= LINK_STATUS_SERDES_LINK;

			if (phy_index == ELINK_EXT_PHY2 &&
			    (elink_phy_selection(params) ==
			     PORT_HW_CFG_PHY_SELECTION_FIRST_PHY)) {
				ELINK_DEBUG_P0(sc,
				   "Not initializing second phy\n");
				continue;
			}
			params->phy[phy_index].config_init(
				&params->phy[phy_index],
				params, vars);
		}
	}
	/* Reset the interrupt indication after phy was initialized */
	elink_bits_dis(sc, NIG_REG_STATUS_INTERRUPT_PORT0 +
		       params->port*4,
		       (ELINK_NIG_STATUS_XGXS0_LINK10G |
			ELINK_NIG_STATUS_XGXS0_LINK_STATUS |
			ELINK_NIG_STATUS_SERDES0_LINK_STATUS |
			ELINK_NIG_MASK_MI_INT));
	return ELINK_STATUS_OK;
}