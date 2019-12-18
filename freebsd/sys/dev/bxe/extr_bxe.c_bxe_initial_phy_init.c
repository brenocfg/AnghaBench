#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct elink_params {scalar_t__* req_line_speed; int feature_config_flags; int* speed_cap_mask; int /*<<< orphan*/  loopback_mode; } ;
struct TYPE_2__ {scalar_t__ link_up; } ;
struct bxe_softc {struct elink_params link_params; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int CHIP_BOND_ID (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_MODE_4_PORT (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int ELINK_FEATURE_CONFIG_EMUL_DISABLE_BMAC ; 
 int ELINK_FEATURE_CONFIG_EMUL_DISABLE_EMAC ; 
 int ELINK_FEATURE_CONFIG_EMUL_DISABLE_UMAC ; 
 int ELINK_FEATURE_CONFIG_EMUL_DISABLE_XMAC ; 
 int /*<<< orphan*/  ELINK_LOOPBACK_EXT ; 
 int /*<<< orphan*/  ELINK_LOOPBACK_XGXS ; 
 scalar_t__ ELINK_SPEED_1000 ; 
 scalar_t__ ELINK_SPEED_10000 ; 
 int LOAD_DIAG ; 
 int LOAD_LOOPBACK_EXT ; 
 int PORT_HW_CFG_SPEED_CAPABILITY_D0_10G ; 
 int /*<<< orphan*/  STATS_EVENT_LINK_UP ; 
 int /*<<< orphan*/  bxe_acquire_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_calc_fc_adv (struct bxe_softc*) ; 
 int bxe_get_link_cfg_idx (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_link_report (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_periodic_start (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_release_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_set_requested_fc (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_stats_handle (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int elink_phy_init (struct elink_params*,TYPE_1__*) ; 

__attribute__((used)) static int
bxe_initial_phy_init(struct bxe_softc *sc,
                     int              load_mode)
{
    int rc, cfg_idx = bxe_get_link_cfg_idx(sc);
    uint16_t req_line_speed = sc->link_params.req_line_speed[cfg_idx];
    struct elink_params *lp = &sc->link_params;

    bxe_set_requested_fc(sc);

    if (CHIP_REV_IS_SLOW(sc)) {
        uint32_t bond = CHIP_BOND_ID(sc);
        uint32_t feat = 0;

        if (CHIP_IS_E2(sc) && CHIP_IS_MODE_4_PORT(sc)) {
            feat |= ELINK_FEATURE_CONFIG_EMUL_DISABLE_BMAC;
        } else if (bond & 0x4) {
            if (CHIP_IS_E3(sc)) {
                feat |= ELINK_FEATURE_CONFIG_EMUL_DISABLE_XMAC;
            } else {
                feat |= ELINK_FEATURE_CONFIG_EMUL_DISABLE_BMAC;
            }
        } else if (bond & 0x8) {
            if (CHIP_IS_E3(sc)) {
                feat |= ELINK_FEATURE_CONFIG_EMUL_DISABLE_UMAC;
            } else {
                feat |= ELINK_FEATURE_CONFIG_EMUL_DISABLE_EMAC;
            }
        }

        /* disable EMAC for E3 and above */
        if (bond & 0x2) {
            feat |= ELINK_FEATURE_CONFIG_EMUL_DISABLE_EMAC;
        }

        sc->link_params.feature_config_flags |= feat;
    }

    bxe_acquire_phy_lock(sc);

    if (load_mode == LOAD_DIAG) {
        lp->loopback_mode = ELINK_LOOPBACK_XGXS;
        /* Prefer doing PHY loopback at 10G speed, if possible */
        if (lp->req_line_speed[cfg_idx] < ELINK_SPEED_10000) {
            if (lp->speed_cap_mask[cfg_idx] &
                PORT_HW_CFG_SPEED_CAPABILITY_D0_10G) {
                lp->req_line_speed[cfg_idx] = ELINK_SPEED_10000;
            } else {
                lp->req_line_speed[cfg_idx] = ELINK_SPEED_1000;
            }
        }
    }

    if (load_mode == LOAD_LOOPBACK_EXT) {
        lp->loopback_mode = ELINK_LOOPBACK_EXT;
    }

    rc = elink_phy_init(&sc->link_params, &sc->link_vars);

    bxe_release_phy_lock(sc);

    bxe_calc_fc_adv(sc);

    if (sc->link_vars.link_up) {
        bxe_stats_handle(sc, STATS_EVENT_LINK_UP);
        bxe_link_report(sc);
    }

    if (!CHIP_REV_IS_SLOW(sc)) {
        bxe_periodic_start(sc);
    }

    sc->link_params.req_line_speed[cfg_idx] = req_line_speed;
    return (rc);
}