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
struct elink_vars {scalar_t__ check_kr2_recovery_cnt; } ;
struct elink_phy {int dummy; } ;
struct elink_params {int link_attr_sync; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL22_WR_OVER_CL45 (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int LINK_ATTR_SYNC_KR2_ENABLE ; 
 int /*<<< orphan*/  MDIO_AER_BLOCK_AER_REG ; 
 int /*<<< orphan*/  MDIO_AN_DEVAD ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_AUTO_NEG ; 
 int /*<<< orphan*/  MDIO_AN_REG_LP_AUTO_NEG2 ; 
 int /*<<< orphan*/  MDIO_REG_BANK_AER_BLOCK ; 
 int /*<<< orphan*/  elink_cl45_read (struct bxe_softc*,struct elink_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elink_disable_kr2 (struct elink_params*,struct elink_vars*,struct elink_phy*) ; 
 int elink_get_warpcore_lane (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_kr2_recovery (struct elink_params*,struct elink_vars*,struct elink_phy*) ; 
 int /*<<< orphan*/  elink_set_aer_mmd (struct elink_params*,struct elink_phy*) ; 
 int elink_warpcore_get_sigdet (struct elink_phy*,struct elink_params*) ; 
 int /*<<< orphan*/  elink_warpcore_restart_AN_KR (struct elink_phy*,struct elink_params*) ; 

__attribute__((used)) static void elink_check_kr2_wa(struct elink_params *params,
			       struct elink_vars *vars,
			       struct elink_phy *phy)
{
	struct bxe_softc *sc = params->sc;
	uint16_t base_page, next_page, not_kr2_device, lane;
	int sigdet;

	/* Once KR2 was disabled, wait 5 seconds before checking KR2 recovery
	 * Since some switches tend to reinit the AN process and clear the
	 * the advertised BP/NP after ~2 seconds causing the KR2 to be disabled
	 * and recovered many times
	 */
	if (vars->check_kr2_recovery_cnt > 0) {
		vars->check_kr2_recovery_cnt--;
		return;
	}

	sigdet = elink_warpcore_get_sigdet(phy, params);
	if (!sigdet) {
		if (!(params->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) {
			elink_kr2_recovery(params, vars, phy);
			ELINK_DEBUG_P0(sc, "No sigdet\n");
		}
		return;
	}

	lane = elink_get_warpcore_lane(phy, params);
	CL22_WR_OVER_CL45(sc, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, lane);
	elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
			MDIO_AN_REG_LP_AUTO_NEG, &base_page);
	elink_cl45_read(sc, phy, MDIO_AN_DEVAD,
			MDIO_AN_REG_LP_AUTO_NEG2, &next_page);
	elink_set_aer_mmd(params, phy);

	/* CL73 has not begun yet */
	if (base_page == 0) {
		if (!(params->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) {
			elink_kr2_recovery(params, vars, phy);
			ELINK_DEBUG_P0(sc, "No BP\n");
		}
		return;
	}

	/* In case NP bit is not set in the BasePage, or it is set,
	 * but only KX is advertised, declare this link partner as non-KR2
	 * device.
	 */
	not_kr2_device = (((base_page & 0x8000) == 0) ||
			  (((base_page & 0x8000) &&
			    ((next_page & 0xe0) == 0x20))));

	/* In case KR2 is already disabled, check if we need to re-enable it */
	if (!(params->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) {
		if (!not_kr2_device) {
			ELINK_DEBUG_P2(sc, "BP=0x%x, NP=0x%x\n", base_page,
			   next_page);
			elink_kr2_recovery(params, vars, phy);
		}
		return;
	}
	/* KR2 is enabled, but not KR2 device */
	if (not_kr2_device) {
		/* Disable KR2 on both lanes */
		ELINK_DEBUG_P2(sc, "BP=0x%x, NP=0x%x\n", base_page, next_page);
		elink_disable_kr2(params, vars, phy);
		/* Restart AN on leading lane */
		elink_warpcore_restart_AN_KR(phy, params);
		return;
	}
}